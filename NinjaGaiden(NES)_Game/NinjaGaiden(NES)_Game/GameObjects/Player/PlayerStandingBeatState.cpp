#include "PlayerStandingBeatState.h"
#include"PlayerStandingState.h"
PlayerStandingBeatState::PlayerStandingBeatState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
	
	mTimePerFrame = 0.15;
}


PlayerStandingBeatState::~PlayerStandingBeatState()
{
}

void PlayerStandingBeatState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	switch (side)
	{
	case Entity::Left:
	{
		if (impactor->Tag == Entity::EntityTypes::Brick)
		{
			this->mPlayerData->player->Tag = Entity::EntityTypes::None;

			impactor->OnCollision(this->mPlayerData->player, data, Entity::SideCollisions::Right);

		}
		break;
	}

	case Entity::Right:
	{
	
		if (impactor->Tag==Entity::EntityTypes::Brick)
		{
			this->mPlayerData->player->Tag = Entity::EntityTypes::None;

			impactor->OnCollision(this->mPlayerData->player,data,Entity::SideCollisions::Left);
			
		}
		break;
	}

	case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
	{/*
		this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
		this->mPlayerData->player->SetVy(0);*/
		break;
	}

	case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
	{
		//this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
	}

	default:
		break;
	}

}

void PlayerStandingBeatState::Update(float dt)
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

void PlayerStandingBeatState::HandleKeyboard()
{
	if (IsKeyDown(DIK_LEFTARROW) || IsKeyDown(DIK_RIGHTARROW))
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
}

PlayerState::StateName PlayerStandingBeatState::GetState()
{
	return PlayerState::StandingBeat;
}
