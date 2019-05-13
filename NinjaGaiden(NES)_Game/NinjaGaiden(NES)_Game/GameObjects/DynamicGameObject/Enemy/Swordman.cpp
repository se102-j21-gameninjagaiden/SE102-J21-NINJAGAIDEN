#include "Swordman.h"

Swordman::~Swordman()
{
}

Swordman::Swordman(D3DXVECTOR3 position)
{
	//mAnimation = new Animation("Resources/Enemy/Swordman.png", 3, 1, 3, 0.25f);
	////this->vx = 0;
	////this->vy = 0;
	//Tag = Enemy;
	////mAnimation->SetPosition(position);
	//this->SetPosition(position);
	//Entity::SetWidth(mAnimation->GetWidth());
	//Entity::SetHeight(mAnimation->GetHeight());
	init(position);

}
void Swordman::Update(float dt)
{
	GameObject::Update(dt);
	vx -= 5 * dt;
	Entity::Update(dt);
}


const char * Swordman::FileName()
{
	return "Resources/Enemy/Swordman.png";
}

int Swordman::TotalFrame()
{
	return 3;
}

int Swordman::Row()
{
	return 1;
}

int Swordman::Column()
{
	return 3;
}

float Swordman::SecondPerFrame()
{
	return 0.3f;
}



void Swordman::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
}
