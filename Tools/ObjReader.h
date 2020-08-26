#pragma once
#include <vector>
#include <string>
#include "..//Graphics/GraphicsDefinitions.h"

class ObjReader {

public:
	static bool ReadFromObj(const std::string& modelObjPath, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);



};