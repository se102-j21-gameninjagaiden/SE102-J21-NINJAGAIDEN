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
	//vx -= 5 * dt;
	//Entity::Update(dt);
	/*relive += dt;
	if (die ==1 && relive >= 10)
	{
		this->SetPosition(200, 150);
		relive = 0;
		die = 0;
	}*/
	//if (die == 1)
	//{
	//	delete mAnimation;
	//}
	
	
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
	////this->SetPosition(-100, 0);
	//die = 1;
	vx = 0;
	vy = 0;
	//Cho ra khỏi màn hình
	this->SetPosition(-100, -100);
}
 