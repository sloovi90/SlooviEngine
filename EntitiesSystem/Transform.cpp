#include "Transform.h"

Transform::Transform()
{
}

void Transform::Translate(const glm::vec3 translation, CoordSys coordSys)
{
}

void Transform::RotateAroundModelOrigin(const glm::vec3 axis, float angle)
{
}

void Transform::Scale(const glm::vec3 scale)
{
}

const glm::mat4& Transform::GetModelMatrix()
{
	return glm::mat4();
}
