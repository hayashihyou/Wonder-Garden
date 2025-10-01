#pragma once
#include "CharacterBase.h"

class EnemyType2 : public CharacterBase
{
public:
	EnemyType2() {};

private:
	~EnemyType2() {};
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void PlayAnimation();

	void HP()override;
	void Attack()override;
	void Move()override;

private:
	enum EnAnimationClip
	{
		enAnimationClip_Idle,
		enAnimationClip_Num
	};

private:
	ModelRender m_enemyType2Model;
	AnimationClip m_animationClips[enAnimationClip_Num];
	CollisionObject m_enemyType2Collison;

	Vector3 m_pos;
	Vector3 m_colPos;
	Vector3 m_colJumpPos;
	Quaternion m_rot;


};

