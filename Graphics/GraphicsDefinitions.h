#pragma once
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>




enum class ShaderType {
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
	GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
	COMPUTE_SHADER = GL_COMPUTE_SHADER
};

enum class CameraType {
	Orthographic,
	Perspective
};

enum class CoordSys{
	World,
	Local
};

enum class ColoringType {
	None,
	Solid,
	Textured
};


enum class MonitorType {
	DONT_CARE=-1,
	PRIMARY = 0,
	SECONDARY,
	THIRD,
	FOURTH,
	MAX_NUMBER_OF_MONITORS
};


struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoord;
	bool operator==(const Vertex vert) {
		return position == vert.position && normal == vert.normal && textureCoord == vert.textureCoord;
	}
};

struct TexRect {
	float minX;
	float maxX;
	float minY;
	float maxY;
	TexRect(float xmin, float xmax, float ymin, float ymax) :minX(xmin), maxX(xmax), minY(ymin), maxY(ymax) {}
	TexRect() :minX(0), maxX(1), minY(0), maxY(1) {}
};