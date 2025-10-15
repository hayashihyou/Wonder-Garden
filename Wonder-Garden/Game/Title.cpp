#include "stdafx.h"
#include "Title.h"
#include "Game.h"

bool Title::Start()
{
	m_title.Init("Assets/texture/Title.DDS", 1920.0f, 1080.0f);
	m_title.Update();

	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		NewGO<Game>(0,"Game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	m_title.Draw(rc);
} 
