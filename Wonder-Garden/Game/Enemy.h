#pragma once
#include "CharacterBase.h"

class Enemy : public CharacterBase
{
public:
	Enemy() {};

private:
	~Enemy() {};
	bool Start();
	void Rotation();
	void Update();
	void Render(RenderContext& rc);

	void HP()override;
	void Attack()override;
	void Move()override;

	ModelRender m_enemyModel;
	PhysicsStaticObject physicsStaticObject;
	Quaternion m_rot;

	Vector3 pos;
};

