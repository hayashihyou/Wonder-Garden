#pragma once
class GameOver:public IGameObject
{
public:
	GameOver() {};
private:
	~GameOver() {};
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_gameOver;
};

