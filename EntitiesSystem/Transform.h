#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "../Graphics/GraphicsDefinitions.h"


class Transform
{

	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 eulerAngles;

public:
	Transform();
	void Translate(const glm::vec3 translation, CoordSys coordSys = CoordSys::World);
	void RotateAroundModelOrigin(const glm::vec3 axis, float angle);
	void Scale(const glm::vec3 scale);
	const glm::mat4& GetModelMatrix();
};