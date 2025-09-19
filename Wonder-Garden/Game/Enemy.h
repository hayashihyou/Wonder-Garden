#pragma once
#include "CharacterBase.h"

class Player;
class Enemy : public CharacterBase
{
public:
	Enemy() {};

public:
	PhysicsStaticObject m_enemyCollision;

private:
	~Enemy() {};
	bool Start();
	void Rotation();
	void Update();
	void Render(RenderContext& rc);
	void ManagerState();
	void PlayAnimation();

	void HP()override;
	void Attack()override;
	void Move()override;

private:
	/// <summary>
	/// ìGÇÃèÛë‘
	/// </summary>
	enum EnAnimationClip
	{
		enAnimationClip_Idle,
		enAnimationClip_Attack,
		enAnimationClip_JumpDie,
		enAnimationClip_AttackDie,
		enAnimationClip_Num,
	};

	enum EnEnemyState
	{
		enEnemyState_Idle,
		enEnemyState_Attack,
		enEnemyState_Move,
		enEnemyState_Die,
		enEnemyState_Num,
	};

	ModelRender m_enemyModel;
	AnimationClip m_animationClips[enAnimationClip_Num];
	EnEnemyState m_enemyState = enEnemyState_Idle;
	Quaternion m_rot;
	Player* m_player;

	Vector3 m_pos;
	Vector3 toPlayer;
	Vector3 toPlayerDir;

	float disToPlayer;
};

