#include "Weapon.h"



Weapon::Weapon()
{
	
}

Weapon::Weapon(D3DXVECTOR3 postition)
{
	_amount = 1;
}


Weapon::~Weapon()
{
}

void Weapon::Update(float dt)
{
}

D3DXVECTOR3 Weapon::GetPosWeaponAtPlayer()
{
	return PosWeaponAtPlayer;
}

bool Weapon::getDirection()
{
	return _direction;
}

void Weapon::SetDirection(bool direction)
{
	_direction = direction;
}

bool Weapon::getDirection2()
{
	return _direction2;
}

void Weapon::SetDirection2(bool direction)
{
	_direction2 = direction;
}

void Weapon::setBoundLimit(RECT bound)
{
	_boundLimit = bound;
}

RECT Weapon::getBoundLimit()
{
	return _boundLimit;
}

void Weapon::setBoundplayer(RECT bound)
{
	_boundPlayer = bound;
}

RECT Weapon::getBoundplayer()
{
	return _boundPlayer;
}

void Weapon::SetPosLimitAtMap(D3DXVECTOR3 posLimit)
{
	PosLimitAtMap = posLimit;
}

D3DXVECTOR3 Weapon::GetPosLimitAtMap()
{
	return PosLimitAtMap;
}

int Weapon::getAmount()
{
	return _amount;
}

void Weapon::setAmount(int amount)
{
	_amount = amount;
}

void Weapon::GetPositionPlayer(D3DXVECTOR3 posPlayer)
{
	PosWeaponAtPlayer = posPlayer;
}



void Weapon::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (_Active)
	{
		for (int i = 0; i < _Weapon.size(); i++)
		{
			_Weapon[i]->Draw(_Weapon[i]->GetPosition(), sourceRect, scale, transform, angle, rotationCenter, colorKey);

		}
	}
}

std::vector<GameObject*> Weapon::GetWeapon()
{
	return _Weapon;
}
