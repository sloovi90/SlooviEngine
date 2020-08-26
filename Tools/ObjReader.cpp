#include "ObjReader.h"
#include <fstream>
#include <sstream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <set>



bool ObjReader::ReadFromObj(const std::string& modelObjPath, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	bool res = true;
	std::ifstream modelFile(modelObjPath);
	

	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	
	std::string line;
	while (std::getline(modelFile, line)) {
		std::istringstream ss(line);
		std::string type;
		ss >> type;
		if (type == "v") {
			glm::vec3 vert;
			ss >> vert.x;
			ss >> vert.y;
			ss >> vert.z;
			verts.push_back(vert);
		}
		else if (type == "vn") {
			glm::vec3 normal;
			ss >> normal.x;
			ss >> normal.y;
			ss >> normal.z;
			normals.push_back(normal);
		}
		else if (type == "vt") {
			glm::vec2 texcoord;
			ss >> texcoord.x;
			ss >> texcoord.y;
			texCoords.push_back(texcoord);
		}
		else if (type == "f") {
			for (int i = 0;  i < 3; i++) {
				Vertex vert;
				std::string faceVert;
				ss >> faceVert;
				std::istringstream faceVertStream(faceVert);
				std::string vertIndex;
				std::getline(faceVertStream, vertIndex, '/');
				vert.position = verts[stoi(vertIndex)-1];
				std::string texCoordIndex;
				std::getline(faceVertStream, texCoordIndex, '/');
				vert.textureCoord = texCoords[stoi(texCoordIndex)-1];
				std::string normalIndex;
				std::getline(faceVertStream, normalIndex, '/');
				vert.normal = normals[stoi(normalIndex)-1];
				auto iter = std::find(vertices.begin(), vertices.end(), vert);
				int index;
				if (iter == vertices.end()) {
					index = (int)vertices.size();
					vertices.push_back(vert);
				}else {
					index = std::distance(vertices.begin(), iter);
				}
				indices.push_back(index);
			}
			



		}
	}
	
	return res;
}
