#pragma once
#include "GameObject.h"

class Stair : public GameObject
{
public:
	Stair(D3DXVECTOR3 position, float posStop);
	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side); // Test 8/5
	const char* FileName();
	int TotalFrame();
	int Row();
	int Column();
	float SecondPerFrame();

	~Stair();
};

