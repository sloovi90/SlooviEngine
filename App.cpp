#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Graphics/Window.h"
#include "Graphics/Model.h"
#include "Graphics/Camera.h"
#include "Graphics/GLProgram.h"
using namespace std;




int main() {
	try
	{
		glm::vec3 vert[] = {

				glm::vec3(-0.5f,-0.5f,0),

				glm::vec3(0.5f,-0.5f,0),

				glm::vec3(0.5f,0.5f,0)

		};



		unsigned int indices[] = { 0,1,2 };

		WindowPtr win = Window::CreateWindow("SlooviEngine", 800, 600);
		win->FocusOnContext();
		ModelPtr mod = Model::CreateFromObj("Models/sphere.obj");
		mod->Scale(glm::vec3(1.5f, 1.5f, 1.5f));
		CameraPtr cam = std::make_shared<Camera>(glm::vec3(0, 0, -2), glm::vec3(0, 0, 0));
		cam->SetCameraPerspective(60, 800.0f / 600.0f, 0.01, 100);
		MaterialPtr mat = std::make_shared<Material>("Default");
		mod->SetModelMaterial(mat);
		mod->SetModelColoring(ColoringType::Textured);
		ProgramPtr program = make_shared<GLProgram>("Default");
		program->AttachShader(ShaderType::VERTEX_SHADER, "Shaders/basic_vert.vert");
		program->AttachShader(ShaderType::FRAGMENT_SHADER, "Shaders/basic_frag.frag");
		program->BuildProgram();
		mat->SetDrawingProgram(program);
		Texture2DPtr tex = Texture2D::CreateTextureFromFile("Textures/earth.png",GL_RGB);
		mod->SetMainTexture(tex);

		while (!win->NeedToClose()) {
			mod->RotateAroundModelOrigin(glm::vec3(0, 1, 0), 0.1f);
			mod->Draw(cam);
			
			win->Refresh();
		}

	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}


	return 0;
}
