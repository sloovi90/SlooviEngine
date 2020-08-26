#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 CameraMatrix;
out vec2 vTexCoord;

void main()
{

	vTexCoord=texcoord;

    gl_Position = CameraMatrix*vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
