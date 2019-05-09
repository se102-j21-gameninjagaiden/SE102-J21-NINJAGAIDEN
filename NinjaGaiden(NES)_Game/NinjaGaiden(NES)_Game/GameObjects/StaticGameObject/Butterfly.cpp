#include "Butterfly.h"

Butterfly::Butterfly(D3DXVECTOR3 position)
{
	init(position);
	SetPos(position); // xét tạm
}

void Butterfly::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::EntityTypes::None)
	{


		mAnimation = new Animation("Resources/normalbrick.png", 1, 1, 1, 1);
		SetPosition(pos);

		Entity::SetWidth(mAnimation->GetWidth());
		Entity::SetHeight(mAnimation->GetHeight());

		impactor->Tag = Entity::EntityTypes::Ninja;

	}
}


Butterfly::~Butterfly()
{
}

const char *Butterfly::FileName()
{
	return "Resources/StaticObject/Butterfly.png";
}

int Butterfly ::TotalFrame()
{
	return 2;
}

int Butterfly::Row()
{
	return 1;
}

int Butterfly::Column()
{
	return 2;
}

float Butterfly::SecondPerFrame()
{
	return 0.3f;
}

void Butterfly::SetPos(D3DXVECTOR3 pos)
{
	this->pos = pos;
}