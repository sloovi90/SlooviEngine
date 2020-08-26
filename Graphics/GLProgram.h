#pragma once
#include <string>
#include <vector>
#include "GLShader.h"
#include <memory>
#include "GraphicsDefinitions.h"
#include "glm/gtc/matrix_transform.hpp"

class GLProgram;
typedef std::shared_ptr<GLProgram> ProgramPtr;

class GLProgram {
protected:
	std::vector<GLShaderPtr> shaders;
	unsigned int programId;
	std::string programName;
public:
	GLProgram(const GLProgram&) = delete;
	GLProgram(const std::string& name);
	void AttachShader(ShaderType type, const std::string& shaderPath);
	//useful when multiple programs use the same shader - compile once, attach and link multiple times
//	void AttachCompiledShader(const GLShaderPtr shader);
	void BuildProgram();
	void Start();
	void Stop();

	void SetUniformInt(const std::string& uniformName, int val);
	void SetUniformUInt(const std::string& uniformName, unsigned int val);
	void SetUniformFloat(const std::string& uniformName, float val);
	void SetUniformMat4(const std::string& uniformName, const glm::mat4 matrix);
	void SetUniformVec3(const std::string& uniformName, const glm::vec3 vector);

	operator GLuint() const { return programId; };
	operator const std::string() const { return programName; }
	~GLProgram();
	class GLProgramException : public std::exception {
		std::string error;
	public:
		GLProgramException(const std::string& error) :error(error) {};
		const char* what() const throw ()
		{
			return error.c_str();
		}
	};
};

