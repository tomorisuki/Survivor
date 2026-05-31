#pragma once

class Component 
{
public:
	
	class GameObject* owner = nullptr;

	void SetOwner(class GameObject* owner) {
		this->owner = owner;
	}

	virtual void Update(float delta) {}
	virtual void Render() {}
	virtual void Input() {}

public:
	//bool disable = true;
	bool enable = true;



};