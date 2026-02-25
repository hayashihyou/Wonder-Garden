#include "stdafx.h"

#include "GameClear.h"
#include "Title.h"
#include "CoinCount.h"
#include "KillCounter.h"
#include "Score.h"
#include "UI/UIBase.h"
#include <Util/CRC32.h>

namespace
{
    const Vector3 TEXTURE_POSITION = {0.0f, 450.0f, 0.0f};
    const Vector3 PUSH_TEXTURE_POSITION = {0.0f, -450.0f, 0.0f};
    const Vector3 COIN_TEXT_POSITION = {-150.0f, 200.0f, 0.0f};
    const Vector3 ENEMY_TEXT_POSITION = {325.0f, 200.0f, 0.0f};
    const Vector3 ENEMYTYPE2_TEXT_POSITION = {-150.0f, 100.0f, 0.0f};
    const Vector3 BOSS_TEXT_POSITION = {325.0f, 100.0f, 0.0f};
    const Vector3 SCORE_UI_POSITION = {200.0f, 0.0f, 0.0f};
    const Vector3 TEXTURE_SCALE = {2.5f, 2.5f, 1.0f};
    const Vector3 PUSH_TEXTURE_SCALE = {2.0f, 2.0f, 1.0f};
    const Vector3 COIN_TEXT_SCALE = {1.0f, 1.0f, 1.0f};
} // namespace

GameClear::GameClear() {}

GameClear::~GameClear()
{
    DeleteGO(m_coinCount);
}

bool GameClear::Start()
{
    m_coinCount = FindGO<CoinCounter>("CoinCounter");
    m_killCount = FindGO<KillCounter>("KillCounter");
    m_score = FindGO<Score>("Score");

    m_killCount->TotalCount();

    m_score->CalcScore();

    // 初期化
    Init();

    return true;
}

void GameClear::Update()
{
    m_fadeTime -= g_gameTime->GetFrameDeltaTime();

    if (m_fadeTime <= 0.0f)
    {
        m_fadeTime = 0.0f;
        m_uiCanvas->PlayAnimation();

        ResultCoin();

        ResultEnemy();

        ResultScore();

        m_uiCanvas->Update();
    }

    // Bボタンでタイトルへ戻る
    if (g_pad[0]->IsTrigger(enButtonB))
    {
        NewGO<Title>(0, "Title");
        DeleteGO(this);
    }
}

void GameClear::Render(RenderContext& rc)
{

    m_gameClear.Draw(rc);

    if (m_fadeTime <= 0.0f)
    {
        m_clearText->Render(rc);
        m_coinTexture->Render(rc);
        m_coinCountMark->Render(rc);
        m_coinUIDigit->Render(rc);
    }

    if (m_coinTime <= 0.0f)
    {
        m_enemyTexture->Render(rc);
        m_enemyCountMark->Render(rc);
        m_enemyUIDigit->Render(rc);
    }

    if (m_enemyTime <= 0.0f)
    {
        m_enemyType2Texture->Render(rc);
        m_enemyType2CountMark->Render(rc);
        m_enemyType2UIDigit->Render(rc);
    }

    if (m_enemyType2Time <= 0.0f)
    {
        m_bossTexture->Render(rc);
        m_bossCountMark->Render(rc);
        m_bossUIDigit->Render(rc);
    }

    if (m_bossTime <= 0.0f)
    {
        m_scoreText->Render(rc);
        m_scoreUIDigit->Render(rc);
    }

    if (m_scoreTime <= 0.0f)
    {
        m_pushText->Render(rc);
    }
}

void GameClear::Init()
{

    m_gameClear.Init("Assets/texture/OutGame/GameClear.DDS", 1920.0f, 1080.0f);
    m_gameClear.SetPosition(Vector3::Zero);
    m_gameClear.Update();

    m_uiCanvas = std::make_unique<UICanvas>();

    m_clearText = m_uiCanvas->CreateUI<UIIcon>(0);
    m_clearText->Initialize("Assets/texture/OutGame/GameClear_Text.DDS", 1000.0f, 900.0f);
    m_clearText->m_transform.m_localPosition = {0.0f, 400.0f, 0.0f};
    auto clearTextAnimation = std::make_unique<UIScaleAnimation>();
    clearTextAnimation->SetParameter(Vector3{0.1f, 0.1f, 1.0f}, Vector3{1.5f, 1.5f, 1.0f}, 1.0f, EasingType::Linear, LoopMode::Once);
    auto clearTextColor = std::make_unique<UIColorAnimation>();
    clearTextColor->SetParameter(Vector4{1.0f, 1.0f, 1.0f, 0.0f}, Vector4{1.0f, 1.0f, 1.0f, 1.0f}, 1.0f, EasingType::Linear, LoopMode::Once);
    m_clearText->AddAnimation(Hash32("clearTextAnimation"), std::move(clearTextAnimation));
    m_clearText->AddAnimation(Hash32("clearTextAnimation"), std::move(clearTextColor));
    

    m_pushText = m_uiCanvas->CreateUI<UIIcon>(1);
    m_pushText->Initialize("Assets/texture/OutGame/PushA_Text.DDS", 500.0f, 400.0f);
    m_pushText->m_transform.m_localPosition = {0.0f, -450.0f, 0.0f};
    auto pushTextAnimation = std::make_unique<UIColorAnimation>();
    pushTextAnimation->SetParameter(Vector4{1.0f, 1.0f, 1.0f, 0.0f}, Vector4{1.0f, 1.0f, 1.0f, 1.0f}, 2.0f ,EasingType::Linear, LoopMode::Loop);
    m_pushText->AddAnimation(Hash32("pushTextAnimation"), std::move(pushTextAnimation));
    

    m_coinTexture = m_uiCanvas->CreateUI<UIIcon>(2);
    m_coinTexture->Initialize("Assets/texture/Coin/coin.DDS", 100.0f, 100.0f);
    m_coinTexture->m_transform.m_localPosition = {-350.0f, 200.0f, 0.0f};

    m_coinCountMark = m_uiCanvas->CreateUI<UIIcon>(3);
    m_coinCountMark->Initialize("Assets/texture/Coin/CoinCountMark.DDS", 100.0f, 100.0f);
    m_coinCountMark->m_transform.m_localPosition = {-275.0f, 195.0f, 0.0f};


    m_enemyTexture = m_uiCanvas->CreateUI<UIIcon>(4);
    m_enemyTexture->Initialize("Assets/texture/Result/SlimeIcon.DDS", 500.0f, 500.0f);
    m_enemyTexture->m_transform.m_localPosition = {100.0f, 200.0f, 0.0f};


    m_enemyCountMark = m_uiCanvas->CreateUI<UIIcon>(5);
    m_enemyCountMark->Initialize("Assets/texture/Coin/CoinCountMark.DDS", 100.0f, 100.0f);
    m_enemyCountMark->m_transform.m_localPosition = {200.0f, 195.0f, 0.0f};


    m_enemyType2Texture = m_uiCanvas->CreateUI<UIIcon>(6);
    m_enemyType2Texture->Initialize("Assets/texture/Result/StoneIcon.DDS", 500.0f, 500.0f);
    m_enemyType2Texture->m_transform.m_localPosition = {-350.0f, 100.0f, 0.0f};


    m_enemyType2CountMark = m_uiCanvas->CreateUI<UIIcon>(7);
    m_enemyType2CountMark->Initialize("Assets/texture/Coin/CoinCountMark.DDS", 100.0f, 100.0f);
    m_enemyType2CountMark->m_transform.m_localPosition = {-275.0f, 95.0f, 0.0f};


    m_bossTexture = m_uiCanvas->CreateUI<UIIcon>(8);
    m_bossTexture->Initialize("Assets/texture/Result/BullIcon.DDS", 500.0f, 500.0f);
    m_bossTexture->m_transform.m_localPosition = {100.0f, 100.0f, 0.0f};


    m_bossCountMark = m_uiCanvas->CreateUI<UIIcon>(9);
    m_bossCountMark->Initialize("Assets/texture/Coin/CoinCountMark.DDS", 100.0f, 100.0f);
    m_bossCountMark->m_transform.m_localPosition = {200.0f, 95.0f,0.0f};


    m_scoreText = m_uiCanvas->CreateUI<UIIcon>(10);
    m_scoreText->Initialize("Assets/texture/OutGame/Score.DDS", 300.0f, 300.0f);
    m_scoreText->m_transform.m_localPosition = {-150.0f, 0.0f, 0.0f};


    m_coinUIDigit = m_uiCanvas->CreateUI<UIDigit>(11);
    m_coinUIDigit->Initialize("Assets/texture/Coin/CoinCount", 2 , 0, 100.0f, 100.0f, COIN_TEXT_POSITION,COIN_TEXT_SCALE, Quaternion::Identity);


    m_enemyUIDigit = m_uiCanvas->CreateUI<UIDigit>(12);
    m_enemyUIDigit->Initialize("Assets/texture/Coin/CoinCount", 2, 0, 100.0f, 100.0f, ENEMY_TEXT_POSITION, Vector3::One,Quaternion::Identity);


    m_enemyType2UIDigit = m_uiCanvas->CreateUI<UIDigit>(13);
    m_enemyType2UIDigit->Initialize("Assets/texture/Coin/CoinCount", 2, 0, 100.0f, 100.0f, ENEMYTYPE2_TEXT_POSITION, Vector3::One, Quaternion::Identity);


    m_bossUIDigit = m_uiCanvas->CreateUI<UIDigit>(14);
    m_bossUIDigit->Initialize("Assets/texture/Coin/CoinCount", 2, 0, 100.0f, 100.0f, BOSS_TEXT_POSITION, Vector3::One, Quaternion::Identity);


    m_scoreUIDigit = m_uiCanvas->CreateUI<UIDigit>(15);
    m_scoreUIDigit->Initialize("Assets/texture/Coin/CoinCount", 5, 0, 100.0f, 100.0f, SCORE_UI_POSITION, Vector3::One,Quaternion::Identity);


}

void GameClear::ResultCoin()
{
    if (m_coinTotal < m_coinCount->GetTotalCount())
    {
        m_coinTotal++;
        m_coinUIDigit->SetNumber(m_coinTotal);
    }

    else if (m_coinTotal == m_coinCount->GetTotalCount() && m_coinTime > 0.0f)
    {
        m_coinTotal == m_coinCount->GetTotalCount();
        m_coinTime -= g_gameTime->GetFrameDeltaTime();
    }
}

void GameClear::ResultEnemy()
{
    if (m_coinTime > 0.0f)
    {
        return;
    }


    if (m_enemyTotal < m_killCount->GetEnemyCount())
    {
        m_enemyTotal++;
        m_enemyUIDigit->SetNumber(m_enemyTotal);
    }

    else if (m_enemyTotal == m_killCount->GetEnemyCount() && m_enemyTime > 0.0f)
    {
        m_enemyTotal = m_killCount->GetEnemyCount();
        m_enemyTime -= g_gameTime->GetFrameDeltaTime();
    }

    else if (m_enemyType2Total < m_killCount->GetEnemyType2Count())
    {
        m_enemyType2Total++;
        m_enemyType2UIDigit->SetNumber(m_enemyType2Total);
    }

    else if (m_enemyType2Total == m_killCount->GetEnemyType2Count() && m_enemyType2Time > 0.0f)
    {
        m_enemyType2Total = m_killCount->GetEnemyType2Count();
        m_enemyType2Time -= g_gameTime->GetFrameDeltaTime();
    }

    else if (m_bossTotal < m_killCount->GetBossCount())
    {
        m_bossTotal++;
        m_bossUIDigit->SetNumber(m_bossTotal);
    }

    else if (m_bossTotal == m_killCount->GetBossCount() && m_bossTime > 0.0f)
    {
        m_bossTotal = m_killCount->GetBossCount();
        m_bossTime -= g_gameTime->GetFrameDeltaTime();
    }
}

void GameClear::ResultScore()
{
    if (m_bossTime > 0.0f)
    {
        return;
    }

    else if (m_scoreTotal < m_score->GetScore())
    {
        m_scoreTotal += 100;
        m_scoreUIDigit->SetNumber(m_scoreTotal);
    }

    else if (m_scoreTotal == m_score->GetScore() && m_scoreTime > 0.0f)
    {
        m_scoreTotal = m_score->GetScore();
        m_scoreTime -= g_gameTime->GetFrameDeltaTime();
    }
}
