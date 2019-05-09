#include "Sprite.h"
#include "GameGlobal.h"

#include <fstream>
#include <iostream>
#include "Camera.h"
#include "../GameDefine/GameDefine.h"
#include "..//GameComponents/QuadTree.h"
#include "../GameObjects/Entity.h"
#include "../GameObjects/StaticGameObject/Butterfly.h"
using namespace std;
class GameMap
{
public:
	GameMap(const char *filepath);
	int GetHeight();
	int GetWidth();
	void Draw();

	void Update(float dt);
	void SetCamera(Camera *camera);
	RECT GetWorldMapBound();
	bool IsBoundLeft(); //kiem tra luc nay Camera o vi bien ben trai so voi WorldMap
	bool IsBoundRight(); // kiem tra xem co o vi tri bien ben phai worldmap khong
	bool IsBoundTop(); // kiem tra xem co o vi tri bien ben trai worldmap khong
	bool IsBoundBottom(); // kiem tra xem co o vi tri bien ben phai worldmap khong
	~GameMap();

	std::vector<GameObject*> GetListObject();

	QuadTree* GetQuadTree();
private:
	void LoadMap(const char *filepath);
	int mrowCount, mcolumnCount, mtotalTile;
	bool isContain(RECT rect1, RECT rect2);

	int **matrixTile;
	Sprite * mTileMap;
	Camera *mCamera;
	QuadTree *mQuadTree;
	std::vector<GameObject*> mListObjects;
	
//	LPD3DXSPRITE                    mSpriteHandler;
	//Sprite                          *mSpriteBricks;


};