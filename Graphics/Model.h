#pragma once
#include <string>
#include <vector>
#include <memory>
#include <glad/glad.h>
#include "GraphicsDefinitions.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Material.h"
#include "Camera.h"
#include "Texture2D.h"

class Model;
typedef std::shared_ptr <Model> ModelPtr;

class Model {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::string modelName;
	bool active = true;

	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	glm::vec3 modelPos;
	glm::mat4 modelMatrix;
	MaterialPtr modelMaterial;
	ColoringType coloringType;
	Texture2DPtr mainTexture;
	bool isMainTexPartial;
	TexRect mainTexCoverZone;

public:
	Model(const std::string& name,const std::vector<Vertex> verts, const std::vector<unsigned int> indices,ColoringType type=ColoringType::None);
	static ModelPtr CreateFromObj(const std::string& modelObjPath);
	void Draw(const CameraPtr& cam);
	void Translate(const glm::vec3 translation,CoordSys coordSys=CoordSys::World);
	void RotateAroundModelOrigin(const glm::vec3 axis, float angle);
	void Scale(const glm::vec3 scale);
	const glm::mat4& GetModelMatrix();
	operator std::string() const { return modelName; }
	void SetModelMaterial(MaterialPtr material);
	const MaterialPtr GetModelMaterial();
	void SetModelColoring(ColoringType colorType);
	void SetMainTexture(Texture2DPtr mainTexture);
	void SetPartialMainTexture(Texture2DPtr partMainTexture);
	void SetTextureRect(TexRect texCoverZone);
	void SetActive(bool newStatus);
private:
	Model();
	void setupModelGraphics();




};
