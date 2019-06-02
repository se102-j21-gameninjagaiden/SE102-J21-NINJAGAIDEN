#pragma once
//#include "Sprite.h"
//#include "TextureManager.h"
#include "Font.h"
#include <vector>
#include "../GameComponents/Sprite.h"
using namespace std;

#define MAX_HP 16

class GameUI
{
protected:
	//GSprite* _sprite;
	Sprite *_manaSprite;

	//Sprite *_Weapon;

	Font* _arial;
	int _playerScore;
	int _gameTimer;
	int _gameStage;
	//int _weaponCount;
	int _playerHP;
	int _enemyHP;
	int _playerMana;
	int _liveCount;
	//int _currentWeapon;


	//float _checkCameraHaft;
	//vector<GSprite*> weapons;
	//GSprite* _hpSprite;
	Sprite* _hpSprite;
	void _initialize();


public:
	GameUI(void);
	GameUI(LPDIRECT3DDEVICE9 d3ddev_, int size_, int screenWidth_, int screenHeight_);
	void drawTable();
	void drawScore();
	// deltaTime is in second
	void initTimer(int deltaTime_);
	int getTimer(); // return Time left of game in second
	void SetTimer(int x);
	//int GetWeaponCount();
	//void SetWeaponCount(int x);
	void SetplayerScore(int x);
	int GetplayerScore();
	void SetplayerHP(int x);
	void SetenemyHP(int x);
	int GetplayerHP();
	int GetenemyHP();
	void Update(float dt);
	void SetLiveCount(int x);
	int GetLiveCount();
	void SetplayerMana(int x);
	int GetplayerMana();
	// deltaTime_ is in milisecond
	//void updateScore(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, int weaponCount_, EnumID weaponID_, int enemyHP_ = 20);
	Sprite * _boxWeapon;

//	void updateScore(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, int weaponCount_, EnumID weaponID_, int enemyHP_, int _x, int _y, int viewPortX, int viewPortY);

	//void updateScore(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, int weaponCount_, EnumID weaponID_, int enemyHP_, int _x, int _y, int viewPortX, int viewPortY, int collideId, bool abc, int rang, bool onstair, float checkCameraHaft);
	~GameUI(void);
};

