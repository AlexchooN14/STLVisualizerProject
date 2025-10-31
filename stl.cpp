#include "stl.h"
#include "Vertex.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <ios>

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

	for (StlFileContent& triangle : this->contents) {
		vertices.push_back(Vertex(triangle.vertex1, triangle.normalVector));
		vertices.push_back(Vertex(triangle.vertex2, triangle.normalVector));
		vertices.push_back(Vertex(triangle.vertex3, triangle.normalVector));
	}

	return vertices;
}
