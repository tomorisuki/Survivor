#include "Collider.h"
#include "GameObject.h"

#include "Engine.h"

void Collider::Start()
{

}

void Collider::Update(float deltaTime)
{
}

void Collider::Render()
{
	if (isDebug) 
	{
		engine->GetRenderSystem()->RenderCollider(engine->GetCamera(), owner->transform, Size());
	}
}

void Collider::SetSize(const Vector2D& size)
{
	this->size = size;
}

void Collider::SetOffset(const Vector2D& offset)
{
	this->offset = offset;
}

Vector2D Collider::Size() const
{
	Vector2D retSize = size;
	retSize.Multiply(owner->transform.scale);
	retSize.Multiply(scale);
	return retSize;
}

Vector2D Collider::Offset() const
{
	return offset;
}

void Collider::SetScale(const Vector2D& scale)
{
	this->scale = scale;
}

void Collider::EnableDebug(bool debug)
{
	this->isDebug = debug;
}