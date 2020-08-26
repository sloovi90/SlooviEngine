#version 430 core


struct Rect
{
	float minX;
	float maxX;
	float minY;
	float maxY;
};

in vec2 vTexCoord;

out vec4 color;

uniform sampler2D MainTexture;
uniform int useTextures = 0;
uniform int isMainTexPartial = 0;
uniform Rect mainTexZoneCover;

void main()
{
	if(useTextures==1)
	{
		if(isMainTexPartial ==0 ){
			color = texture(MainTexture,vTexCoord);
			return;
		}
		//texcoord.x >= minX && texcoord.x <maxX
		//else if(step(mainTexZoneCover.minX,vTexCoord.x)-step(mainTexZoneCover.maxX,vTexCoord.x) == 1.0) 
		else if(vTexCoord.x >= mainTexZoneCover.minX && vTexCoord.x <= mainTexZoneCover.maxX && vTexCoord.y >= mainTexZoneCover.minY && vTexCoord.y <= mainTexZoneCover.maxY) 
		{
			//calc new texture coord in relation to the area that the texture cover
			float Vx=(vTexCoord.x-mainTexZoneCover.minX)/(mainTexZoneCover.maxX-mainTexZoneCover.minX);
			float Vy = (vTexCoord.y-mainTexZoneCover.minY) / (mainTexZoneCover.maxY-mainTexZoneCover.minY);
			Vx=1+Vx*-1;
			color=texture(MainTexture,vec2(Vx,Vy));
			return;
		}
	}
	
	color = vec4(1);
	
}
