#pragma once

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	virtual void Init() {}

	virtual void Update(float delta) {}
	virtual void Render() {}
	virtual void Input() {}

	virtual void Destroy() {}

protected:
	bool enable = true;

};