#pragma once
#include <memory>
#include <vector>
#include <glad/glad.h>
#include <iostream>
template <typename T>
class GLBufferT {
	GLBufferT() {
		glGenBuffers(1,&ssboId);
	}
	GLuint ssboId;
	int elementCount;
public:
	static std::shared_ptr<GLBufferT<T>> CreateBuffer(int elementNumber,int shaderBufferIndex) {
		GLBufferT* buffer = new GLBufferT();
		elementCount = elementNumber;
		glBindBuffer(GL_SHADER_STORAGE_BUFFER,ssboId);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(T) * elementCount, NULL, GL_STATIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, shaderBufferIndex, ssboId);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
	void Upload(const std::vector<T>& dataToUpload)
	{
		if (data.size() > elementCount) {
			std::cout << "Warning: data passed to buffer is larger than original buffer size!!" << std::endl;
		}
		int elementNumber = elementCount < dataToUpload.size() ? elementCount : dataToUpload.size();
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboId);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(T) * elementNumber, dataToUpload.data());
	}
	//dataToDownload should be allocated
	void Download(std::vector<T>& dataToDownload)
	{
		if (dataToDownload.size() > elementCount) {
			std::cout << "Warning: requested more data than existing" << std::endl;
		}
		int elementNumber = elementCount < dataToUpload.size() ? elementCount : dataToUpload.size();
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboId);
		glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, elementNumber * sizeof(T), dataToDownload.data());
	}
	
};


