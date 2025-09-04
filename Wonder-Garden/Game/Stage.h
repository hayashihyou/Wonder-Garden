#pragma once
class Stage : public IGameObject
{
public:
	Stage() {};
private:
	~Stage() {};
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	ModelRender m_stage;
	PhysicsStaticObject physicsStaticObject;
};

