#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"

bool GameOver::Start()
{
	m_gameOver.Init("Assets/texture/GameOver.DDS", 1920.0f, 1080.0f);
	m_gameOver.Update();

	return true;
}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		NewGO<Title>(0, "Title");
		DeleteGO(this);
	}

}

void GameOver::Render(RenderContext& rc)
{
	m_gameOver.Draw(rc);
}