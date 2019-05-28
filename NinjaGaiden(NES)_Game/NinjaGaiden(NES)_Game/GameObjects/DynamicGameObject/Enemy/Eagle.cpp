#include "Eagle.h"

Eagle::Eagle(D3DXVECTOR3 position)
{
	init(position);
}

void Eagle::Update(float dt)
{
	GameObject::Update(dt);
}

const char * Eagle::FileName()
{
	return "Resources/Enemy/Eagle.png";
}

int Eagle::TotalFrame()
{
	return 2;
}

int Eagle::Row()
{
	return 1;
}

int Eagle::Column()
{
	return 2;
}

float Eagle::SecondPerFrame()
{
	return 0.3f;
}

void Eagle::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	////this->SetPosition(-100, 0);
	//die = 1;
	vx = 0;
	vy = 0;
	//Cho ra khỏi màn hình
	this->SetPosition(-100, -100);
}
