#pragma once

#include "../../../GameComponents/Animation.h""
#include "../../Entity.h"
#include "../../DynamicGameObject/Player/Player.h"
#include "../../StaticGameObject/GameObject.h"
class Brute : public GameObject
{
private:
public:
	~Brute();

	Brute(D3DXVECTOR3 position);
	void Update(float dt);

	const char* FileName();
	int TotalFrame();
	int Row();
	int Column();
	float SecondPerFrame();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side); // Test 8/5

};