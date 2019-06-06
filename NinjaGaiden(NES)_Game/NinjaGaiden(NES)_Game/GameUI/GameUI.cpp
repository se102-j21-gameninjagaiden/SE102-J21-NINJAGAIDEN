#include "GameUI.h"


void GameUI::_initialize()
{
	// init weaponSprite
	// _currentWeapon dùng để vẽ hình weapon trên UI thôi
	//weapons = vector<GSprite*>();
	/*weapons.push_back(new GSprite(TextureManager::getInstance()->getTexture(EnumID::Dagger_ID), 1));
	weapons.push_back(new GSprite(TextureManager::getInstance()->getTexture(EnumID::Boomerang_ID), 1));
	weapons.push_back(new GSprite(TextureManager::getInstance()->getTexture(EnumID::Throw_Axe_ID), 1));
	weapons.push_back(new GSprite(TextureManager::getInstance()->getTexture(EnumID::StopWatch_ID), 1));
	weapons.push_back(new GSprite(TextureManager::getInstance()->getTexture(EnumID::HolyWaterItem_ID), 1));*/

	// init hp sprite
	//_hpSprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::HP_ID), 1);
	_hpSprite = new Sprite("Resources/Item_Effect/heal.png");
	_boxWeapon = new Sprite("Resources/Item_Effect/BoxWeapon.png");
	_manaSprite = new Sprite("Resources/Item_Effect/mana.png");
	//_Weapon = new Sprite("Resources/Item_Effect/ThrowingStarWeapon.png");
	_gameTimer = 0;
	_gameStage = 1;
	_liveCount = 2;
	_playerHP = 16;
	_enemyHP = 16;
	_playerMana = 0;
}
GameUI::GameUI(LPDIRECT3DDEVICE9 d3ddev_, int size_, int screenWidth_, int screenHeight_)
{
	this->_initialize();
	//_sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::GameUI_ID), 1);
	_arial = new Font(d3ddev_, size_, screenWidth_, screenHeight_);
}
void GameUI::drawTable()
{
	// draw table
	
	//draw Box Weapon
	_boxWeapon->Draw(D3DXVECTOR3(95,8,0));
	//_Weapon->Draw(D3DXVECTOR3(95, 8, 0));
	// draw Mana
	_manaSprite->Draw(D3DXVECTOR3(45,50,0));
	// draw hp
	// Vẽ hình thứ 2 của HP sprite
	RECT rect;
	rect.left = _hpSprite->GetWidth() / 2;
	rect.right = _hpSprite->GetWidth();
	rect.top = 0;
	rect.bottom = _hpSprite->GetHeight();
	for (int i = 0; i < MAX_HP; i++)
	{
		_hpSprite->Draw(D3DXVECTOR3(150 + 7.5 * i, 30, 0), rect);
	}
	for (int i = 0; i < _playerHP; i++)
	{
		_hpSprite->Draw(D3DXVECTOR3(150 + 7.5 * i, 30, 0));
	}
	
	// boss
	for (int i = 0; i < MAX_HP; i++)
	{
		_hpSprite->Draw(D3DXVECTOR3(150 + 7.5 * i, 45, 0), rect);
	}
	for (int i = 0; i < _enemyHP; i++)
	{
		_hpSprite->Draw(D3DXVECTOR3(150 +7.5 * i, 45, 0));
	}
	



	// draw weapon
	/*if (_currentWeapon != -1)
	{
		weapons.at(_currentWeapon)->Draw(345, 48);
	}
*/
}

void GameUI::drawScore()
{
	
	_arial->onLost();
	

	_arial->render("Score:", 5, 0);
	
	_arial->render(_playerScore, 45, 0);

	_arial->render("TIME:", 5,20);
	_arial->render(_gameTimer / 1000, 40, 20);

	_arial->render("STAGE: 3 -", 150, 0);
	_arial->render(_gameStage, 215, 0);
	_arial->render("PLAYER:", 85, 23);
	_arial->render("ENEMY:", 90, 40);

	_arial->render("P:", 5, 40);
	_arial->render(_liveCount, 20, 40);

	_arial->render(_playerMana, 54, 42);
	//_arial->render(_weaponCount, 430, 50);

	//_arial->render("collide ID: ", 150, 80);
	//_arial->render(_collideID, 250, 80);
	//_arial->render("colstair: ", 390, 80);
	//_arial->render(_colabc, 480, 80);
	//_arial->render("ranger: ", 290, 80);
	//_arial->render(_rang, 360, 80);
	////_arial->render("onstair: ", 290, 80);
	//_arial->render(_onstair, 390, 100);
	//_arial->render(_checkCameraHaft, 100, 100);
}

void GameUI::initTimer(int deltaTime_)
{
	_gameTimer = deltaTime_ * 1000;
}

int GameUI::getTimer()
{
	return _gameTimer / 1000;
}

void GameUI::SetTimer(int x)
{
	_gameTimer += x;
}

//int GameUI::GetWeaponCount()
//{
//	return _weaponCount;
//}

//void GameUI::SetWeaponCount(int x)
//{
//	_weaponCount += x;
//}

void GameUI::SetplayerScore(int x)
{
	_playerScore = x;
}

int GameUI::GetplayerScore()
{
	return _playerScore;
}

void GameUI::SetplayerHP(int x)
{
	_playerHP = x;
}

void GameUI::SetenemyHP(int x)
{
	_enemyHP = x;
}

int GameUI::GetplayerHP()
{
	return _playerHP;
}

int GameUI::GetenemyHP()
{
	return _enemyHP;
}

GameUI::GameUI(void)
{

}

void GameUI::Update(float dt)
{
	if (_gameTimer <= 0)
	{
		_playerHP = 0;
		
	}
	else
	{
		_gameTimer = _gameTimer - dt * 1000;
	}
	//if (_playerHP == 0)
	//{
	//	if (_liveCount > 0)
	//	{
	//		_liveCount--;
	//		//_playerHP = MAX_HP;
	//		SetplayerHP(MAX_HP);

	//		initTimer (150);
	//	}
	//	else
	//	{
	//		_liveCount = 2;
	//		SetplayerHP(MAX_HP);

	//		_playerScore = 0;
	//		initTimer(150);
	//	}

	//	
	//}
}

void GameUI::SetLiveCount(int x)
{
	_liveCount = x;
}

int GameUI::GetLiveCount()
{
	return _liveCount;
}

void GameUI::SetplayerMana(int x)
{
	_playerMana = x;
}

int GameUI::GetplayerMana()
{
	return _playerMana;
}



//void GameUI::updateScore(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, int weaponCount_, EnumID weaponID_, int enemyHP_)
//{
//	//(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, EnumID weaponID_, int weaponCount_, int enemyHP_)
//	_gameStage = gameStage_;
//	_playerScore = playerScore_;
//	if (_gameTimer <= 0)
//	{
//	}
//	else
//		_gameTimer = _gameTimer - deltaTime_;
//	//_weaponCount = weaponCount_;
//	_playerHP = playerHP_;
//	_enemyHP = enemyHP_;
//	_liveCount = liveCount_;

	//switch (weaponID_)
	//{

	//case Dagger_ID:
	//	_currentWeapon = 0;
	//	break;
	//case Boomerang_ID:
	//	_currentWeapon = 1;
	//	break;
	//case Throw_Axe_ID:
	//	_currentWeapon = 2;
	//	break;
	//case StopWatch_ID:
	//	_currentWeapon = 3;
	//	break;
	//case HolyWaterItem_ID:
	//	_currentWeapon = 4;
	//	break;
	//default:
	//	_currentWeapon = -1;
	//	break;
	//}

//}


//void GameUI::updateScore(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, int weaponCount_, EnumID weaponID_, int enemyHP_, int _x, int _y, int viewPortX, int viewPortY)
//{
//	//(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, EnumID weaponID_, int weaponCount_, int enemyHP_)
//	_gameStage = gameStage_;
//	_playerScore = playerScore_;
//	if (_gameTimer <= 0)
//	{
//	}
//	else
//		_gameTimer = _gameTimer - deltaTime_;
//	//_weaponCount = weaponCount_;
//	_playerHP = playerHP_;
//	_enemyHP = enemyHP_;
//	_liveCount = liveCount_;
	/*_playerX = _x;
	_playerY = _y;
	_viewPortY = viewPortY;
	_viewPortX = viewPortX;*/
	//switch (weaponID_)
	//{
	//	/*case Watch_ID:
	//	_currentWeapon = 0;
	//	break;*/
	//case Dagger_ID:
	//	_currentWeapon = 0;
	//	break;
	//case Boomerang_ID:
	//	_currentWeapon = 1;
	//	break;
	//case Throw_Axe_ID:
	//	_currentWeapon = 2;
	//	break;
	//default:
	//	_currentWeapon = -1;
	//	break;
	//}

//}



//void GameUI::updateScore(int gameStage_, int playerScore_, int deltaTime_, int playerHP_, int liveCount_, int weaponCount_, EnumID weaponID_, int enemyHP_, int _x, int _y, int viewPortX, int viewPortY, int collideId, bool abc, int rang, bool onstair, float checkCameraHaft)
//{
//
//	_gameStage = gameStage_;
//	_playerScore = playerScore_;
//	if (_gameTimer <= 0)
//	{
//	}
//	else
//		_gameTimer = _gameTimer - deltaTime_;
//	//_weaponCount = weaponCount_;
//	_playerHP = playerHP_;
//	_enemyHP = enemyHP_;
//	_liveCount = liveCount_;
//
//	_checkCameraHaft = checkCameraHaft;
//
	//switch (weaponID_)
	//{

	//case Dagger_ID:
	//	_currentWeapon = 0;
	//	break;
	//case Boomerang_ID:
	//	_currentWeapon = 1;
	//	break;
	//case Throw_Axe_ID:
	//	_currentWeapon = 2;
	//	break;
	//case StopWatch_ID:
	//	_currentWeapon = 3;
	//	break;

	//case HolyWater_ID:
	//	_currentWeapon = 4;
	//	break;
	//default:
	//	_currentWeapon = -1;
	//	break;
	//}

//}

GameUI::~GameUI(void)
{
}
