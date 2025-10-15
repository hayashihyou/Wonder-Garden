#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "PlayerState.h"
#include "Enemy.h"
#include "EnemyType2.h"
#include "Boss.h"
#include "Stage.h"
#include "Star.h"
#include "StarCounter.h"
#include "Title.h"
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
	DeleteGO(m_boss);
	DeleteGO(m_stage);
	DeleteGO(m_starCounter);
	DeleteGO(m_gameCamera);
}

bool Game::Start()
{
	m_player = NewGO<Player>(0, "Player");
	m_enemy = NewGO<Enemy>(0, "Enemy");
	m_enemyType2 = NewGO<EnemyType2>(0, "EnemyType2");
	m_boss = NewGO<Boss>(0, "Boss");
	m_stage = NewGO<Stage>(0, "Stage");
	m_starCounter = NewGO<StarCounter>(0, "StarCounter");
	m_gameCamera = NewGO<GameCamera>(0, "GameCamera");

	//コメントアウトする。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

void Game::Update()
{
	CreateStar();

	if (m_player->playerPos.y <= -400.0f)
	{
		m_gameOver = NewGO<GameOver>(0, "GameOver");
		DeleteGO(this);
	}

	if (m_starCounter->GetStarCount() == 1)
	{
		m_gameClear = NewGO<GameClear>(0, "GameClear");
		DeleteGO(this);
	}
		
}

void Game::CreateStar()
{
	if (m_boss->isDeadFlag == true)
	{
		if (m_star == nullptr)
		{
			m_star = NewGO<Star>(0, "Star");
		}
	}
}

void Game::Render(RenderContext& rc)
{

}