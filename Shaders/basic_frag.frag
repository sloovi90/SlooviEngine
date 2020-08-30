#version 430 core



in vec2 vTexCoord;

out vec4 color;

uniform sampler2D MainTexture;
uniform int useTextures = 0;


void main()
{
	if(useTextures==1)
	{
			vec4 c=texture(MainTexture,vTexCoord);
			color = c;
			
			return;
	}
	
	color = vec4(1);
	
}
