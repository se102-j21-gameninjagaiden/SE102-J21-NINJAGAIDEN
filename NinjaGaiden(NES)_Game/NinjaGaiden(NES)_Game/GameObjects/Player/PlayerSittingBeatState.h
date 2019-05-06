#pragma once

//#include "PlayerState.h"
//#include "Player.h"

#include "Player.h"
#include "../Player/PlayerState.h"

class PlayerSittingBeatState : public PlayerState
{
public:
	PlayerSittingBeatState(PlayerData *playerData);
	~PlayerSittingBeatState();

	void Update(float dt);

	void HandleKeyboard();

	virtual StateName GetState();

protected:
	float                       mTimePerFrame, //thoi gian luan chuyen 1 frame
		mCurrentTotalTime; //tong thoi gian hien tai de thuc hien timeperframe
};

