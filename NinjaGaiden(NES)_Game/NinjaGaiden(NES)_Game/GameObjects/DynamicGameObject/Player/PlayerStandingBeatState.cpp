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
		this->mPlayerData->player->SetVy(0);
		this->mPlayerData->player->SetVx(0);
	}
	//this->mPlayerData->player->SetVy(this->mPlayerData->player->GetVy());
	/*acceleratorY = 10;
	acceleratorX = 3;*/
	mTimePerFrame = 0.15;
	//this->mPlayerData->player->isUpdate = true;
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
	
	//if (mPlayerData->player->GetVy() <= -Define::PLAYER_MAX_JUMP_VELOCITY )
	/*if (mPlayerData->player->GetVy() >=0)
	{
		mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));

		return;
		
	}*/
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
		//mPlayerData->player->SetVy(0);
	//	if (IsKeyDown(DIK_LEFTARROW) || IsKeyDown(DIK_RIGHTARROW))
	//{
	//	this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
	//	return;
	//}
		
		//}
		//if (mPlayerData->player->GetVy() >= 0)
		//{
		//	//mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));

		//	return;
		//}
		//if (mPlayerData->player->GetVy() == 0)
		//{
			mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			return;
		//}
		/*else {
			mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
			return;
		}*/


	}
	else
	{
		mCurrentTotalTime += dt;
	}
}

void PlayerStandingBeatState::HandleKeyboard()
{
	/*if (IsKeyDown(DIK_LEFTARROW) || IsKeyDown(DIK_RIGHTARROW))
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}*/
	//if (IsKeyDown(DIK_RIGHTARROW))
	//{
	//	mPlayerData->player->SetReverse(false);

	//	isLeftOrRightKeyPressed = true;
	//	//di chuyen sang phai
	//	if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
	//	{
	//		this->mPlayerData->player->AddVx(acceleratorX);

	//		if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
	//		{
	//			this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
	//		}
	//	}
	//}
	//else if (IsKeyDown(DIK_LEFTARROW))
	//{
	//	mPlayerData->player->SetReverse(true);

	//	isLeftOrRightKeyPressed = true;
	//	//di chuyen sang trai
	//	if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
	//	{
	//		this->mPlayerData->player->AddVx(-acceleratorX);

	//		if (this->mPlayerData->player->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
	//		{
	//			this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	//		}
	//	}
	//}
	//else

	//{
	//	isLeftOrRightKeyPressed = false;
	//}
}

PlayerState::StateName PlayerStandingBeatState::GetState()
{
	return PlayerState::StandingBeat;
}
