#include "WindmillStarWeapon.h"

WindmillStarWeapon::WindmillStarWeapon(D3DXVECTOR3 position)
{
	GameObject  *object = new GameObject(position, "Resources/Item_Effect/WindmillStar.png", 1, 1, 1, 1);
	flag = 1;


	_Weapon.push_back(object);
	this->SetPosition(position);
	_Weapon[0]->SetPosition(position);
	this->SetWidth(_Weapon[0]->GetWidth());
	this->SetHeight(_Weapon[0]->GetHeight());
	this->TagWeapon = Entity::WeaponType::WindmillStarWeapon;
}

WindmillStarWeapon::~WindmillStarWeapon()
{
}

void WindmillStarWeapon::Update(float dt)
{
	if (posX >= _boundLimit.right || posX <= _boundLimit.left  || posY <= _boundLimit.top)
	{
		this->SetPosition(GetPosWeaponAtPlayer());
		vx = 0;
		vy = 0;
		_Active = false;
	}
	if (_Active)
	{
		if (this->vx >= 40)
		{
			int a = (GetPosWeaponAtPlayer().y - posY) / (GetPosWeaponAtPlayer().x - posX);
			int b = posY - posX * a;
			if (!_direction)
			{
				this->vx += 5;
				this->vy = - (a * vx + b);
			}
			else
			{

				this->vx -= 5;
				this->vy = a * vx + b;
			}
		}
		else
		{
			if (!_direction)
			{
				this->vx += 5;
				
			}
			else
			{
				this->vx -= 5;
				

			}
		}
		

		Entity::Update(dt);

		
		//GetPosWeaponAtPlayer().y
		

		_Weapon[0]->SetPosition(this->GetPosition());
	}
	else {
		this->SetPosition(GetPosWeaponAtPlayer());
	}
}
