#pragma once

#include "../../../GameComponents/Animation.h""
#include "../../Entity.h"
#include "../../DynamicGameObject/Player/Player.h"

class Swordman: public Entity
{
	~Swordman();
	void Update(float dt);
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	
	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side); // Test 8/5
};