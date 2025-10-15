#pragma once

class Player;
class StarCounter;

class Star : public IGameObject
{
public:
	Star() {};

public:
	ModelRender m_star;

private:
	~Star() {};
	bool Start();
	void Update();
	void GetFlag();
	void Rotation();
	void Render(RenderContext& rc);

private:
	Vector3 m_pos;
	Vector3 toPlayer;
	Quaternion m_rot;
	Player* m_player = nullptr;
	StarCounter* m_starCounter = nullptr;

	float disToPlayer;
};

