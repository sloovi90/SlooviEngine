#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <Tools/stb_image.h>

Texture2DPtr Texture2D::CreateEmptyTexture(int width, int height,int fixedSizeFormat)
{
	Texture2D* tex = new Texture2D();
	tex->texHeight = height;
	tex->texWidth = width;
	glGenTextures(1, &tex->textureId);
	glBindTexture(GL_TEXTURE_2D, tex->textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//allocate memory on gpu for the texture
	glTexStorage2D(GL_TEXTURE_2D, 1, fixedSizeFormat, tex->texWidth, tex->texHeight);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	return Texture2DPtr(tex);
}

Texture2DPtr Texture2D::CreateTextureFromFile(const std::string& imagePath, int format)
{
	Texture2D * tex = new Texture2D();
	glGenTextures(1, &tex->textureId);
	glBindTexture(GL_TEXTURE_2D, tex->textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	auto data = stbi_load(imagePath.c_str(), &tex->texWidth, &tex->texHeight, &tex->channels, 3);

	if (data) {
		
		//glTexStorage2D(GL_TEXTURE_2D, 1, fixedSizeFormat, tex->texWidth, tex->texHeight);
		//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, tex->texWidth, tex->texHeight, fixedSizeFormat, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, format, tex->texWidth, tex->texHeight, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else {
		
		delete tex;
		tex=nullptr;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	return Texture2DPtr(tex);
}

void Texture2D::BindTextureToUnit(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture2D::UpdateTextureData(const unsigned char* texData, int format)
{
	if (texData) {
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texWidth, texHeight, format, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

	}
}

Texture2D::~Texture2D()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureId);
}
