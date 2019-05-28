#include "Brute.h"
Brute::~Brute()
{
}

Brute::Brute(D3DXVECTOR3 position)
{
	//mAnimation = new Animation("Resources/Enemy/Brute.png", 3, 1, 3, 0.25f);
	////this->vx = 0;
	////this->vy = 0;
	//Tag = Enemy;
	////mAnimation->SetPosition(position);
	//this->SetPosition(position);
	//Entity::SetWidth(mAnimation->GetWidth());
	//Entity::SetHeight(mAnimation->GetHeight());
	init(position);

}
void Brute::Update(float dt)
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


const char * Brute::FileName()
{
	return "Resources/Enemy/Brute.png";
}

int Brute::TotalFrame()
{
	return 2;
}

int Brute::Row()
{
	return 1;
}

int Brute::Column()
{
	return 2;
}

float Brute::SecondPerFrame()
{
	return 0.3f;
}



void Brute::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	////this->SetPosition(-100, 0);
	//die = 1;
	vx = 0;
	vy = 0;
	//Cho ra khỏi màn hình
	this->SetPosition(-100, -100);
}
