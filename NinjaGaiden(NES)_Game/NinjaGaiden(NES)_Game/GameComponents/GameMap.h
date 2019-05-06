#include "Sprite.h"
#include "GameGlobal.h"

#include <fstream>
#include <iostream>
#include "Camera.h"
#include "../GameDefine/GameDefine.h"
#include "../GameObjects/MapObjects/Brick.h"
#include "..//GameObjects/MapObjects/BrickNormal.h"
#include "../GameObjects/MapObjects/BrickGold.h"

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
	~GameMap();
private:
	void LoadMap(const char *filepath);
	int mrowCount, mcolumnCount, mtotalTile;
	bool isContain(RECT rect1, RECT rect2);

	int **matrixTile;
	Sprite * mTileMap;
	Camera *mCamera;
	std::vector<Brick*> mListBricks;
	
	


};