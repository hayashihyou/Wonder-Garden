#pragma once

#include "Level3DRender/LevelRender.h"
#include "nature/SkyCube.h"

class Player;
class IEnemyState;
class Enemy;
class EnemyType2;
class EnemyManager;
class Boss;
class Stage;
class Star;
class StarCounter;
class Title;
class GameCamera;
class GameClear;
class GameOver;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void CreateStar();
	void Render(RenderContext& rc);

private:
	Player* m_player = nullptr;
	IEnemyState* m_iState = nullptr;
	Enemy* m_enemy = nullptr;
	EnemyType2* m_enemyType2 = nullptr;
	Boss* m_boss = nullptr;
	Stage* m_stage = nullptr;
    SkyCube* m_skyCube = nullptr;
	Star * m_star = nullptr;
	StarCounter* m_starCounter = nullptr;
	Title* m_title = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameClear* m_gameClear = nullptr;
	GameOver* m_gameOver = nullptr;

	Vector3 m_pos;
};

