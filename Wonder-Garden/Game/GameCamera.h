#pragma once

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera() {};
private:
	~GameCamera() {};
	bool Start();
	void Update();

private:
	Player* m_player = nullptr;
	Vector3 m_toCameraPos;
};

