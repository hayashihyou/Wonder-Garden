#include "stdafx.h"

#include "GameOver.h"
#include "Title.h"

namespace
{
    const float IMAGE_WIDTH = 1920.0f;  // 画像の幅
    const float IMAGE_HEIGHT = 1080.0f; // 画像の高さ
} // namespace

bool GameOver::Start()
{
    // 初期化
    Init();

    return true;
}

void GameOver::Update()
{
    // Bボタンが押されたらタイトルに戻る
    if (g_pad[0]->IsTrigger(enButtonB))
    {
        NewGO<Title>(0, "Title");
        DeleteGO(this);
    }
}

void GameOver::Render(RenderContext& rc)
{
    m_gameOverSprite.Draw(rc);
}

void GameOver::Init()
{
    m_gameOverSprite.Init("Assets/texture/GameOver.DDS", IMAGE_WIDTH, IMAGE_HEIGHT);
    m_gameOverSprite.Update();
}
