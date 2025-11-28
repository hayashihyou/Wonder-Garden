#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "SoundManager.h"

bool Title::Start()
{
	m_title.Init("Assets/texture/Title.DDS", 1920.0f, 1080.0f);
	m_title.Update();

    // タイトルBGM再生
    SoundManager::GetInstance().PlayBGM(SoundManager::SoundNumber::TitleBGM);

	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
        // 決定SE再生
        SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::SystemDecisionSE, 0.7f, false);

		NewGO<Game>(0,"Game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	m_title.Draw(rc);
} 
