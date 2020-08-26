#pragma once
#include <vector>
#include <string>
#include "Transform.h"
#include <cstdint>
#include <memory>

class IComponent;
typedef std::shared_ptr<IComponent> Component;

class GameObject;
typedef std::shared_ptr<GameObject> GameObjectPtr;

class GameObject {

	Transform m_tTransform;
	std::vector<Component> m_vComponents;
	std::string m_sName;
	bool m_bIsActive;
	uint32_t m_iUuid;

public:
	GameObject(const std::string& name) noexcept;

	void SetTransform(const Transform& tranform) noexcept;
	Transform& GetTransform()  noexcept;

	void SetName(const std::string& name) noexcept;
	const std::string& GetName() const noexcept;

	void SetActive(bool newState) noexcept;
	bool IsActive() const noexcept;

	GameObjectPtr Clone();








};