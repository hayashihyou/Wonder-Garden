#include "stdafx.h"
#include "GameClear.h"

bool GameClear::Start()
{
	m_gameClear.Init("Assets/texture/naniya2.DDS",1920.0f,1080.0f);
	m_gameClear.Update();

	return true;
}

void GameClear::Update()
{

}

void GameClear::Render(RenderContext& rc)
{
	m_gameClear.Draw(rc);
}