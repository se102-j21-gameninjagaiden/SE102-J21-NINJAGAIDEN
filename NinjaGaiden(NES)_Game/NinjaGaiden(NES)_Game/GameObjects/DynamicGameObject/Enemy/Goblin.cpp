#include "Goblin.h"
Goblin::~Goblin()
{
}

Goblin::Goblin(D3DXVECTOR3 position)
{
	//mAnimation = new Animation("Resources/Enemy/Goblin.png", 3, 1, 3, 0.25f);
	////this->vx = 0;
	////this->vy = 0;
	//Tag = Enemy;
	////mAnimation->SetPosition(position);
	//this->SetPosition(position);
	//Entity::SetWidth(mAnimation->GetWidth());
	//Entity::SetHeight(mAnimation->GetHeight());
	init(position);

}
void Goblin::Update(float dt)
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


const char * Goblin::FileName()
{
	return "Resources/Enemy/Goblin.png";
}

int Goblin::TotalFrame()
{
	return 3;
}

int Goblin::Row()
{
	return 1;
}

int Goblin::Column()
{
	return 3;
}

float Goblin::SecondPerFrame()
{
	return 0.3f;
}



void Goblin::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	////this->SetPosition(-100, 0);
	//die = 1;
	vx = 0;
	vy = 0;
	//Cho ra khỏi màn hình
	this->SetPosition(-100, -100);
}
