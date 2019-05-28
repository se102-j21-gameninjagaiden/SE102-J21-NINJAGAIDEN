#include "DemoScene.h"

DemoScene::DemoScene()
{
    LoadContent();
}

void DemoScene::LoadContent()
{
    //set mau backcolor cho scene o day la mau xanh
	mMap = new GameMap("Resources/MaxtrixMap.txt");
	
	mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	mCamera->SetPosition(GameGlobal::GetWidth() / 2,
		 GameGlobal::GetHeight() / 2);
	
		
	mMap->SetCamera(mCamera);
	mPlayer = new Player();
	
	mPlayer->SetPosition(FrameWidth*2,
		mMap->GetHeight() -FrameHeight*1.5);
	mPlayer->SetCamera(mCamera);
	gameUI = new GameUI(GameGlobal::GetCurrentDevice(), 16, GameGlobal::GetWidth(), GameGlobal::GetHeight());
	gameUI->initTimer(150);
}

void DemoScene::Update(float dt)
{
	if (IsKeyDown(DIK_LEFTARROW))
	{
		mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(-CAMERA_SPEED, 0, 0));
			if (mCamera->GetPosition().x <= mCamera->GetWidth() / 2)
			{
				mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);

			}
	}
	if (IsKeyDown(DIK_RIGHTARROW))
	{
		mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(CAMERA_SPEED, 0, 0));
		if (mCamera->GetPosition().x >= mMap->GetWidth() - GameGlobal::GetWidth() / 2)
		{
			mCamera->SetPosition(mMap->GetWidth() - GameGlobal::GetHeight() / 2, mCamera->GetPosition().y);

		}
	}
	/*if (IsKeyDown(DIK_UPARROW))
	{
		mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(0, -CAMERA_SPEED, 0));
	}
	if (IsKeyDown(DIK_DOWNARROW))
	{
		mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(0, CAMERA_SPEED, 0));
	}*/
	//
	if (IsKeyDown(DIK_Z))
	{
		mPlayer->OnKeyUp(DIK_Z);

		mPlayer->OnKeyPressed(DIK_Z);
	}
	if (IsKeyDown(DIK_SPACE))
	{
		mPlayer->OnKeyUp(DIK_SPACE);
		mPlayer->OnKeyPressed(DIK_SPACE);
	}

	checkCollision();



	
	
	mMap->Update(dt);
	mPlayer->HandleKeyboard();
	mPlayer->Update(dt);
	gameUI->Update(dt);

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
	/*if (keyCode == VK_LEFT)
	{
		mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(-10, 0, 0));
		if (mCamera->GetPosition().x <=mCamera->GetWidth()/2)
		{
			mCamera->SetPosition(mCamera->GetWidth()/2, mCamera->GetPosition().y);

		}
	}*/

	//if (keyCode == VK_RIGHT)
	//{
	//	mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(10, 0, 0));
	//	if (mCamera->GetPosition().x >= mMap->GetWidth()- GameGlobal::GetWidth()/2)
	//	{
	//		mCamera->SetPosition(mMap->GetWidth()-GameGlobal::GetHeight()/2, mCamera->GetPosition().y);
	//			
	//	}
	//
	//}

	//if (keyCode == VK_UP)
	//{
	//	mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(0, -10, 0));
	///*	if (mCamera->GetPosition().y >= mMap->GetHeight())
	//	{
	//		mCamera->SetPosition(mCamera->GetPosition().x,mCamera->GetHeight()/2);

	//	}*/
	//}

	//if (keyCode == VK_DOWN)
	//{
	//	mCamera->SetPosition(mCamera->GetPosition() + D3DXVECTOR3(0, 10, 0));
	//}
	
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

void DemoScene::checkCollision()
{
	/*su dung de kiem tra xem khi nao ninja khong dung tren 1 object hoac
	dung qua sat mep trai hoac phai cua object do thi se chuyen state la falling*/
	int widthBottom = 0;

	vector<Entity*> listCollision;

	mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mPlayer);
	
	for (size_t i = 0; i < listCollision.size(); i++)
	{
		Entity::CollisionReturn r = GameCollision::RecteAndRect(mPlayer->GetBound(),
			listCollision.at(i)->GetBound());

		if (r.IsCollided)
		{
			//lay phia va cham cua Entity so voi Player
			Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, r);

			//lay phia va cham cua Player so voi Entity
			Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollision.at(i), r);

			//goi den ham xu ly collision cua Player va Entity		
			if (listCollision.at(i)->Tag == Entity::EntityTypes::Enemy && mPlayer->invincible == false && mPlayer->getState() != PlayerState::StandingBeat &&  mPlayer->getState() != PlayerState::SittingBeat)
			{
				gameUI->SetplayerHP(-1);
			}
			mPlayer->OnCollision(listCollision.at(i), r, sidePlayer);
			if (mPlayer->getState() == PlayerState::StandingBeat && listCollision.at(i)->Tag == Entity::EntityTypes::Enemy || mPlayer->getState() == PlayerState::SittingBeat && listCollision.at(i)->Tag == Entity::EntityTypes::Enemy)
			{
				gameUI->SetplayerScore(100); // Sau nay xét Enemy Type để tính điểm

			}
			else
			{
				
			}
			
				
			
			
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
			//if (listCollision.at(i)->Tag == Entity::EntityTypes::Enemy)
			//	break;
		}
	}

	//Neu ninja dung ngoai mep thi luc nay cho ninja rot xuong duoi dat    
	if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
	{
		mPlayer->OnNoCollisionWithBottom();
	}
}