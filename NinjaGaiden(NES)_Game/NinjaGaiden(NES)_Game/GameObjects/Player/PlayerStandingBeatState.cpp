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
