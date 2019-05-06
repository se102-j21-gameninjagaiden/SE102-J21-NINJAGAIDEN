#include "PlayerFallingState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "../..//GameDefine/GameDefine.h"

PlayerFallingState::PlayerFallingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    acceleratorY = 10.0f;
    acceleratorX = 3.0f;

    if (this->mPlayerData->player->GetVx() == 0)
    {
        allowMoveX = false;
    }
    else
    {
        allowMoveX = true;
    }
}


PlayerFallingState::~PlayerFallingState()
{
}


void PlayerFallingState::Update(float dt)
{
    
     if (mPlayerData->player->GetVy() >= Define::PLAYER_MAX_JUMP_VELOCITY)
    {
		
		 mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
		 if (mPlayerData->player->GetPosition().y>=GameGlobal::GetHeight()-FrameHeight) // xét vị trí tạm
		 {

			
		

		 
			 mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			// mPlayerData->player->Set_allowJump();
			 
			 return;
		 }
		
    }
	else this->mPlayerData->player->AddVy(acceleratorY);
	
}

void PlayerFallingState::HandleKeyboard()
{
    if (IsKeyDown(DIK_RIGHTARROW))
    {
        mPlayerData->player->SetReverse(false);

        isLeftOrRightKeyPressed = true;
        //di chuyen sang phai
        if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(acceleratorX);

            if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }
    }
    else if (IsKeyDown(DIK_LEFTARROW))
    {
        mPlayerData->player->SetReverse(true);

        isLeftOrRightKeyPressed = true;
        //di chuyen sang trai
        if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(-acceleratorX);

            if (this->mPlayerData->player->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }
    }
    else
    {
        isLeftOrRightKeyPressed = false;    
    }
}

PlayerState::StateName PlayerFallingState::GetState()
{
    return PlayerState::Falling;
}
