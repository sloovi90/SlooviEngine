#include <glad/glad.h>
#include "GLProgram.h"


GLProgram::GLProgram(const std::string& name) {
	programId = glCreateProgram();
	programName = name;
}

void GLProgram::AttachShader(ShaderType type, const std::string& shaderPath) {
	GLShaderPtr shader=std::make_shared<GLShader>(type, shaderPath);
	try
	{
		shader->ReadAndCompileShader();
		shaders.push_back(shader);
		//conversion op of shader will activate here
		glAttachShader(programId, *shader);
	}
	catch (const GLShader::GLShaderException& ex)
	{
		throw GLProgramException(std::string(ex.what()));
	}
}
//void GLProgram::AttachCompiledShader(const GLShaderPtr shader)
//{
//	//conversion op of shader will activate here
//	if (*shader != 0 && shader->IsCompiled()) {
//		shaders.push_back(shader);
//		glAttachShader(programId, *shader);
//	}
//}
void GLProgram::BuildProgram() {
	
	glLinkProgram(programId);
	int success;
	char infoLog[512];
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programId, 512, NULL, infoLog);
		throw GLProgramException(infoLog);
	}
}
void GLProgram::Start()
{
	glUseProgram(programId);
}

void GLProgram::Stop() {
	glUseProgram(0);
}

void GLProgram::SetUniformInt(const std::string& uniformName, int val)
{
	auto uniformLoc = glGetUniformLocation(*this, uniformName.c_str());
	if (uniformLoc == -1)
		throw GLProgramException(uniformName + " wasn't found!");
	glUniform1i(uniformLoc, val);
	
}

void GLProgram::SetUniformUInt(const std::string& uniformName, unsigned int val)
{
	auto uniformLoc = glGetUniformLocation(*this, uniformName.c_str());
	if (uniformLoc == -1)
		throw GLProgramException(uniformName + " wasn't found!");
	glUniform1ui(uniformLoc, val);
}

void GLProgram::SetUniformFloat(const std::string& uniformName, float val)
{
	auto uniformLoc = glGetUniformLocation(*this, uniformName.c_str());
	if (uniformLoc == -1)
		throw GLProgramException(uniformName + " wasn't found!");
	glUniform1f(uniformLoc, val);
	
}

void GLProgram::SetUniformMat4(const std::string& uniformName, const glm::mat4 matrix)
{
	auto uniformLoc = glGetUniformLocation(programId,uniformName.c_str());
	if (uniformLoc == -1) 
		throw GLProgramException(uniformName + " wasn't found!");
	
	glUniformMatrix4fv(uniformLoc, 1,GL_FALSE, &matrix[0][0]);
	
}

void GLProgram::SetUniformVec3(const std::string& uniformName, const glm::vec3 vector)
{
	auto uniformLoc = glGetUniformLocation(*this, uniformName.c_str());
	if (uniformLoc == -1)
		throw GLProgramException(uniformName + " wasn't found!");
	glUniform3fv(uniformLoc, 1, &vector[0]);
}

GLProgram::~GLProgram() {
	//this will trigger automatic shaders detach
	glDeleteProgram(programId);
	//the destructor of the shaders will be called here and therefore deleted immidiately
}