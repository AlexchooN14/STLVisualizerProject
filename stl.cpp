#include "stl.h"
#include "Vertex.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <ios>
#include <glm/glm.hpp>


void printVec3(std::ostream& stream, const std::string name, const float vector[3]) {
	static const char axis[] = { 'x', 'y', 'z' };
	stream << std::setw(8) << std::left << name << ": ";
	for (int i = 0; i < 3; i++) {
		stream << axis[i] << " = " << std::setw(10) << std::right << vector[i];
		if (i < 2) stream << ", ";
	}
	stream << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const StlFileHeader& header) {
	stream << "Header: ";
	for (uint8_t byte : header.header) {
		stream << byte;
	}
	stream << std::endl;
	stream << "Triangles: " << header.numberOfTriangles << std::endl;

	return stream;
}

std::ostream& operator<<(std::ostream& stream, const StlFileContent& content) {
	printVec3(stream, "Normal", content.normalVector);
	printVec3(stream, "Vertex1", content.vertex1);
	printVec3(stream, "Vertex2", content.vertex2);
	printVec3(stream, "Vertex3", content.vertex3);

	/*stream << "attributeByteCount" << std::endl;
	for (int i = 0; i < 2; i++) {
		stream << "Byte" << i << ":" << std::endl;
		for (int j = 15; j > 0; j--) {
			stream << "Bit" << abs(j - 15) << ": " << (content.attributeByteCount >> j) << std::endl;
		}
	}*/

	return stream;
}

std::ostream& operator<<(std::ostream& stream, const StlFile& file) {
	stream << file.header << std::endl;
	for (const auto& triangle : file.contents) {
		stream << triangle << std::endl;
	}

	return stream;
}

StlFile::StlFile(std::string filename) {
	readStlFileContents(filename);
}

void StlFile::readStlFileContents(std::string filename) {
	std::ifstream file(filename, std::ios::binary);

	if (!file) {
		throw std::runtime_error("Error opening STL file: " + filename);
	}

	file.read(reinterpret_cast<char*>(&this->header), sizeof(this->header));

	contents.resize(header.numberOfTriangles);

	file.read(reinterpret_cast<char*>(contents.data()),
		this->header.numberOfTriangles * sizeof(StlFileContent));

	file.close();
}

std::vector<Vertex> StlFile::verticesConvertVertexArray() {
	std::vector<Vertex> vertices;

	// Step 1: Compute bounding box
	glm::vec3 minBounds(FLT_MAX);
	glm::vec3 maxBounds(-FLT_MAX);

	for (const StlFileContent& triangle : this->contents) {
		for (int i = 0; i < 3; ++i) {
			glm::vec3 v1(triangle.vertex1[0], triangle.vertex1[1], triangle.vertex1[2]);
			glm::vec3 v2(triangle.vertex2[0], triangle.vertex2[1], triangle.vertex2[2]);
			glm::vec3 v3(triangle.vertex3[0], triangle.vertex3[1], triangle.vertex3[2]);

			minBounds = glm::min(minBounds, v1);
			minBounds = glm::min(minBounds, v2);
			minBounds = glm::min(minBounds, v3);

			maxBounds = glm::max(maxBounds, v1);
			maxBounds = glm::max(maxBounds, v2);
			maxBounds = glm::max(maxBounds, v3);
		}
	}

	// Step 2: Compute center and scale
	glm::vec3 center = (minBounds + maxBounds) * 0.5f;
	glm::vec3 size = maxBounds - minBounds;
	float maxDimension = std::max({ size.x, size.y, size.z });

	// Step 3: Normalize and convert to Vertex
	for (StlFileContent& triangle : this->contents) {
		glm::vec3 normal(triangle.normalVector[0], triangle.normalVector[1], triangle.normalVector[2]);

		glm::vec3 v1 = (glm::vec3(triangle.vertex1[0], triangle.vertex1[1], triangle.vertex1[2]) - center) / maxDimension;
		glm::vec3 v2 = (glm::vec3(triangle.vertex2[0], triangle.vertex2[1], triangle.vertex2[2]) - center) / maxDimension;
		glm::vec3 v3 = (glm::vec3(triangle.vertex3[0], triangle.vertex3[1], triangle.vertex3[2]) - center) / maxDimension;

		vertices.push_back(Vertex(v1, normal, glm::vec3(0.0f)));
		vertices.push_back(Vertex(v2, normal, glm::vec3(0.0f)));
		vertices.push_back(Vertex(v3, normal, glm::vec3(0.0f)));
	}

	return vertices;
}
