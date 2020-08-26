#pragma once
#include <memory>

class IComponent;
typedef std::shared_ptr<IComponent> Component;

class IComponent {

public:
	virtual Component Clone() const  = 0;
	virtual void Update() = 0;


};