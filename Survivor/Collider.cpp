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
		Transform transform;
		transform.position = owner->transform.position + offset;
		transform.previousPosition = owner->transform.previousPosition + offset;
		transform.scale = owner->transform.scale;
		engine->GetRenderSystem()->RenderCollider(engine->GetCamera(), transform, Size());
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

Vector2D Collider::ComputedSize() const
{
	Vector2D retSize = Size();
	retSize *= engine->GetCamera()->GetZoom();
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