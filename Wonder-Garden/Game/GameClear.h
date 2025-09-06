#pragma once
class GameClear :public IGameObject
{
public:
	GameClear() {};
private:
	~GameClear() {};
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	SpriteRender m_gameClear;
};

