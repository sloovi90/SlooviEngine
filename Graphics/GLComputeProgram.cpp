#include "GLComputeProgram.h"
#include "GLShader.h"
GLComputeProgram::GLComputeProgram(const std::string& name):GLProgram(name)
{

}

void GLComputeProgram::AttachShader(const std::string& shaderPath)
{
	GLProgram::AttachShader(ShaderType::COMPUTE_SHADER, shaderPath);
}

void GLComputeProgram::Dispatch(const std::string& func, int num_groups_x, int num_groups_y, int num_groups_z)
{
	auto subroutineUniformIndex = glGetSubroutineIndex(programId, GL_COMPUTE_SHADER, func.c_str());
	if (subroutineUniformIndex != -1) {
		glUniformSubroutinesuiv(GL_COMPUTE_SHADER, 1, &subroutineUniformIndex);
	}
	glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void GLComputeProgram::DispatchWithGroupSize(const std::string& func, int num_groups_x, int num_groups_y, int num_groups_z, int work_group_size_x, int work_group_size_y, int work_group_size_z)
{
	auto subroutineUniformIndex = glGetSubroutineIndex(programId, GL_COMPUTE_SHADER, func.c_str());
	if (subroutineUniformIndex != -1) {
		glUniformSubroutinesuiv(GL_COMPUTE_SHADER, 1, &subroutineUniformIndex);
	}
	glDispatchComputeGroupSizeARB(num_groups_x, num_groups_y, num_groups_z, 
		work_group_size_x, work_group_size_y, work_group_size_z);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}
