#include "Collider.h"
#include "GameObject.h"

#include "Engine.h"
#include "OrbitBullet.h"


Collider::~Collider()
{
	engine->GetCollisionSystem()->RemoveCollider(this);
}

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
	this->size = size.Multiply(owner->transform.scale);
}

void Collider::SetOffset(const Vector2D& offset)
{
	this->offset = offset;
}


void Collider::SetLayer(int layer)
{
	this->layer = layer;
}

void Collider::SetIsTrigger(bool trigger)
{
	this->isTrigger = trigger;
}

int Collider::Layer() const
{
	return layer;
}

bool Collider::IsTrigger() const
{
	return isTrigger;
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
	Vector2D retSize = size;
	retSize.Multiply(owner->transform.scale);
	retSize.Multiply(scale);
	retSize *= engine->GetCamera()->GetZoom();
	return retSize;
}

Vector2D Collider::ComputedPosition() const
{
	Vector2D retPosition = owner->transform.position;
	retPosition += offset;
	return retPosition;
}

Vector2D Collider::Offset() const
{
	return offset;
}

bool Collider::Enable() const
{
	return enable;
}

void Collider::SetScale(const Vector2D& scale)
{
	this->scale = scale;
}

void Collider::SetEnableDebug(bool debug)
{
	this->isDebug = debug;
}

void Collider::SetEnable(bool enable)
{
	this->enable = enable;
}
