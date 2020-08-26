#include "Material.h"


Material::Material(const std::string& name)
{

	materialName = name;
}

void Material::SetDrawingProgram(ProgramPtr program)
{
	drawingProgram = program;
}

const ProgramPtr& Material::GetDrawingProgram()
{
	return drawingProgram;
}
