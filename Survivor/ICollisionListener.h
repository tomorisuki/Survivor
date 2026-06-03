#pragma once
class ICollisionListener
{
public:

	virtual ~ICollisionListener() = default;

	virtual void OnCollision(class Collider* collider) = 0;


};

