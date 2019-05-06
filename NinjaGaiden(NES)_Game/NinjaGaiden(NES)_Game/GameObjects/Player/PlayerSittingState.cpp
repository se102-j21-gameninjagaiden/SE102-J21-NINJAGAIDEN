//#include "PlayerStandingState.h"
//#include "Player.h"
//#include "PlayerFallingState.h"
//#include "../../GameDefines/GameDefine.h"
#include "Player.h"
#include "PlayerSittingState.h"
#include "../..//GameDefine/GameDefine.h"
#include "PlayerStandingState.h"
#include "PlayerSittingBeatState.h"

PlayerSittingState::PlayerSittingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;

	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}


PlayerSittingState::~PlayerSittingState()
{
}

void PlayerSittingState::Update(float dt)
{

}

void PlayerSittingState::HandleKeyboard()
{
	if (IsKeyDown(DIK_LEFTARROW) || IsKeyDown(DIK_RIGHTARROW))
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
	if (IsKeyDown(DIK_UPARROW))
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
	if (IsKeyDown(DIK_Z))
	{
		this->mPlayerData->player->SetState(new PlayerSittingBeatState(this->mPlayerData));
		return;
	}
}

PlayerState::StateName PlayerSittingState::GetState()
{
	return PlayerState::Sitting;
}
