#include "stdafx.h"
#include "GameOver.h"

bool GameOver::Start()
{
	m_gameOver.Init("Assets/texture/naniya.DDS", 1920.0f, 1080.0f);
	m_gameOver.Update();

	return true;
}

void GameOver::Update()
{
}

void GameOver::Render(RenderContext& rc)
{
	m_gameOver.Draw(rc);
}