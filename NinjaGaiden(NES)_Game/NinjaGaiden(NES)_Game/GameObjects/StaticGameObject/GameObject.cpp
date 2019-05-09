#include "GameObject.h"
#include "../../GameComponents/GameGlobal.h"


GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

bool GameObject::init(D3DXVECTOR3 position)
{
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

void GameObject::Update(float dt)
{
	mAnimation->Update(dt);
}

void GameObject::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void GameObject::OnCollision(Entity * impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
}



void GameObject::Draw(D3DXVECTOR2 transform)
{
	mAnimation->Draw(D3DXVECTOR3(transform.x, transform.y, 0));
}
