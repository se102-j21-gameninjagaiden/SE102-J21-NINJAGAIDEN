#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerFallingState.h"

#include "../..//GameDefine/GameDefine.h"
#include "PlayerSittingState.h"

PlayerStandingState::PlayerStandingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}


PlayerStandingState::~PlayerStandingState()
{
}

void PlayerStandingState::Update(float dt)
{

}

void PlayerStandingState::HandleKeyboard()
{
	if (IsKeyDown(DIK_DOWNARROW))
	{
		this->mPlayerData->player->SetState(new PlayerSittingState(this->mPlayerData));
		return;
	}
    if ( IsKeyDown(DIK_LEFTARROW)|| IsKeyDown(DIK_RIGHTARROW))
    {
        this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
        return;
    }
	
}

PlayerState::StateName PlayerStandingState::GetState()
{
    return PlayerState::Standing;
}
