#include "Panther.h"

Panther::Panther(D3DXVECTOR3 position)
{
	init(position);
}

void Panther::Update(float dt)
{
	GameObject::Update(dt);
}

const char * Panther::FileName()
{
	return "Resources/Enemy/Panther.png";
}

int Panther::TotalFrame()
{
	return 2;
}

int Panther::Row()
{
	return 1;
}

int Panther::Column()
{
	return 2;
}

float Panther::SecondPerFrame()
{
	return 0.3f;
}

void Panther::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	////this->SetPosition(-100, 0);
	//die = 1;
	vx = 0;
	vy = 0;
	//Cho ra khỏi màn hình
	this->SetPosition(-100, -100);
}
