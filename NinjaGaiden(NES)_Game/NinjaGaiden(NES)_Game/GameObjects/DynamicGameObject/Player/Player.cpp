#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingBeatState.h"

Player::Player()
{
	//e_Hit = nullptr;
	mAnimationStanding = new Animation("Resources/Ninja/standing.png", 1, 1, 1, 0, D3DCOLOR_XRGB(255, 163, 177));
    mAnimationJumping = new Animation("Resources/Ninja/jumping.png", 4, 1, 4, 0.25f, D3DCOLOR_XRGB(255, 163, 177));
    mAnimationRunning = new Animation("Resources/Ninja/running.png", 3, 1, 3, 0.15f, D3DCOLOR_XRGB(255, 163, 177));
	mAnimationStandingBeat = new Animation("Resources/Ninja/standingbeat.png", 3, 1, 3, 0.15f, D3DCOLOR_XRGB(255, 163, 177));
    mAnimationSitting= new Animation ("Resources/Ninja/sitting.png", 1, 1, 1, 0, D3DCOLOR_XRGB(255, 163, 177));
	mAnimationSittingBeat = new Animation("Resources/Ninja/sittingbeat.png", 3, 1, 3, 0.15f, D3DCOLOR_XRGB(255, 163, 177));
	mAnimationDying = new Animation("Resources/Ninja/dying.png", 1, 1, 1, 0, D3DCOLOR_XRGB(255, 163, 177));
	this->mPlayerData = new PlayerData();
    this->mPlayerData->player = this;
    this->vx = 0;
    this->vy = 0;
    this->SetState(new PlayerStandingState(this->mPlayerData));
	invincible = false;
    allowJump = false;
	allowHit = false;
	isJummping = false;
	Tag = Ninja;
	InvincibleTime = 100;
	e_Hit = new ExplosionHit();
	e_Hit->Active = false;
	
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	
	if (e_Hit->Active)
	{ 
		e_Hit->Update(dt);
		if (e_Hit->timeSpawn >= e_Hit->Column()* e_Hit->SecondPerFrame())
		{
			e_Hit->Active = false;
		}
		else
		{
			e_Hit->timeSpawn += dt;
		}
	}
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
            if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing || mCurrentState==PlayerState::Sitting)
            {
                this->SetState(new PlayerJumpingState(this->mPlayerData));
            }

            allowJump = false;
        }
		
    }
	if (key == DIK_Z)
	{
		if (allowHit)
		{
			if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)// || mCurrentState == PlayerState::Falling || mCurrentState == PlayerState::Jumping)
			{
				this->SetState(new PlayerStandingBeatState(this->mPlayerData));


			}
		}
		allowHit = false;
	}
}

void Player::OnKeyUp(int key)
{
    if (key == DIK_SPACE)
        allowJump = true;
	if (key == DIK_Z)
		allowHit = true;

}

void Player::SetReverse(bool flag)
{
    mCurrentReverse = flag;
}

void Player::SetCamera(Camera *camera)
{
	this->mCamera = camera;
}

void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    mCurrentAnimation->FlipVertical(mCurrentReverse);
    mCurrentAnimation->SetPosition(this->GetPosition());

   
	if (mCamera)
	{
		
		D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
			GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
		if (e_Hit->Active)
		{
			e_Hit->Draw(e_Hit->GetPosition(),RECT(),D3DXVECTOR2(),trans);
		}
		if (invincible)
		{
			InvincibleTime--;
			if (InvincibleTime % 2 == 0 && InvincibleTime >=0)
			{
				mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
			}
			if (InvincibleTime <= 0)
			{
				invincible=false;
				InvincibleTime = 40;
			}
		}
		else mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
	}
	else
	{
		if (e_Hit->Active)
		{
			e_Hit->Draw(e_Hit->GetPosition());
		}
		 mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));
	}
}

void Player::SetState(PlayerState *newState)
{
	allowMoveLeft = true;
	allowMoveRight = true;
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
		case PlayerState::Die:
			mCurrentAnimation = mAnimationDying;
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
void Player::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	 this->mPlayerData->state->OnCollision(impactor, side, data);
}
void Player::OnNoCollisionWithBottom()
{
	if (mCurrentState != PlayerState::Jumping && mCurrentState != PlayerState::Falling && mCurrentState != PlayerState::StandingBeat)
	{
		this->SetState(new PlayerFallingState(this->mPlayerData));
	}
}
PlayerState::StateName Player::getState()
{
    return mCurrentState;
}