#pragma once
#include "CharacterBase.h"

class Player;
class IEnemyState;
class AttackCollision;
class Enemy : public CharacterBase
{
public:
	Enemy() {};
	void SetAttackFlag(bool attack);

public:
	enum EnEnemyAnimationClip
	{
		enAnimationClip_Idle,
		enAnimationClip_Attack,
		enAnimationClip_JumpDead,
		enAnimationClip_AttackDead,
		enAnimationClip_Num,
	};

	/// <summary>
	/// ìGÇÃèÛë‘
	/// </summary>
	enum EnEnemyState
	{
		enEnemyState_Idle,
		enEnemyState_Attack,
		enEnemyState_JumpDead,
		enEnemyState_AttackDead,
		enEnemyState_Num,
	};

public:
	PhysicsStaticObject m_enemyCollision;
	ModelRender m_enemyModel;

	bool isStopMove = false;

private:
	~Enemy() {};
	bool Start();
	void Rotation();
	void Update();
	void Render(RenderContext& rc);
	void JumpHit();
	void PunchHit();
	void ManagerState();
	void UpdateChangeState();

	void HP()override;
	void Attack()override;
	void Move()override;

private:

	AnimationClip m_animationClips[enAnimationClip_Num];
	EnEnemyState m_enemyState = enEnemyState_Idle;
	CollisionObject enemyCollisionObject;
	CollisionObject enemyJumpCollision;
	Quaternion m_rot;
	Player* m_player;
	AttackCollision* m_attackCollision = nullptr;
	IEnemyState* m_currentState = nullptr;
	IEnemyState* m_stateList[enEnemyState_Num];

	Vector3 m_pos;
	Vector3 m_colPos;
	Vector3 m_colJumpPos;
	Vector3 toPlayer;
	Vector3 toPlayerDir;
	Vector3 currentToPlayer;

	float disToPlayer;

	bool isAttack = false;
	bool isDead = false;
};

