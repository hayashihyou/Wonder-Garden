#pragma once

#include "Level3DRender/LevelRender.h"
class Player;
class Enemy;
class Stage;
class GameCamera;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	Player* m_player = nullptr;
	Enemy* m_enemy = nullptr;
	Stage* m_stage = nullptr;
	GameCamera* m_gameCamera = nullptr;
	Vector3 m_pos;
};

