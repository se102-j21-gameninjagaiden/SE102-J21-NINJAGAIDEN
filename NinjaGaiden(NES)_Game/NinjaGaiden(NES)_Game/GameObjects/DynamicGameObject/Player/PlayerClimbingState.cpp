#include "PlayerClimbingState.h"

PlayerClimbingState::PlayerClimbingState(PlayerData * playerData)
{
	this->mPlayerData = playerData;
	acceleratorY = 3;
	this->mPlayerData->player->SetVy(0);
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->isOnStair = true;
	this->mPlayerData->player->isUpdate = true;
}

PlayerClimbingState::~PlayerClimbingState()
{
}

void PlayerClimbingState::Update(float dt)
{
}

void PlayerClimbingState::HandleKeyboard()
{
	if (IsKeyDown(DIK_UPARROW) && this->mPlayerData->player->isOnStair == true)
	{
		this->mPlayerData->player->AddVy(-acceleratorY);
		this->mPlayerData->player->isUpdate = true;
		return;
	}
	
	if (IsKeyDown(DIK_DOWNARROW) && this->mPlayerData->player->isOnStair == true)
	{
		this->mPlayerData->player->AddVy(acceleratorY);
		this->mPlayerData->player->isUpdate = true;
	}
	else
	{
		this->mPlayerData->player->SetVy(0);
	}
	if (IsKeyDown(DIK_SPACE))
	{
		this->mPlayerData->player->AddPosition(-4, 0);
		this->mPlayerData->player->SetState(new PlayerJumpingState(this->mPlayerData));
		return;
	}
	//this->mPlayerData->player->
}

void PlayerClimbingState::OnCollision(Entity * impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::EntityTypes::Stair)
	{
		this->mPlayerData->player->isOnStair = true;
	}
	else
	{
		this->mPlayerData->player->isOnStair = false;
	}
	if (this->mPlayerData->player->GetPosition().y <= impactor->GetBound().top)
	{
		this->mPlayerData->player->AddVy(acceleratorY);
	}
	
}

PlayerState:: StateName PlayerClimbingState::GetState()
{
	return PlayerState::StateName::Climbing;
}
