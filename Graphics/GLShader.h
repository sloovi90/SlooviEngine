#pragma once
#include <string>
#include "GraphicsDefinitions.h"
#include <exception>
#include <memory>

class GLShader;
typedef std::shared_ptr<GLShader> GLShaderPtr;


class GLShader {

private :
	void CompileShaderInternal(const std::string& shaderSource);
	void ReadShaderSource(std::string& shaderSource);

protected:
	bool m_isCompiled;
	unsigned int shaderId;
	const std::string shaderPath;
public:
	GLShader(const GLShader&) = delete;
	class GLShaderException : public std::exception {
		std::string error;
	public:
		GLShaderException(const std::string& error) :error(error) {};
		const char* what() const throw ()
		{
			return error.c_str();
		}
	};
	GLShader(ShaderType shaderType, const std::string& shaderSourcePath);
	operator GLuint() const { return shaderId; }
	void ReadAndCompileShader();
	bool IsCompiled() const;

	virtual ~GLShader();
	

};