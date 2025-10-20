#include "stdafx.h"

#include "Boss.h"
#include "Enemy.h"
#include "EnemyType2.h"
#include "EnemyManager.h"
#include "Game.h"
#include "GameCamera.h"
#include "GameClear.h"
#include "GameOver.h"
#include "Player.h"
#include "PlayerState.h"
#include "Stage.h"
#include "Star.h"
#include "StarCounter.h"
#include "Title.h"

Game::Game(){

};

Game::~Game()
{
    DeleteGO(m_player);
    EnemyManager::DeleteInstance();
    DeleteGO(m_boss);
    DeleteGO(m_stage);
    DeleteGO(m_skyCube);
    DeleteGO(m_starCounter);
    DeleteGO(m_gameCamera);
}

bool Game::Start()
{
    m_player = NewGO<Player>(0, "Player");
    EnemyManager::CreateInstance();
    m_boss = NewGO<Boss>(0, "Boss");
    m_stage = NewGO<Stage>(0, "Stage");
    m_skyCube = NewGO<SkyCube>(0, "SkyCube");
    m_starCounter = NewGO<StarCounter>(0, "StarCounter");
    m_gameCamera = NewGO<GameCamera>(0, "GameCamera");

    // コメントアウトする。
    //PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

    EnemyManager::GetInstance()->Setup();
    return true;
}

void Game::Update()
{
    CreateStar();

    EnemyManager::GetInstance()->Update();

    if (m_player->playerPos.y <= -400.0f)
    {
        m_gameOver = NewGO<GameOver>(0, "GameOver");
        DeleteGO(m_star);
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
