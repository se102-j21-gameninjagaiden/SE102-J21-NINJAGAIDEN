#include "GameObject.h"
#include "../../GameComponents/GameGlobal.h"


GameObject::GameObject()
{
	
}

GameObject::GameObject(D3DXVECTOR3 position, const char* filename, int totalFrame, int row, int colum, int seconeFrame )
{
	_Active = true;
	mAnimation = new Animation(filename, totalFrame, row, colum, seconeFrame);
	SetPosition(position);
	Entity::SetWidth(mAnimation->GetWidth());
	Entity::SetHeight(mAnimation->GetHeight());
	
	
}

GameObject::~GameObject()
{

}

bool GameObject::init(D3DXVECTOR3 position)
{
	_Active = true;
	_allowPlayerpick = false;
	mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());

	SetPosition(position);

	Entity::SetWidth(mAnimation->GetWidth());
	Entity::SetHeight(mAnimation->GetHeight());


	return true;
}

void GameObject::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
}

const char * GameObject::FileName()
{
	return nullptr;
}

int GameObject::TotalFrame()
{
	return 0;
}

int GameObject::Row()
{
	return 0;
}

int GameObject::Column()
{
	return 0;
}

float GameObject::SecondPerFrame()
{
	return 0.0f;
}



void GameObject::Update(float dt)
{
	if (_Active)
	{
		mAnimation->Update(dt);
	}
	//vx -= 5 * dt;
	Entity::Update(dt);
}

void GameObject::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (this->_Active)
	{
		mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
	}
}

//int GameObject::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
//{
//	return 0;
//}



void GameObject::Draw(D3DXVECTOR2 transform)
{
	if (this->_Active)
	{
		mAnimation->Draw(D3DXVECTOR3(transform.x, transform.y, 0));
	}
}

void GameObject::Hidden()
{
	this->_Active = false;
	vx = 0;
	vy = 0;
	this->SetPosition(-100, 0);
}

void GameObject::OnCollision()
{
	_Active = false;
	vx = 0;
	vy = 0;
}
