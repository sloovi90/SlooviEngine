#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GraphicsDefinitions.h"
#include <memory>

class Camera;
typedef std::shared_ptr<Camera> CameraPtr;

class Camera {
	CameraType camType;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
public:
	Camera(const glm::vec3 eye, const glm::vec3 lookAtPos, const glm::vec3 up = glm::vec3(0, 1, 0));

	void SetCameraPerspective(float fov, float aspect, float near, float far);

	void SetCameraOrtho(float left, float right, float bottom, float top, float near, float far);
	//rotate around world center
	void RotateCamera(const glm::vec3 axis, float angle);
	//rotate around camera center
	void RotateCameraAroundSelf(const glm::vec3 axis, float angle);

	void TranslateCamera(const glm::vec3 translation);
	const glm::mat4 GetCameraViewProjectionMatrix();

	


};