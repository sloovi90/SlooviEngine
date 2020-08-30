#include "GameObject.h"

GameObject::GameObject(const std::string& name) noexcept
	:
	m_sName(name),
	m_bIsActive(true),
	m_iUuid(0)
{
}

void GameObject::SetTransform(const Transform& tranform) noexcept
{
	this->m_tTransform = tranform;
}

Transform& GameObject::GetTransform() noexcept
{
	return m_tTransform;
}

void GameObject::SetName(const std::string& name) noexcept
{
	m_sName = name;
}

const std::string& GameObject::GetName() const noexcept
{
	return m_sName;
}

void GameObject::SetActive(bool newState) noexcept
{
	m_bIsActive = newState;
}

bool GameObject::IsActive() const noexcept
{
	return m_bIsActive;
}

GameObjectPtr GameObject::Clone()
{
	return GameObjectPtr();
}

void GameObject::AddComponent(Component component)
{

	if (component != nullptr)
		m_vComponents.push_back(component);

}
