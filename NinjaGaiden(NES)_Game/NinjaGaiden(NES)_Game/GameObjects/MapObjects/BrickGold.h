#pragma once
#include "Brick.h"

class BrickGold : public Brick
{
public:
    BrickGold(D3DXVECTOR3 position);
	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side); // Test 8/5

    ~BrickGold();
	D3DXVECTOR3 pos;
    virtual const char* FileName();
    virtual int TotalFrame();
    virtual int Row();
    virtual int Column();
    virtual float SecondPerFrame();
	
	void SetPos(D3DXVECTOR3); //Test 8/5
};