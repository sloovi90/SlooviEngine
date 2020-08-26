#include "Scene.h"

Scene::Scene(const std::string& name)
{
	activeCamera = nullptr;
	sceneName = name;
}

void Scene::AddModel(ModelPtr model)
{
	if (model) {
		sceneModels[(std::string)(*model)] = model;
	}
}
ModelPtr Scene::GetModel(const std::string& name) {
	if (sceneModels.find(name) != sceneModels.end())
		return sceneModels[name];

	return nullptr;
}

void Scene::SetModelActiveState(bool newState, const std::string& modelName)
{
	if (sceneModels.find(modelName) != sceneModels.end()) {
		sceneModels[modelName]->SetActive(newState);
	}
}



void Scene::SetActiveCamera(CameraPtr cam)
{
	if (cam)
		activeCamera = cam;
}

CameraPtr Scene::GetActiveCamera()
{
	return activeCamera;
}

void Scene::Draw()
{
	if (activeCamera) {
		for (auto modelPair : sceneModels) {
			//model won't be nullptr ever
			ModelPtr model = modelPair.second;
			model->Draw(activeCamera);
		}
	}
}

void Scene::Clear()
{
	activeCamera = nullptr;
	sceneModels.clear();
}
