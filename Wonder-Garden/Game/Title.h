#pragma once
class Title : public IGameObject
{
public:
	Title() {};

private:
	~Title() {};
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_title;
};

