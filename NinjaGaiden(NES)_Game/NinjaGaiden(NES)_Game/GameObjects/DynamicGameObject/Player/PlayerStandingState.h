#pragma once
#include "PlayerState.h"

class PlayerStandingState : public PlayerState
{
public:
    PlayerStandingState(PlayerData *playerData);
    ~PlayerStandingState();

    void Update(float dt);

    void HandleKeyboard();

    virtual StateName GetState();

protected:
};

