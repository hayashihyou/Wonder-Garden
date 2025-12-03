#include "stdafx.h"

#include "Game.h"
#include "SoundManager.h"
#include "Title.h"

bool Title::Start()
{
    InitSprite();

    SoundManager::GetInstance().PlayBGM(SoundManager::SoundNumber::TitleBGM);

    return true;
}

void Title::Update()
{
    // Bボタンが押されたらゲームシーンへ移行
    if (g_pad[0]->IsTrigger(enButtonB))
    {
        // 決定SE再生
        SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::SystemDecisionSE, 0.7f, false);

        NewGO<Game>(0, "Game");
        DeleteGO(this);
    }
}

void Title::Render(RenderContext& rc)
{
    m_titleSprite.Draw(rc);
}

void Title::InitSprite()
{
    m_titleSprite.Init("Assets/texture/Title.DDS", 1920.0f, 1080.0f);
    m_titleSprite.Update();
}
