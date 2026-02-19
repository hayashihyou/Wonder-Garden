#include "stdafx.h"

#include "GameClear.h"
#include "Title.h"
#include "UI/UIBase.h"
#include <Util/CRC32.h>

namespace
{
    const Vector3 TEXTURE_POSITION = {0.0f, 450.0f, 0.0f};
    const Vector3 PUSH_TEXTURE_POSITION = {0.0f, -450.0f, 0.0f};
    const Vector3 TEXTURE_SCALE = {2.5f, 2.5f, 1.0f};
    const Vector3 PUSH_TEXTURE_SCALE = {2.0f, 2.0f, 1.0f};
} // namespace

GameClear::GameClear() {}

GameClear::~GameClear() {}

bool GameClear::Start()
{
    // 初期化
    Init();

    return true;
}

void GameClear::Update()
{
    // Bボタンでタイトルへ戻る
    if (g_pad[0]->IsTrigger(enButtonB))
    {
        NewGO<Title>(0, "Title");
        DeleteGO(this);
    }

    m_uiCanvas->Update();
}

void GameClear::Render(RenderContext& rc)
{
    m_uiCanvas->Render(rc);
}

void GameClear::Init()
{
    m_uiCanvas = std::make_unique<UICanvas>();

    m_gameClear = m_uiCanvas->CreateUI<UIIcon>(0);
    m_gameClear->Initialize("Assets/texture/OutGame/GameClear.DDS", 1920.0f, 1080.0f);
    m_gameClear->m_transform.m_localPosition = Vector3::Zero;

    m_clearText = m_uiCanvas->CreateUI<UIIcon>(1);
    m_clearText->Initialize("Assets/texture/OutGame/GameClear_Text.DDS", 900.0f, 800.0f);
    m_clearText->m_transform.m_localPosition = {0.0f, 450.0f, 0.0f};
    auto clearTextAnimation = std::make_unique<UIScaleAnimation>();
    clearTextAnimation->SetParameter(Vector3{0.1f, 0.1f, 1.0f}, Vector3{1.25f, 1.25f, 1.0f}, 2.0f, EasingType::Linear, LoopMode::Once);
    m_clearText->AddAnimation(Hash32("clearTextAnimation"), std::move(clearTextAnimation));
    m_clearText->PlayAnimation();

    m_pushText = m_uiCanvas->CreateUI<UIIcon>(2);
    m_pushText->Initialize("Assets/texture/OutGame/PushA_Text.DDS", 800.0f, 700.0f);
    m_pushText->m_transform.m_localPosition = {0.0f, -450.0f, 0.0f};
    auto pushTextAnimation = std::make_unique<UIColorAnimation>();
    pushTextAnimation->SetParameter(Vector4{1.0f, 1.0f, 1.0f, 0.0f}, Vector4{1.0f, 1.0f, 1.0f, 1.0f}, 2.0f ,EasingType::Linear, LoopMode::Loop);
    m_pushText->AddAnimation(Hash32("pushTextAnimation"), std::move(pushTextAnimation));
    m_pushText->PlayAnimation();

    m_coinTexture = m_uiCanvas->CreateUI<UIIcon>(3);
    m_coinTexture->Initialize("Assets/texture/Coin/coin.DDS", 100.0f, 100.0f);
    m_coinTexture->m_transform.m_localPosition = {-100.0f, 100.0f, 0.0f};

    m_coinCountMark = m_uiCanvas->CreateUI<UIIcon>(4);
    m_coinCountMark->Initialize("Assets/texture/Coin/CoinCountMark.DDS", 100.0f, 100.0f);
    m_coinCountMark->m_transform.m_localPosition = {-25.0f, 95.0f, 0.0f};
}
