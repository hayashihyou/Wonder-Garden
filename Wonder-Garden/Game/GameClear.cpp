#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"

bool GameClear::Start()
{
	m_gameClear.Init("Assets/texture/GameClear.DDS",1920.0f,1080.0f);
	m_gameClear.Update();

	return true;
}

void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		NewGO<Title>(0,"Title");
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_gameClear.Draw(rc);
}