#include "Stair.h"




Stair::~Stair()
{
}

Stair::Stair(D3DXVECTOR3 position, float pposStop)
{
	init(position);
}

void Stair::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
}

const char * Stair::FileName()
{
	return "Resources/StaticObject/stair.png";
}

int Stair::TotalFrame()
{
	return 1;
}

int Stair::Row()
{
	return 1;
}

int Stair::Column()
{
	return 1;
}

float Stair::SecondPerFrame()
{
	return 1;
}
