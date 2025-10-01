#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "IState.h"
#include "Enemy.h"
#include "EnemyType2.h"
#include "Stage.h"
#include "GameCamera.h"
#include "GameClear.h"
#include "GameOver.h"


Game::Game()
{

};

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_enemy);
	DeleteGO(m_enemyType2);
	DeleteGO(m_stage);
	DeleteGO(m_gameCamera);
}

bool Game::Start()
{
	m_player = NewGO<Player>(0, "Player");
	m_enemy = NewGO<Enemy>(0, "Enemy");
	m_enemyType2 = NewGO<EnemyType2>(0, "EnemyType2");
	m_stage = NewGO<Stage>(0, "Stage");
	m_gameCamera = NewGO<GameCamera>(0, "GameCamera");

	//コメントアウトする。
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

void Game::Update()
{
	//if (m_player->hp == 0)
	//{
	//	//m_gameOver = NewGO<GameOver>(0, "GameOver");
	//}

	//if (m_enemy->hp == 0)
	//{
	//	//m_gameClear = NewGO<GameClear>(0, "GameClear");
	//}
}

void Game::Render(RenderContext& rc)
{

}