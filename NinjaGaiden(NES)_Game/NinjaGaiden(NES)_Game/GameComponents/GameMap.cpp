﻿#include "GameMap.h"

void GameMap::LoadMap( const char *filepath)
{
	fstream fs(filepath);
	//fs >> mtotalTile;
	fs >> mtotalTile>> mrowCount >> mcolumnCount;
	matrixTile = new int *[mrowCount];
	for (int rowIndex = 0; rowIndex < mrowCount; rowIndex++)
	{
		matrixTile[rowIndex] = new int[mcolumnCount];
		for (int columIndex = 0; columIndex < mcolumnCount; columIndex++)
		{
			fs >> matrixTile[rowIndex][columIndex];
		}
	}
	fs.close();
	mTileMap = new Sprite("Resources/tileSet.png");

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth();
	r.bottom = this->GetHeight();

	mQuadTree = new QuadTree(1, r);
	// Khởi tạo các viên gạch
	//khoi tao cac khoi Brick (vien gach)
#pragma region -BRICK-
	for (int i = 0; i <10 ; i++)
	{
		D3DXVECTOR3 position((13+i*2)*FrameWidth + FrameWidth/2,5*FrameHeight + FrameHeight/2-20,0 );
			//fstream fs("Brick");
		Brick *brick = nullptr;
		brick = new BrickGold(position);
		brick->Tag = Entity::EntityTypes::Brick;
		
		mListBricks.push_back(brick);
		if (brick)
			mQuadTree->insertEntity(brick);
	
	}
	
#pragma endregion
#pragma region -OBJECTGROUP, STATIC OBJECT-

	//for (size_t i = 0; i < mMap->GetNumObjectGroups(); i++)
	//{
	//	const Tmx::ObjectGroup *objectGroup = mMap->GetObjectGroup(i);

	//	for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
	//	{
	//		//lay object group chu khong phai layer
	//		//object group se chua nhung body
	//		Tmx::Object *object = objectGroup->GetObjects().at(j);

	//		Entity *entity = new Entity();
	//		entity->SetPosition(object->GetX() + object->GetWidth() / 2,
	//			object->GetY() + object->GetHeight() / 2);
	//		entity->SetWidth(object->GetWidth());
	//		entity->SetHeight(object->GetHeight());
	//		entity->Tag = Entity::EntityTypes::Static;

	//		mQuadTree->insertEntity(entity);
	//	}
	//}
	fstream f("Resources/StaticObjectMap.txt");
	int widthObject, heightObject, idX_Object, idY_Object;
	//f >> widthObject;
	f >> widthObject >> heightObject >> idX_Object >> idY_Object;
	f.close();
	Entity *entity = new Entity();
	entity->SetPosition(idX_Object + widthObject / 2, idY_Object*FrameHeight + heightObject / 2);
	entity->SetWidth(widthObject);
	entity->SetHeight(heightObject);
	entity->Tag = Entity::EntityTypes::Static;
	mQuadTree->insertEntity(entity);
#pragma endregion
	
}


bool GameMap::isContain(RECT rect1, RECT rect2)
{
	if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
	{
		return false;
	}

	return true;
}

void GameMap::Update(float dt)
{
	for (size_t i = 0; i < mListBricks.size(); i++)
	{
		mListBricks[i]->Update(dt);
	}
}
void GameMap::Draw()
{
	RECT rect;
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
 #pragma region DRAW TILESET
	for (int rowIndex = 0; rowIndex < mrowCount; rowIndex++)
	{
		
		for (int columIndex = 0; columIndex < mcolumnCount; columIndex++)
		{
			//mMap->SetSourceRect()
			rect.left =matrixTile[rowIndex][columIndex]* FrameWidth;
			rect.right = rect.left * FrameWidth;
			rect.top = 0;
			rect.bottom = rect.top + FrameHeight;
			D3DXVECTOR3 position(columIndex*FrameWidth + FrameWidth / 2, rowIndex*FrameHeight + FrameHeight / 2, 0);

		//	mMap->SetSourceRect(rect);
			if (mCamera != NULL)
			{
				RECT objRECT;
				objRECT.left = position.x - FrameWidth / 2;
				objRECT.top = position.y - FrameHeight / 2;
				objRECT.right = objRECT.left + FrameWidth;
				objRECT.bottom = objRECT.top + FrameHeight;

				//neu nam ngoai camera thi khong Draw
				if (isContain(objRECT, mCamera->GetBound()) == false)
					continue;
			}
			mTileMap->SetHeight(FrameHeight);
			mTileMap->SetWidth(FrameWidth);
			//position
			mTileMap->Draw(position,rect,D3DXVECTOR2(),trans);
		}
	}
 #pragma endregion

#pragma region DRAW BRICK

	for (size_t i = 0; i < mListBricks.size(); i++)
	{
		//D3DXVECTOR2 pos(200,80);
		mListBricks[i]->Draw(mListBricks[i]->GetPosition(),RECT(),D3DXVECTOR2(),trans);
		//mListBricks[i]->Draw(pos);
	}

#pragma endregion
}

void GameMap::SetCamera(Camera * camera)
{
	this->mCamera = camera;
}

RECT GameMap::GetWorldMapBound()
{
	
		RECT bound;
		bound.left = bound.top = 0;
		bound.right = GetWidth() * FrameWidth;
		bound.bottom = GetHeight() * FrameHeight;

		return bound;
	
}

bool GameMap::IsBoundLeft()
{
	return (mCamera->GetBound().left == 0);
}

bool GameMap::IsBoundRight()
{
	return (mCamera->GetBound().right == this->GetWidth());
}

bool GameMap::IsBoundTop()
{
	return (mCamera->GetBound().top == 0);
}

bool GameMap::IsBoundBottom()
{
	return (mCamera->GetBound().bottom == this->GetHeight());
}

GameMap::~GameMap()
{
	for (int i = 0; i < mrowCount; i++)
	{
		delete[]	matrixTile[i];
	}
	delete[]matrixTile;
	delete mTileMap;
	delete mCamera;
	for (size_t i = 0; i < mListBricks.size(); i++)
	{
		if (mListBricks[i])
			delete mListBricks[i];
	}
	mListBricks.clear();
	delete mQuadTree;
}

GameMap::GameMap(const char * filepath)
{
	LoadMap(filepath);
}

int GameMap::GetHeight()
{
	return mrowCount*FrameHeight;
}

int GameMap::GetWidth()
{
	return mcolumnCount * FrameWidth;
}
std::vector<Brick*> GameMap::GetListBrick()
{
	return mListBricks;
}

QuadTree * GameMap::GetQuadTree()
{
	return mQuadTree;
}