#include "stdafx.h"

#include "Enemy/Boss.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyType2.h"
#include "EnemyManager.h"
#include "Game.h"
#include "GameCamera.h"
#include "GameClear.h"
#include "GameOver.h"
#include "Player/Player.h"
#include "Player/PlayerState.h"
#include "Stage.h"
#include "Star.h"
#include "StarCounter.h"
#include "Title.h"
#include "Collision/CollisionManager.h"
#include "UI/HPUI.h"
#include "Gimmic/Warp.h"
#include "Gimmic/Cannon.h"
#include "EffectManager.h"
#include "SoundManager.h"

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
    DeleteGO(m_hpUI);
    DeleteGO(m_warp);
    DeleteGO(m_cannon);
    DeleteGO(m_effectManager);

    CollisionManager::Delete();
}

bool Game::Start()
{
    // サウンドマネージャーのインスタンスを取得し、BGMを再生
    SoundManager::GetInstance().PlayBGM(SoundManager::SoundNumber::InGameBGM);

    m_player = NewGO<Player>(0, "Player");
    EnemyManager::CreateInstance();
    m_boss = NewGO<Boss>(0, "Boss");
    m_stage = NewGO<Stage>(0, "Stage");
    m_skyCube = NewGO<SkyCube>(0, "SkyCube");
    m_starCounter = NewGO<StarCounter>(0, "StarCounter");
    m_gameCamera = NewGO<GameCamera>(0, "GameCamera");
    m_hpUI = NewGO<HPUI>(0, "HPUI");
    m_warp = NewGO<Warp>(0, "Warp");
    m_cannon = NewGO<Cannon>(0, "Cannon");
    m_effectManager = NewGO<EffectManager>(0, "EffectManager");

    m_levelRender.Init("Assets/stage/stage.tkl",[&](LevelObjectData& objData)
    {
        if (objData.EqualObjectName(L"Slime") == true)
        {
            m_enemy = NewGO<Enemy>(0, "Enemy");
            m_enemy->SetPosition(objData.position);
            return true;
        }
        return true;
    });

    // コメントアウトする。
    //PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

    //エネミーの複数対のモデルを生成
    EnemyManager::GetInstance()->Setup();

    //コリジョンマネージャのインスタンスの取得
    CollisionManager::Create();

    return true;
}

void Game::Update()
{
    CreateStar();

    EnemyManager::GetInstance()->Update();

    // UIに情報を渡す
    {
        float hpRatio = m_player->GetHP() / static_cast<float>(m_player->GetMaxHP());
        m_hpUI->SetRatio(hpRatio);
    }

    if (m_player->GetPosition().y <= -400.0f || m_player->IsGameOver() == true)
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

    CollisionManager::Get()->Update();
}

void Game::CreateStar()
{
    if (m_boss->IsDead() == true)
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
