#include "PlayerStandingBeatState.h"
#include"PlayerStandingState.h"
PlayerStandingBeatState::PlayerStandingBeatState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
//	this->mPlayerData->player->SetVx(0);
	
	if (this->mPlayerData->player->isJummping)
	{
		this->mPlayerData->player->AddVy(6);
		//this->mPlayerData->player->isJummping = false;

	}
	else
	{
		//this->mPlayerData->player->SetVy(0);
		this->mPlayerData->player->SetVx(0);
	}
	//this->mPlayerData->player->SetVy(this->mPlayerData->player->GetVy());
	/*acceleratorY = 10;
	acceleratorX = 3;*/
	mTimePerFrame = 0.15;
	
	Sound::getInstance()->play("Beat", true, 0);
	
	//this->mPlayerData->player->isUpdate = true;
}


PlayerStandingBeatState::~PlayerStandingBeatState()
{
	//Sound::getInstance()->stop("Best");
}

void PlayerStandingBeatState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Static)
	{
		this->mPlayerData->player->SetVx(0);
	}
	switch (side)
	{
	case Entity::Left:
	{
		if (impactor->Tag == Entity::EntityTypes::Enemy&& impactor->_Active && this->mPlayerData->player->GetReserse())
		{
			//this->mPlayerData->player->Tag = Entity::EntityTypes::None;
		
			this->mPlayerData->player->e_Hit = new ExplosionHit(impactor->GetPosition());
			impactor->OnCollision(this->mPlayerData->player, data, Entity::SideCollisions::Right);

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
	
		if (impactor->Tag==Entity::EntityTypes::Enemy && impactor->_Active == true && ! this->mPlayerData->player->GetReserse())
		{
		
			this->mPlayerData->player->e_Hit = new ExplosionHit(impactor->GetPosition());
		
			impactor->Hidden();
		}
		if (impactor->Tag == Entity::EntityTypes::Item)
		{

			

			impactor->OnCollision();
			//impactor->Hidden();
		}
		break;
	}

	case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
	{
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
			this->mPlayerData->player->isJummping = false;
		//	this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			this->mPlayerData->player->SetVy(0);

			
		}
	}

	default:
		break;
	}

}

void PlayerStandingBeatState::Update(float dt)
{
	
	
	if (this->mPlayerData->player->isJummping)
	{
		this->mPlayerData->player->AddVy(6);
		if (this->mPlayerData->player->GetVy() >= Define::PLAYER_MAX_JUMP_VELOCITY)
		{
			this->mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
		}
		//this->mPlayerData->player->isJummping = false;

	}
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
	
}

PlayerState::StateName PlayerStandingBeatState::GetState()
{
	return PlayerState::StandingBeat;
}
