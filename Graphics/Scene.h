#pragma once
#include <map>
#include <memory>
#include <string>
#include "Model.h"
#include "GLProgram.h"
#include "Camera.h"



typedef std::map<std::string, ModelPtr> modelsMap;
class Scene;
typedef std::shared_ptr<Scene> ScenePtr;

class Scene {
	std::string sceneName;
	modelsMap sceneModels;
	CameraPtr activeCamera;
	
public:
	Scene(const std::string& name);
	void AddModel(ModelPtr model);
	ModelPtr GetModel(const std::string& name);
	void SetModelActiveState(bool newState,const std::string& modelName);
	void SetActiveCamera(CameraPtr cam);
	CameraPtr GetActiveCamera();
	void Draw();
	void Clear();


};