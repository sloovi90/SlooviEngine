#pragma once
#include "GLProgram.h"
#include <memory>

class Material;
typedef std::shared_ptr<Material> MaterialPtr;

class Material {
	//add lighting params here
	ProgramPtr drawingProgram;
	std::string materialName;

public:
	Material(const std::string& name);
	void SetDrawingProgram(ProgramPtr program);
	const ProgramPtr& GetDrawingProgram();
};

