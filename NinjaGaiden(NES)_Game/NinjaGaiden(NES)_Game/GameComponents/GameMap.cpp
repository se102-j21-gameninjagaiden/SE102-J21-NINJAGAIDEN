#include "GameMap.h"
#include <string>
GameMap::GameMap(int level)
{
	LoadMap(level);
}
void GameMap::LoadMap( int level)
{
	/*drawEffect = false;
	TimeDrawEffect = 6000;*/
	

	fstream fs("Resources/Map/Map" + to_string(level) + "/map.txt");
	//fs >> mtotalTile;
	fs >> mcolumnCount >> mrowCount;
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
	string  tileSet = "Resources/Map/Map"+ to_string(level) + "/tileSet.png";
	mTileMap = new Sprite(tileSet.c_str());

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth();
	r.bottom = this->GetHeight();

	mQuadTree = new QuadTree(1, r);
	// Khởi tạo các viên gạch
	//khoi tao cac khoi Brick (vien gach)
#pragma region -ENEMY-
	fstream f_ei("Resources/Map/Map" + to_string(level) + "/Enemy.txt");
	float idType, posX, posY;
	while (!f_ei.eof())
	{
		f_ei >> idType >> posX >> posY;
		D3DXVECTOR3 position;
			//fstream fs("Brick");
		GameObject *object = nullptr;
		switch (int(idType))
		{
		case 1:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new Swordman(position);
			
			object->Tag = Entity::EntityTypes::Enemy;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;
		
		case 3:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new Panther(position);

			object->Tag = Entity::EntityTypes::Enemy;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);
			break;
		case 4:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new Eagle(position);

			object->Tag = Entity::EntityTypes::Enemy;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;
		case 5:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new Goblin(position);

			object->Tag = Entity::EntityTypes::Enemy;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;
			
		case 6:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new Brute(position);

			object->Tag = Entity::EntityTypes::Enemy;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;
		/*case 7 :	
			position = D3DXVECTOR3(posX, posY, 0);
			object = new Stair(position);

			object->Tag = Entity::EntityTypes::Stair;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);
			break;*/
		

		}
		
	
	}
	f_ei.close();
	
#pragma endregion

#pragma region -Item-
	fstream f_item("Resources/Map/Map" + to_string(level) + "/Item.txt");
	float  posStop;
	while (!f_item.eof())
	{
		f_item >> idType >> posX >> posY >> posStop;
		D3DXVECTOR3 position;
		//fstream fs("Brick");
		GameObject *object = nullptr;
		switch (int(idType))
		{
		case 0:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new Butterfly(position);

			object->Tag = Entity::EntityTypes::Item;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;

		case 1:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new BlueMana(position,posStop);

			object->Tag = Entity::EntityTypes::Item;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;
		case 2:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new RedMana(position, posStop);

			object->Tag = Entity::EntityTypes::Item;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;
		case 3:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new RedBonus(position, posStop);

			object->Tag = Entity::EntityTypes::Item;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;
		case 4:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new BlueBonus(position, posStop);

			object->Tag = Entity::EntityTypes::Item;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;
		case 5:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new RedHP(position, posStop);

			object->Tag = Entity::EntityTypes::Item;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;
		case 6:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new Fire(position, posStop);

			object->Tag = Entity::EntityTypes::Item;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;
		case 7:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new ThrowingStar(position, posStop);

			object->Tag = Entity::EntityTypes::Item;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;
		case 8:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new TimeFreeze(position, posStop);

			object->Tag = Entity::EntityTypes::Item;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;
		case 9:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new WindmillStar(position, posStop);

			object->Tag = Entity::EntityTypes::Item;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;

		case 10:
			position = D3DXVECTOR3(posX, posY, 0);
			object = new Stair(position, posStop);

			object->Tag = Entity::EntityTypes::Stair;

			mListObjects.push_back(object);
			if (object)
				mQuadTree->insertEntity(object);

			break;
		
		}
	}
		f_item.close();
		

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
	fstream f("Resources/Map/Map" + to_string(level) + "/StaticObjectMap.txt");
	float widthObject, heightObject, idX_Object, idY_Object;
	//f >> widthObject;
	while (!f.eof())
	{
		f >>idType>> widthObject >> heightObject >> idX_Object >> idY_Object;
		Entity *entity = nullptr;
		switch (int (idType))
		{

		case 0:
			entity= new Entity();
			entity->SetPosition(idX_Object*FrameWidth + widthObject / 2, idY_Object*FrameHeight + heightObject / 2);
			entity->SetWidth(widthObject);
			entity->SetHeight(heightObject);
			entity->Tag = Entity::EntityTypes::Static;
			mQuadTree->insertEntity(entity);
			break;
		case 1:
			entity = new Entity();
			entity->SetPosition(idX_Object*FrameWidth + widthObject / 2, idY_Object*FrameHeight + heightObject / 2);
			entity->SetWidth(widthObject);
			entity->SetHeight(heightObject);
			entity->Tag = Entity::EntityTypes::Stair;
			mQuadTree->insertEntity(entity);
			break;
		}
		
	}
	f.close();

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
	for (size_t i = 0; i < mListObjects.size(); i++)
	{
		//if (mListObjects[i]->Tag ==Entity::EntityTypes ::None)
		//{
		//	mListObjects.erase(mListObjects.begin() + i);
		//
		//	//mListObjects[i]->Update(dt);

		//}
		//else
		//{
			mListObjects[i]->Update(dt);
		//}
	}
}
void GameMap::Draw()
{
	RECT rect;
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
 #pragma region DRAW TILESET
	for (int rowIndex = 0; rowIndex <mrowCount; rowIndex++)
	{
		
		for (int columIndex = 0; columIndex < mcolumnCount; columIndex++)
		{
			//mMap->SetSourceRect()
			rect.left =( matrixTile[rowIndex][columIndex]) * FrameWidth;
			rect.right = rect.left +FrameWidth;
			rect.top = 0;
			rect.bottom = rect.top + FrameHeight;
			D3DXVECTOR3 position((columIndex)*FrameWidth+FrameWidth/2, (rowIndex)*FrameHeight+FrameHeight/2, 0);

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
			//if (!drawEffect)
			mTileMap->Draw(position,rect,D3DXVECTOR2(),trans);
			/*else
			{
				mTileMap->Draw(position, rect, D3DXVECTOR2(), trans, 0, D3DXVECTOR2(), D3DCOLOR_ARGB(rand() % 255, 255, 255, 255));
				TimeDrawEffect--;
				if (TimeDrawEffect <= 0)
				{
					TimeDrawEffect = 6000;
					Sleep(2000);
					drawEffect = false;

				}

			}*/

		}
	}
 #pragma endregion

#pragma region DRAW BRICK

	for (size_t i = 0; i < mListObjects.size(); i++)
	{
		//D3DXVECTOR2 pos(200,80);
		mListObjects[i]->Draw(mListObjects[i]->GetPosition(),RECT(),D3DXVECTOR2(),trans);
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
	for (size_t i = 0; i < mListObjects.size(); i++)
	{
		if (mListObjects[i])
			delete mListObjects[i];
	}
	mListObjects.clear();
	delete mQuadTree;
}



int GameMap::GetHeight()
{
	return (mrowCount)*FrameHeight;
}

int GameMap::GetWidth()
{
	return mcolumnCount * FrameWidth;
}
//std::vector<Entity*> GameMap::GetListObject()
//{
//	return mListObjects;
//}

std::vector<GameObject*> GameMap::GetListObject()
{
	return mListObjects;
}
QuadTree * GameMap::GetQuadTree()
{
	return mQuadTree;
}