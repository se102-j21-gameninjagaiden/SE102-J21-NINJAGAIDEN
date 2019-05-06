#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingBeatState.h"

Player::Player()
{
	mAnimationStanding = new Animation("Resources/Ninja/standing.png", 1, 1, 1, 0, D3DCOLOR_XRGB(255, 163, 177));
    mAnimationJumping = new Animation("Resources/Ninja/jumping.png", 4, 1, 4, 0.25f, D3DCOLOR_XRGB(255, 163, 177));
    mAnimationRunning = new Animation("Resources/Ninja/running.png", 3, 1, 3, 0.15f, D3DCOLOR_XRGB(255, 163, 177));
	mAnimationStandingBeat = new Animation("Resources/Ninja/standingbeat.png", 3, 1, 3, 0.15f, D3DCOLOR_XRGB(255, 163, 177));
    mAnimationSitting= new Animation ("Resources/Ninja/sitting.png", 1, 1, 1, 0, D3DCOLOR_XRGB(255, 163, 177));
	mAnimationSittingBeat = new Animation("Resources/Ninja/sittingbeat.png", 3, 1, 3, 0.15f, D3DCOLOR_XRGB(255, 163, 177));
	this->mPlayerData = new PlayerData();
    this->mPlayerData->player = this;
    this->vx = 0;
    this->vy = 0;
    this->SetState(new PlayerStandingState(this->mPlayerData));

    allowJump = true;
}

Player::~Player()
{
}

void Player::Update(float dt)
{    
    mCurrentAnimation->Update(dt);

    if (this->mPlayerData->state)
    {
        this->mPlayerData->state->Update(dt);
    }

    Entity::Update(dt);
}

void Player::HandleKeyboard()
{
    if (this->mPlayerData->state)
    {
        this->mPlayerData->state->HandleKeyboard();
    }
}

void Player::OnKeyPressed(int key)
{
    if (key ==DIK_SPACE )
    {
        if (allowJump)
        {
            if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)
            {
                this->SetState(new PlayerJumpingState(this->mPlayerData));
            }

           // allowJump = false;
        }
		
    }
	if (key == DIK_Z)
	{
		if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing) //|| mCurrentState==PlayerState::Jumping)
		{
			this->SetState(new PlayerStandingBeatState(this->mPlayerData));
			
			
		}
	}
}

void Player::OnKeyUp(int key)
{
  //  if (key == VK_SPACE)
      //  allowJump = true;
}

void Player::SetReverse(bool flag)
{
    mCurrentReverse = flag;
}



void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    mCurrentAnimation->FlipVertical(mCurrentReverse);
    mCurrentAnimation->SetPosition(this->GetPosition());

    mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));
}

void Player::SetState(PlayerState *newState)
{
    delete this->mPlayerData->state;

    this->mPlayerData->state = newState;

    this->changeAnimation(newState->GetState());

    mCurrentState = newState->GetState();
}

RECT Player::GetBound()
{
    RECT rect;
    rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
    rect.right = rect.left + mCurrentAnimation->GetWidth();
    rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
    rect.bottom = rect.top + mCurrentAnimation->GetHeight();

    return rect;
}

void Player::changeAnimation(PlayerState::StateName state)
{
    switch (state)
    {
        case PlayerState::Running:
            mCurrentAnimation = mAnimationRunning;
            break;

        case PlayerState::Standing:
            mCurrentAnimation = mAnimationStanding;
            break;

        case PlayerState::Falling:
            mCurrentAnimation = mAnimationJumping;
            break;

        case PlayerState::Jumping:
            mCurrentAnimation = mAnimationJumping;
            break;
		case PlayerState ::StandingBeat:
			mCurrentAnimation = mAnimationStandingBeat;
			break;
		case PlayerState ::Sitting:
			mCurrentAnimation = mAnimationSitting;
			break;
		case PlayerState::SittingBeat:
			mCurrentAnimation = mAnimationSittingBeat;
			break;
    }

    this->width = mCurrentAnimation->GetWidth();
    this->height = mCurrentAnimation->GetHeight();
}

Player::MoveDirection Player::getMoveDirection()
{
    if (this->vx > 0)
    {
        return MoveDirection::MoveToRight;
    }
    else if (this->vx < 0)
    {
        return MoveDirection::MoveToLeft;
    }

    return MoveDirection::None;
}

PlayerState::StateName Player::getState()
{
    return mCurrentState;
}