#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "../..//GameDefine/GameDefine.h"

PlayerJumpingState::PlayerJumpingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);

    acceleratorY = 5.0f;
    acceleratorX = 6.0f;

    noPressed = false;
}


PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::Update(float dt)
{
    this->mPlayerData->player->AddVy(acceleratorY);   

    if (mPlayerData->player->GetVy() >= 0)
    {
        mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));

        return;
    }

    if (noPressed)
    {
        if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
        {
            //player dang di chuyen sang ben trai      
            if (mPlayerData->player->GetVx() < 0)
            {
                this->mPlayerData->player->AddVx(acceleratorX);

                if (mPlayerData->player->GetVx() > 0)
                    this->mPlayerData->player->SetVx(0);
            }
        }
        else if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
        {
            //player dang di chuyen sang phai   
            if (mPlayerData->player->GetVx() > 0)
            {
                this->mPlayerData->player->AddVx(-acceleratorX);

                if (mPlayerData->player->GetVx() < 0)
                    this->mPlayerData->player->SetVx(0);
            }
        }
	
		
    }
}

void PlayerJumpingState::HandleKeyboard()
{
	//if (keys[VK_SHIFT])
	//{
	//	mPlayerData->player->SetState(new PlayerStandingBeatState(this->mPlayerData));
	//	return;
	//	noPressed = false;


	//}

    if (IsKeyDown(DIK_RIGHTARROW))
    {
        mPlayerData->player->SetReverse(false);

        //di chuyen sang phai
        if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(acceleratorX);

            if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }

        noPressed = false;
    }
    else if (IsKeyDown(DIK_LEFTARROW))
    {
        mPlayerData->player->SetReverse(true);

        //di chuyen sang trai
        if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
        {
            this->mPlayerData->player->AddVx(-acceleratorX);

            if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
            }
			noPressed = false;

        }
	

    }
    else
    {
        noPressed = true;
    }
}

PlayerState::StateName PlayerJumpingState::GetState()
{
    return PlayerState::Jumping;
}
