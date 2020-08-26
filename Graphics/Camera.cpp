#include "Camera.h"



Camera::Camera(const glm::vec3 eye, const glm::vec3 lookAtPos, const glm::vec3 up) :camType(CameraType::Perspective) {
	viewMatrix = glm::lookAt(eye, lookAtPos, up);
	projectionMatrix = glm::perspective(45.f, 800.f / 600.f, 0.01f, 10.f);
}

void Camera::SetCameraPerspective(float fov, float aspect, float near, float far) {
	camType = CameraType::Perspective;
	projectionMatrix = glm::perspective(fov, aspect, near, far);
}

void Camera::SetCameraOrtho(float left, float right, float bottom, float top, float near, float far) {
	camType = CameraType::Orthographic;
	projectionMatrix = glm::ortho(left, right, bottom, top, near, far);
}

void Camera::RotateCamera(const glm::vec3 axis, float angle)
{	
	viewMatrix = glm::rotate(viewMatrix, angle, axis);
}

void Camera::RotateCameraAroundSelf(const glm::vec3 axis, float angle)
{
	glm::vec3 camLocation = viewMatrix[3];
	viewMatrix = glm::translate(viewMatrix, -camLocation);
	RotateCamera(axis, angle);
	viewMatrix = glm::translate(viewMatrix, camLocation);
}

void Camera::TranslateCamera(const glm::vec3 translation)
{
	viewMatrix = glm::translate(viewMatrix, translation);
}

const glm::mat4 Camera::GetCameraViewProjectionMatrix() {
	return projectionMatrix * viewMatrix;
}

