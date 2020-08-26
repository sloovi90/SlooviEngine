#version 430 core


in vec2 vTexCoord;

out vec4 color;

uniform sampler2D MainTexture;

void main()
{
		color = texture(MainTexture,vTexCoord);

}
