#include "stdafx.h"

#include "Coin.h"
#include "CoinCount.h"
#include "Collision/CollisionManager.h"
#include "EffectManager.h"
#include "Enemy/Boss.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyType2.h"
#include "KillCounter.h"
#include "Game.h"
#include "GameCamera.h"
#include "GameClear.h"
#include "GameOver.h"
#include "Gimmic/Cannon.h"
#include "Gimmic/Warp.h"
#include "Fade.h"
#include "Player/Player.h"
#include "Player/PlayerState.h"
#include "SoundManager.h"
#include "Stage.h"
#include "Star.h"
#include "StarCounter.h"
#include "Score.h"
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

    const auto& enemysType2 = FindGOs<EnemyType2>("EnemyType2");
    for (auto m_enemyType2 : enemysType2)
    {
        DeleteGO(m_enemyType2);
    }

    if (m_boss != nullptr)
    {
        DeleteGO(m_boss);
    }

    if (m_star != nullptr)
    {
        DeleteGO(m_star);
    }

    DeleteGO(m_starCounter);
    DeleteGO(m_boss);
    DeleteGO(m_stage);
    DeleteGO(m_skyCube);
    DeleteGO(m_coinUI);
    DeleteGO(m_hpUI);
    DeleteGO(m_warp);
    DeleteGO(m_cannon);

    CollisionManager::Delete();
    EffectManager::Delete();
}

bool Game::Start()
{
    // サウンドマネージャーのインスタンスを取得し、BGMを再生
    SoundManager::GetInstance().PlayBGM(SoundManager::SoundNumber::InGameBGM);

    m_player = NewGO<Player>(0,"Player");
    m_stage = NewGO<Stage>(0, "Stage");
    m_starCounter = NewGO<StarCounter>(0, "StarCounter");
    m_gameCamera = NewGO<GameCamera>(0,"GameCamera");
    m_hpUI = NewGO<HPUI>(0, "HPUI");
    m_warp = NewGO<Warp>(0, "Warp");
    m_countCointer = NewGO<CoinCounter>(0, "CoinCounter");
    m_coinUI = NewGO<CoinUI>(0, "CoinUI");
    m_killCounter = NewGO<KillCounter>(0, "KillCounter");
    m_score = NewGO<Score>(0, "Score");


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

        if (objData.EqualObjectName(L"StoneMonster") == true)
        {
            m_enemyType2 = NewGO<EnemyType2>(0, "EnemyType2");
            m_enemyType2->SetPosition(objData.position);
            m_enemyType2->SetRotation(objData.rotation);
            return true;
        }

        if (objData.EqualObjectName(L"Cannon") == true)
        {
            m_cannon = NewGO<Cannon>(0, "Cannon");
            m_cannon->SetPosition(objData.position);
            m_cannon->SetRotation(objData.rotation);
            return true;
        }
    });

    // コメントアウトする。
    //PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

    g_sceneLight->SetDirectionLight(0, Vector3(0.0f, -1.0f, 0.5f), Vector3(4.2f,4.2f,4.8f));
    g_sceneLight->SetAmbinet(Vector3(0.8f, 0.8f, 0.8f));

    // コリジョンマネージャのインスタンスの取得
    CollisionManager::Create();

    //エフェクトマネージャーのインスタンスの取得
    EffectManager::Create();
    EffectManager::Get()->Start();

    return true;
}

void Game::Update()
{
    // ボス戦開始判定
    BossBattle(); 

    // 星生成判定
    CreateStar();


    CollisionManager::Get()->Update();

    // UIに情報を渡す
    {
        float hpRatio = m_player->GetHP() / static_cast<float>(m_player->GetMaxHP());
        m_hpUI->SetRatio(hpRatio);
    }

    if (m_player->GetPosition().y <= -400.0f || m_player->IsGameOver() == true)
    {
        if (m_fade == nullptr)
        {
            m_fade = NewGO<Fade>(1, "Fade"); 
        }
        SoundManager::GetInstance().DeleteCurrentBGM();
        if (m_fade->IsFade())
        {
            DeleteGO(this);
        }
        
    }

    if (m_player->IsClear())
    {
        if (m_fade == nullptr)
        {
            m_fade = NewGO<Fade>(1, "Fade");
        }
        SoundManager::GetInstance().DeleteCurrentBGM();
        if (m_fade->IsFade())
        {
            DeleteGO(this);
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

           //ボスの登場時のカメラのフラグをtrueにする
           m_gameCamera->SetBossCamera(true);

           //HPバーを出現するフラグをtrueにする
           m_boss->SetAppear(true);
           m_boss->InitHPBar();
       }
   }
}

void Game::CreateStar()
{
    if (m_boss->IsDead() == true)
    {
        if (m_star == nullptr)
        {
            m_star = NewGO<Star>(0, "Star");
            m_gameCamera->SetStarCamera(true);

        }
    }
}


void Game::Render(RenderContext& rc) {}
