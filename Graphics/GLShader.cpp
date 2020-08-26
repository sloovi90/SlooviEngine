#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include "GLShader.h"


GLShader::GLShader(ShaderType shaderType,const std::string& shaderSourcePath) :shaderPath(shaderSourcePath),
	m_isCompiled(false)
{
	shaderId = glCreateShader((int)shaderType);

}

void GLShader::CompileShaderInternal(const std::string& shaderSource) {
	const GLchar* shaderSourceCode = shaderSource.c_str();
	glShaderSource(shaderId, 1, &shaderSourceCode, NULL);
	glCompileShader(shaderId);

	int  success;
	char infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		throw GLShaderException(std::string(infoLog));
	}
	m_isCompiled = true;
}

void GLShader::ReadShaderSource(std::string& shaderSource) {
	std::ifstream infile(shaderPath);
	std::string line;

	while (std::getline(infile, line)) {
		shaderSource.append(line+'\n');
		
	}
}

void GLShader::ReadAndCompileShader() {
	std::string shaderSource;
	ReadShaderSource(shaderSource);
	CompileShaderInternal(shaderSource);
}

bool GLShader::IsCompiled() const
{
	return m_isCompiled;
}

GLShader::~GLShader() {
	//this deletion only marks the shader- only when all program that attached this shader
	//detaches it it will be deleted
	glDeleteShader(shaderId);
}

