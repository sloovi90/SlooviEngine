#include "Model.h"
#include <cstddef>
#include "../Tools/ObjReader.h"

Model::Model(const std::string& name, const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, ColoringType type) :
	modelMatrix(1.f),
	coloringType(type),
	isMainTexPartial(false),
	modelPos(glm::vec3(0))
{
	modelName = name;
	this->vertices = vertices;
	this->indices = indices;
	setupModelGraphics();


}


ModelPtr Model::CreateFromObj(const std::string& modelObjPath)
{
	Model* model = new Model();
	size_t lastSlashIndex = modelObjPath.find_last_of("/\\");
	size_t lastPointIndex = modelObjPath.find_last_of(".");
	model->modelName = modelObjPath.substr(lastSlashIndex + 1, lastPointIndex - lastSlashIndex - 1);
	ObjReader::ReadFromObj(modelObjPath, model->vertices, model->indices);
	if (model)
		model->setupModelGraphics();
	return ModelPtr(model);
}

void Model::Draw(const CameraPtr& cam)
{
	if (modelMaterial) {

		auto prog = modelMaterial->GetDrawingProgram();
 		auto mvp = cam->GetCameraViewProjectionMatrix() * modelMatrix;
		prog->Start();
		bool useTextures = false;
 		if (coloringType == ColoringType::None)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			if (coloringType == ColoringType::Textured)
				useTextures = true;
		}

		if (useTextures) {
			if (mainTexture) {
				mainTexture->BindTextureToUnit(0);
				prog->SetUniformInt("MainTexture", 0);
				prog->SetUniformInt("useTextures", 1);
			}
		}
		else {
			prog->SetUniformInt("useTextures", 0);
		}

		prog->SetUniformMat4("CameraMatrix", mvp);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
		prog->Stop();

	}

}

void Model::Translate(const glm::vec3 translation, CoordSys coordSys)
{
	if (coordSys == CoordSys::World) {
		modelPos += translation;
		modelMatrix[3] += glm::vec4(translation.x, translation.y, translation.z, 0.f);
	}
	else if (coordSys == CoordSys::Local) {
		//glm::translate uses the current matrix columns meaning the current orientation 
		//axises thus it will move in local axies
		glm::vec4 trans = (modelMatrix[0] * translation.x + modelMatrix[1] * translation.y + modelMatrix[2] * translation.z);
		modelPos += glm::vec3(trans.x, trans.y, trans.z);
		modelMatrix = glm::translate(modelMatrix, translation);
	}

}

void Model::RotateAroundModelOrigin(const glm::vec3 axis, float angle)
{
	//in order to rotate around model center we translate to origin rotate and go back
	auto origPos = modelPos;
	Translate(-origPos);
	modelMatrix = glm::rotate(modelMatrix, angle, axis);
	Translate(origPos);
}

void Model::Scale(const glm::vec3 scale)
{
	//in order to scale around model center we translate to origin scale and go back
	auto origPos = modelPos;
	Translate(-origPos);
	modelMatrix[0][0] *= scale.x;
	modelMatrix[1][1] *= scale.y;
	modelMatrix[2][2] *= scale.z;
	Translate(origPos);
}

const glm::mat4& Model::GetModelMatrix()
{
	return modelMatrix;
}

void Model::SetModelMaterial(MaterialPtr material)
{
	if (material)
		modelMaterial = material;
}

const MaterialPtr Model::GetModelMaterial()
{
	return modelMaterial;
}

void Model::SetModelColoring(ColoringType colorType)
{
	coloringType = colorType;
}

void Model::SetMainTexture(Texture2DPtr mainTexture)
{
	isMainTexPartial = false;
	this->mainTexture = mainTexture;
}


void Model::SetActive(bool newStatus)
{
	active = newStatus;
}



Model::Model() :vao(-1), vbo(-1), ebo(-1), modelMatrix(1.f)
{

	modelPos = glm::vec3(0);
	modelMaterial = nullptr;
}

void Model::setupModelGraphics()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//vertex position attribute
	glEnableVertexArrayAttrib(vao, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	////vertex normal attribute
	//glEnableVertexArrayAttrib(vao, 1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex,normal));
	//
	////vertex texture coord attribute
	glEnableVertexArrayAttrib(vao, 2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoord));

	glBindVertexArray(0);
}
