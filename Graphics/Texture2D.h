#pragma once

#include <memory>
#include <glad/glad.h>
#include <string>


class Texture2D;
typedef std::shared_ptr<Texture2D> Texture2DPtr;

class Texture2D {

	GLuint textureId;
	int channels;
	int texHeight;
	int texWidth;


	Texture2D():textureId(-1),texHeight(0),texWidth(0),channels(0) {}
public:
	static Texture2DPtr CreateEmptyTexture(int width, int height, int fixedSizeFormat = GL_RGB8);
	static Texture2DPtr CreateTextureFromFile(const std::string& imagePath, int format = GL_RGB);
	void BindTextureToUnit(unsigned int unit);
	void UpdateTextureData(const unsigned char* texData, int format = GL_RGB);
	~Texture2D();


	



};
