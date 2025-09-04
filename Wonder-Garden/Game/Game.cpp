#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "GameCamera.h"


Game::Game()
{

};

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_enemy);
	DeleteGO(m_stage);
	DeleteGO(m_gameCamera);
}

bool Game::Start()
{
	m_player = NewGO<Player>(0, "Player");
	m_enemy = NewGO<Enemy>(0, "Enemy");
	m_stage = NewGO<Stage>(0, "Stage");
	m_gameCamera = NewGO<GameCamera>(0, "GameCamera");

	//コメントアウトする。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{
	
}