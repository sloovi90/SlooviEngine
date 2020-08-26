#pragma once
#include "GLProgram.h"

class GLComputeProgram : public GLProgram{

	
public:
	GLComputeProgram(const GLComputeProgram&) = delete;
	GLComputeProgram(const std::string& name);
	void AttachShader(const std::string& shaderPath);
	void Dispatch(const std::string& func,int num_groups_x,int num_groups_y=1,int num_groups_z=1);
	void DispatchWithGroupSize(const std::string& func, int num_groups_x, int num_groups_y, int num_groups_z,
		int work_group_size_x, int work_group_size_y, int work_group_size_z);
};