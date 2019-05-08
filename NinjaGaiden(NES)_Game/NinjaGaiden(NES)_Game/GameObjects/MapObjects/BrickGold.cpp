#include "BrickGold.h"

BrickGold::BrickGold(D3DXVECTOR3 position)
{
    init(position);
	SetPos(position); // xét tạm
}

void BrickGold::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if(impactor->Tag == Entity:: EntityTypes::None)
	{
		
		
		mAnimation = new Animation("Resources/normalbrick.png", 1, 1, 1, 1);
		SetPosition(pos);

		Entity::SetWidth(mAnimation->GetWidth());
		Entity::SetHeight(mAnimation->GetHeight());
		impactor->Tag = Entity::EntityTypes::Ninja;
	}
}


BrickGold::~BrickGold()
{
}

const char * BrickGold::FileName()
{
    return "Resources/goldbrick.png";
}

int BrickGold::TotalFrame()
{
    return 4;
}

int BrickGold::Row()
{
    return 1;
}

int BrickGold::Column()
{
    return 4;
}

float BrickGold::SecondPerFrame()
{
    return 0.3f;
}

void BrickGold::SetPos(D3DXVECTOR3 pos)
{
	this->pos = pos;
}