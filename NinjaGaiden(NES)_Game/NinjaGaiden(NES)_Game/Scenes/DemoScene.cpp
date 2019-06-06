#include "DemoScene.h"

DemoScene::DemoScene()
{
	LoadContent();
}

void DemoScene::LoadContent()
{
	level = 1;
	Sound::getInstance()->LoadAllSound();
	
	Sound::getInstance()->play("Level" + to_string(level), true,0,1);
	mMap = new GameMap(level);
	mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	mCamera->SetPosition(GameGlobal::GetWidth() / 2,
		GameGlobal::GetHeight() / 2);


	mMap->SetCamera(mCamera);
	mPlayer = new Player();

	mPlayer->SetPosition(50,	20);
	mPlayer->SetCamera(mCamera);
	gameUI = new GameUI(GameGlobal::GetCurrentDevice(), 16, GameGlobal::GetWidth(), GameGlobal::GetHeight());
	gameUI->initTimer(150);
}

void DemoScene::Update(float dt)
{

	if (IsKeyDown(DIK_Z))
	{
		mPlayer->OnKeyUp(DIK_Z);

		mPlayer->OnKeyPressed(DIK_Z);
	}
	if (IsKeyDown(DIK_C))
	{

		mPlayer->OnKeyUp(DIK_C);

		mPlayer->OnKeyPressed(DIK_C);
		
		
	
	}
	if (IsKeyDown(DIK_SPACE))
	{
		mPlayer->OnKeyUp(DIK_SPACE);
		mPlayer->OnKeyPressed(DIK_SPACE);
	}
#pragma region - UI update-
	gameUI->SetplayerMana(mPlayer->getPlayerMana());
	gameUI->Update(dt);
#pragma endregion
	checkRuleGame();





	mMap->Update(dt);

	mPlayer->HandleKeyboard();
	mPlayer->Update(dt);

	CheckCameraAndWorldMap();
}

void DemoScene::Draw()
{
	mMap->Draw();
	mPlayer->Draw();
	gameUI->drawTable();
	gameUI->drawScore();
}

void DemoScene::OnKeyDown(int keyCode)
{

}

void DemoScene::OnKeyUp(int keyCode)
{

}


int DemoScene::IsKeyDown(int KeyCode)
{
	return (GameGlobal::GetCurrentKeyState()[KeyCode] & 0x80) > 0;
}

void DemoScene::CheckCameraAndWorldMap()
{
	mCamera->SetPosition(mPlayer->GetPosition());

	if (mCamera->GetBound().left < 0)
	{
		//vi position cua camera ma chinh giua camera
		//luc nay o vi tri goc ben trai cua the gioi thuc
		mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().right > mMap->GetWidth())
	{
		//luc nay cham goc ben phai cua the gioi thuc
		mCamera->SetPosition(mMap->GetWidth() - mCamera->GetWidth() / 2,
			mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().top < 0)
	{
		//luc nay cham goc tren the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
	}

	if (mCamera->GetBound().bottom > mMap->GetHeight())
	{
		//luc nay cham day cua the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x,
			mMap->GetHeight() - mCamera->GetHeight() / 2);
	}
}

D3DXVECTOR2 DemoScene::InitPosPlayer()
{
	return D3DXVECTOR2(FrameWidth * 4,
		mMap->GetHeight() - FrameHeight * 3);
}



void DemoScene::checkRuleGame()
{


	/*su dung de kiem tra xem khi nao ninja khong dung tren 1 object hoac
	dung qua sat mep trai hoac phai cua object do thi se chuyen state la falling*/
	int widthBottom = 0;
	//mMap->GetListObject().at(3)->AddPosition(mPlayer->Ge)
	vector<Entity*> listCollisionWithPlayer, listCollisionWithWeaponPlayer;

	// Lấy danh sách có khả năng va chạm với Player
	mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionWithPlayer, mPlayer);
	// Lấy danh sách có khả năng va chạm với Weapon of Player
	//mMap->GetQuadTree()

	for (size_t i = 0; i < listCollisionWithPlayer.size(); i++)
	{
		



#pragma region - Collision with Wepaon
		if (mPlayer->mWeapon &&mPlayer->mWeapon->_Active)
		{
			for (int j = 0; j < mPlayer->mWeapon->GetWeapon().size(); j++)
			{
				if (mPlayer->mWeapon->GetWeapon()[j]->_Active)
				{
					Entity::CollisionReturn r2 = GameCollision::RecteAndRect(mPlayer->mWeapon->GetWeapon()[j]->GetBound(), listCollisionWithPlayer.at(i)->GetBound());
					if (r2.IsCollided)
					{
						if (listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::Enemy && listCollisionWithPlayer.at(i)->_Active == true)
						{
							listCollisionWithPlayer.at(i)->_Active == false;
							gameUI->SetplayerScore(gameUI->GetplayerScore() + 100); // Xét điểm tạm
							Sound::getInstance()->play("BeatEnemy", true, 0);
							mPlayer->e_Hit->_Active = true;
							mPlayer->e_Hit->SetPosition(listCollisionWithPlayer.at(i)->GetPosition());
							//listCollisionWithPlayer.at(i)->OnCollision()
							mPlayer->mWeapon->GetWeapon()[j]->_Active = false;
							mPlayer->mWeapon->GetWeapon()[j]->SetVx(0);
							mPlayer->mWeapon->GetWeapon()[j]->SetVy(0);
							mPlayer->mWeapon->SetVx(0);
							mPlayer->mWeapon->SetVy(0);
							mPlayer->mWeapon->_Active = false;

							listCollisionWithPlayer.at(i)->Hidden();
						}
						if (listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::Item)
						{
							if (listCollisionWithPlayer.at(i)->TagItem != Entity::ItemType::Container && listCollisionWithPlayer.at(i)->_Active == false)
							{

								mPlayer->mWeapon->GetWeapon()[j]->_Active = false;
								//mPlayer->mWeapon->GetWeapon()[j]->SetVx(0);
								//mPlayer->mWeapon->GetWeapon()[j]->SetVy(0);
								mPlayer->mWeapon->SetVx(0);
								mPlayer->mWeapon->SetVy(0);
								mPlayer->mWeapon->_Active = false;
							}

						}
						else
						{

						}
							listCollisionWithPlayer.at(i)->OnCollision();



					}
				}

			}
		   
		}
#pragma endregion

		Entity::CollisionReturn r = GameCollision::RecteAndRect(mPlayer->GetBound(),
			listCollisionWithPlayer.at(i)->GetBound());
		if (r.IsCollided)
		{
			//lay phia va cham cua Entity so voi Player
			Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, r);

			//lay phia va cham cua Player so voi Entity
			Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollisionWithPlayer.at(i), r);

#pragma region	-Update GUI theo luật game -
			if (listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::Enemy&&listCollisionWithPlayer.at(i)->_Active == true && mPlayer->invincible == false && mPlayer->getState() != PlayerState::StandingBeat &&  mPlayer->getState() != PlayerState::SittingBeat)
			{
				gameUI->SetplayerHP(gameUI->GetplayerHP() - 1);
				
				Sound::getInstance()->play("Injured", true, 0);
				
			}
			if (listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::Item && listCollisionWithPlayer.at(i)->_allowPlayerpick == true  )//&& mPlayer->getState()!=PlayerState::StandingBeat)
			{
				
				Sound::getInstance()->play("PickItem", true, 0);
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::BlueMana)
				{
					//gameUI->SetplayerScore(gameUI->Ge)
					gameUI->SetplayerMana(gameUI->GetplayerMana() + 5);
					mPlayer->setPlayerMana(gameUI->GetplayerMana());
					listCollisionWithPlayer.at(i)->Hidden();
				}
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::RedMana)
				{
					//gameUI->SetplayerScore(gameUI->Ge)
					gameUI->SetplayerMana(gameUI->GetplayerMana() + 10);
					mPlayer->setPlayerMana(gameUI->GetplayerMana());
					listCollisionWithPlayer.at(i)->Hidden();
				}

				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::BlueBonus)
				{
					//gameUI->SetplayerScore(gameUI->Ge)
					gameUI->SetplayerScore(gameUI->GetplayerScore() + 500);
					listCollisionWithPlayer.at(i)->Hidden();
				}
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::RedBonus)
				{
					//gameUI->SetplayerScore(gameUI->Ge)
					gameUI->SetplayerScore(gameUI->GetplayerScore() + 1000);
					listCollisionWithPlayer.at(i)->Hidden();
				}
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::RedHP)
				{
					//gameUI->SetplayerScore(gameUI->Ge)
					gameUI->SetplayerHP(gameUI->GetplayerHP() + 6);
					Sound::getInstance()->play("BonusHP", true, 0);
					listCollisionWithPlayer.at(i)->Hidden();
				}
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::ThrowingStar)
				{

					listCollisionWithPlayer.at(i)->SetPosition(-100, 14);
				
					mPlayer->mWeapon = new ThrowingStarWeapon(mPlayer->GetPosition());
					gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/ThrowingStarBox.png");



				}
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::WindmillStar)
				{
					listCollisionWithPlayer.at(i)->Hidden();

					mPlayer->mWeapon = new WindmillStarWeapon(mPlayer->GetPosition());
					gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/WindmillStarBox.png");
				}
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::Fire)
				{
					listCollisionWithPlayer.at(i)->Hidden();

					mPlayer->mWeapon = new FireWeapon(mPlayer->GetPosition());
					gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/FireBox.png");
				}
				if (listCollisionWithPlayer.at(i)->TagItem == Entity::ItemType::TimeFreeze)
				{

				}
			}
			if (mPlayer->getState() != PlayerState::StandingBeat && listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::Item)
			{
				goto ExitPlayerOnCollision;

			}
			if (mPlayer->getState() == PlayerState::StandingBeat && listCollisionWithPlayer.at(i)->_Active == true && listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::Enemy || mPlayer->getState() == PlayerState::SittingBeat && listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::Enemy)
			{
				gameUI->SetplayerScore(gameUI->GetplayerScore() + 100); // Sau nay xét Enemy Type để tính điểm
				Sound::getInstance()->play("BeatEnemy", true, 0);
			}
			else
			{

			}
		
#pragma endregion
			if ( (mPlayer->getState() != PlayerState::Climbing && listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::StairTop) 
				|| ( mPlayer->getState() != PlayerState::Climbing && listCollisionWithPlayer.at(i)->Tag == Entity::EntityTypes::StairBottom) 
				|| (mPlayer->getState() == PlayerState::Climbing && listCollisionWithPlayer[i]->Tag == Entity::EntityTypes::Grass))
			{
			 
			
				goto ExitPlayerOnCollision;
				//mPlayer->OnNoCollisionWithBottom();
			}
			
			mPlayer->OnCollision(listCollisionWithPlayer.at(i), r, sidePlayer);
		ExitPlayerOnCollision:






			//	listCollision.at(i)->OnCollision(mPlayer, r, sideImpactor);

				//kiem tra neu va cham voi phia duoi cua Player 
			if (sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomLeft
				|| sidePlayer == Entity::BottomRight)
			{

				//kiem cha do dai ma ninja tiep xuc phia duoi day
				int bot = r.RegionCollision.right - r.RegionCollision.left;

				if (bot > widthBottom)
					widthBottom = bot;
			}
			if (listCollisionWithPlayer[i]->Tag == Entity::EntityTypes::Grass)
			{
				widthBottom = Define::PLAYER_BOTTOM_RANGE_FALLING + 5; // cho khỏi bị rơi
			}
			/*if (sidePlayer == Entity::Top || sidePlayer == Entity::TopLeft
				|| sidePlayer == Entity::TopRight)
			{
				widthBottom = 8;
			}*/
			//if (listCollision.at(i)->Tag == Entity::EntityTypes::Enemy)
			//	break;
		}
	}

	// Chỉnh sửa các thông số theo luật game 
	if (gameUI->GetplayerHP() == 0 || CheckPositionPlayer())
	{
		Sound::getInstance()->play("Death", true, 0);
		Sound::getInstance()->stop("Level" + to_string(level) );
		//Sound::getInstance()->play("Death", true, 0);
		Sleep(2000);

		mPlayer->SetPosition(InitPosPlayer());
		mPlayer->SetState(new PlayerStandingState(mPlayer->mPlayerData));
		mPlayer->mWeapon = nullptr;
		gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/BoxWeapon.png");

		mMap->GetQuadTree()->Clear();
		mMap = new GameMap(level);

		Sound::getInstance()->play("Level"+ to_string(level), true, 0,1);

		mMap->SetCamera(mCamera);

		


		if (gameUI->GetLiveCount() > 0)
		{
			gameUI->SetLiveCount(gameUI->GetLiveCount() - 1);

			
			gameUI->SetplayerHP(MAX_HP);
			mPlayer->setPlayerMana(mPlayer->getPlayerMana() / 2);
			

			gameUI->initTimer(150);
		}
		else
		{
			
			gameUI->SetLiveCount(2);
			gameUI->SetplayerHP(MAX_HP);
			gameUI->SetplayerMana(0);

			gameUI->SetplayerScore(0);
			gameUI->initTimer(150);
			gameUI->_boxWeapon = new Sprite("Resources/Item_Effect/BoxWeapon.png");
			mPlayer->mWeapon = nullptr;
		}
	}
	if (mPlayer->GetPosition().x >= mMap->GetWidth())
	{
		level++;
		mMap = new GameMap(level);
		gameUI->SetplayerHP(MAX_HP);

		gameUI->initTimer(150);
		mPlayer->SetPosition(InitPosPlayer());
		mMap->SetCamera(mCamera);
	}
	
	//Neu ninja dung ngoai mep thi luc nay cho ninja rot xuong duoi dat    
	if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
	{
		mPlayer->OnNoCollisionWithBottom();
	}
}

int DemoScene::CheckPositionPlayer()
{
	if (mPlayer->GetPosition().y > mMap->GetHeight())
	{
		return 1;
	}

	return 0;
}
