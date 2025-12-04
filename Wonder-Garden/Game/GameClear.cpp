#include "stdafx.h"

#include "GameClear.h"
#include "Title.h"

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
}

void GameClear::Render(RenderContext& rc)
{
    m_gameClearSprite.Draw(rc);
}

void GameClear::Init()
{
    m_gameClearSprite.Init("Assets/texture/GameClear.DDS", 1920.0f, 1080.0f);
    m_gameClearSprite.Update();
}
