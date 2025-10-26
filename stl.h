#ifndef STL_FILE_STRUCT_H
#define STL_FILE_STRUCT_H

#include <cstdint>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"

#pragma pack(push, 1)
typedef struct StlFileHeader {
	uint8_t header[80];
	uint32_t numberOfTriangles;
}StlFileHeader;

typedef struct StlFileContent {
	float normalVector[3];
	float vertex1[3];
	float vertex2[3];
	float vertex3[3];
	uint16_t attributeByteCount;
}StlFileContent;
#pragma pack(pop)

class StlFile {
public:
	StlFileHeader header;
	std::vector<StlFileContent> contents;

	StlFile(std::string filename);

	void readStlFileContents(std::string filename);

	std::vector<Vertex> verticesConvertVertexArray();
};

void printVec3(std::ostream& stream, const std::string name, const float vector[3]);
std::ostream& operator<<(std::ostream& stream, StlFileHeader& header);
std::ostream& operator<<(std::ostream & stream, const StlFileContent & content);
std::ostream& operator<<(std::ostream & stream, const StlFile & file);


#endif // !STL_FILE_STRUCT_H
