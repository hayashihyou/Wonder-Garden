#include "stdafx.h"

#include "Coin.h"
#include "CoinCount.h"
#include "Collision/CollisionManager.h"
#include "EffectManager.h"
#include "Enemy/Boss.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyType2.h"
#include "EnemyManager.h"
#include "Game.h"
#include "GameCamera.h"
#include "GameClear.h"
#include "GameOver.h"
#include "Gimmic/Cannon.h"
#include "Gimmic/Warp.h"
#include "Player/Player.h"
#include "Player/PlayerState.h"
#include "SoundManager.h"
#include "Stage.h"
#include "Star.h"
#include "StarCounter.h"
#include "Title.h"
#include "UI/CoinUI.h"
#include "UI/HPUI.h"


namespace
{
    const Vector3 BOSS_BATTLE_POS = {2100.0f, 68.0f, 3000.0f};
}


Game::Game(){

};

Game::~Game()
{
    const auto& coins = FindGOs<Coin>("Coin");
    for (auto m_coin : coins)
    {
        DeleteGO(m_coin);
    }

    const auto& enemys = FindGOs<Enemy>("Enemy");
    for (auto m_enemy : enemys)
    {
        DeleteGO(m_enemy);
    }

    if (m_boss != nullptr)
    {
        DeleteGO(m_boss);
    }

    if (m_star != nullptr)
    {
        DeleteGO(m_star);
    }

    EnemyManager::DeleteInstance();
    DeleteGO(m_player);
    DeleteGO(m_stage);
    DeleteGO(m_skyCube);
    DeleteGO(m_starCounter);
    DeleteGO(m_gameCamera);
    DeleteGO(m_countCointer);
    DeleteGO(m_coinUI);
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
    m_stage = NewGO<Stage>(0, "Stage");
    m_skyCube = NewGO<SkyCube>(0, "SkyCube");
    m_starCounter = NewGO<StarCounter>(0, "StarCounter");
    m_gameCamera = NewGO<GameCamera>(0, "GameCamera");
    m_hpUI = NewGO<HPUI>(0, "HPUI");
    m_warp = NewGO<Warp>(0, "Warp");
    m_cannon = NewGO<Cannon>(0, "Cannon");
    m_effectManager = NewGO<EffectManager>(0, "EffectManager");
    m_countCointer = NewGO<CountCointer>(0, "CoinCounter");
    m_coinUI = NewGO<CoinUI>(0, "CoinUI");

    m_levelRender.Init("Assets/stage/stage.tkl",[&](LevelObjectData& objData)
    {
        if (objData.EqualObjectName(L"Slime") == true)
        {
            m_enemy = NewGO<Enemy>(0, "Enemy");
            m_enemy->SetPosition(objData.position);
            m_enemy->SetRotation(objData.rotation);
            return true;
        }

        if (objData.EqualObjectName(L"Coin") == true)
        {
            m_coin = NewGO<Coin>(0, "Coin");
            m_coin->SetPosition(objData.position);
            m_coin->SetRotation(objData.rotation);
            return true;
        }

        if (objData.EqualObjectName(L"Boss") == true)
        {
            m_boss = NewGO<Boss>(0, "Boss");
            m_boss->SetPosition(objData.position);
            m_boss->SetRotation(objData.rotation);
            return true;
        }
             return true;
    });

    // コメントアウトする。
    //PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

    // エネミーの複数対のモデルを生成
    EnemyManager::GetInstance()->Setup();

    // コリジョンマネージャのインスタンスの取得
    CollisionManager::Create();

    return true;
}

void Game::Update()
{
    CreateStar();

    BossBattle();

    EnemyManager::GetInstance()->Update();

    CollisionManager::Get()->Update();

    // UIに情報を渡す
    {
        float hpRatio = m_player->GetHP() / static_cast<float>(m_player->GetMaxHP());
        m_hpUI->SetRatio(hpRatio);
    }

    if (m_player->GetPosition().y <= -400.0f || m_player->IsGameOver() == true)
    {
        NewGO<GameOver>(0, "GameOver");
        DeleteGO(this);
    }

    if (m_starCounter->GetStarCount() == 1)
    {
        NewGO<GameClear>(0, "GameClear");
        DeleteGO(this);
    }
}

void Game::CreateStar()
{
    if (m_boss->IsDead() == true)
    {
        if (m_star == nullptr)
        {
            DeleteGO(m_boss);
            m_star = NewGO<Star>(0, "Star");
        }
    }
}

void Game::BossBattle()
{
   Vector3 playerPos = m_player->GetPosition();
   if (playerPos.x >= BOSS_BATTLE_POS.x && playerPos.z >= BOSS_BATTLE_POS.z)
   {
       if (m_boss->GetBattleFlag() == false)
       {
           m_boss->SetBattleFlag(true);
           m_gameCamera->SetBossCamera(true);
           m_boss->SetAppear(true);
           m_boss->InitHPBar();
       }
   }
}

void Game::Render(RenderContext& rc) {}
