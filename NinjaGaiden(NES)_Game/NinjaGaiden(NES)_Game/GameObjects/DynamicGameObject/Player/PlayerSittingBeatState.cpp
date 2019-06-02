
#include "PlayerStandingBeatState.h"
#include "PlayerStandingState.h"
#include "PlayerSittingBeatState.h"
PlayerSittingBeatState::PlayerSittingBeatState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	mTimePerFrame = 0.25;
	//this->mPlayerData->player->isUpdate = true;
}


PlayerSittingBeatState::~PlayerSittingBeatState()
{
}

void PlayerSittingBeatState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
	{
		if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active)
		{
			//this->mPlayerData->player->Tag = Entity::EntityTypes::None;
			this->mPlayerData->player->e_Hit = new ExplosionHit(impactor->GetPosition());

			impactor->OnCollision();

		}
		if (impactor->Tag == Entity::EntityTypes::Item)
		{



			impactor->OnCollision();
			//impactor->Hidden();
		}
		break;
	}

	case Entity::Right:
	{

		if (impactor->Tag == Entity::EntityTypes::Enemy && impactor->_Active==true)
		{

			
			this->mPlayerData->player->e_Hit = new ExplosionHit(impactor->GetPosition());
			//	this->mPlayerData->player->e_Hit->Draw(impactor->GetPosition());

			impactor->OnCollision();

		}
		if (impactor->Tag == Entity::EntityTypes::Item)
		{



			impactor->OnCollision();
			//impactor->Hidden();
		}
		break;
	}

	case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
	{/*
		this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
		this->mPlayerData->player->SetVy(0);*/
		if (impactor->Tag == Entity::EntityTypes::Enemy)
		{

		}
		if (impactor->Tag == Entity::EntityTypes::Item)
		{


			impactor->OnCollision();
			//impactor->Hidden();
		}
		break;
	}

	case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
	{

		if (impactor->Tag == Entity::EntityTypes::Enemy)
		{

		}
		if (impactor->Tag == Entity::EntityTypes::Item)
		{

			impactor->OnCollision();
			//impactor->Hidden();
		}
		else
		{
			//	this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);


		}
	}

	default:
		break;
	}
}

void PlayerSittingBeatState::Update(float dt)
{
	if (mCurrentTotalTime >= mTimePerFrame * 3)
	{

		mCurrentTotalTime = 0;
		mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;


	}
	else
	{
		mCurrentTotalTime += dt;
	}
}

void PlayerSittingBeatState::HandleKeyboard()
{
	if (IsKeyDown(DIK_LEFTARROW) || IsKeyDown(DIK_RIGHTARROW))
	{
		
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
}

PlayerState::StateName PlayerSittingBeatState::GetState()
{
	return PlayerState::SittingBeat;
}
