#pragma once

#include "PlayerState.h"
#include "Player.h"

class PlayerStandingBeatState : public PlayerState
{
public:
	PlayerStandingBeatState(PlayerData *playerData);
	~PlayerStandingBeatState();

	void Update(float dt);

	void HandleKeyboard();

	virtual StateName GetState();

protected:
	float                       mTimePerFrame, //thoi gian luan chuyen 1 frame
		mCurrentTotalTime; //tong thoi gian hien tai de thuc hien timeperframe
};

