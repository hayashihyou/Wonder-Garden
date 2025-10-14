#pragma once
#include "CharacterBase.h"

class Player;
class AttackCollision;
class IEnemyType2State;

class EnemyType2 : public CharacterBase
{
public:
	EnemyType2() {};

public:
	enum EnEnemyType2AnimationClip
	{
		enAnimationClip_Idle,
		enAnimationClip_Attack,
		enAnimationClip_AttackDead,
		enAnimationClip_JumpDead,
		enAnimationClip_Num
	};

public:
	ModelRender m_enemyType2Model;
	AnimationClip m_animationClips[enAnimationClip_Num];

private:
	~EnemyType2() {};
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Rotation();
	void AttackFlag();
	void UpdateChangeState();
	void ManagerState();
	void HitPunch();
	void HitJump();

	void HP()override;
	void Attack()override;
	void Move()override;

private:
	enum EnEnemyType2State
	{
		enEnemyType2State_Idle,
		enEnemyType2State_Attack,
		enEnemyType2State_AttackDead,
		enEnemyType2State_JumpDead,
		enEnemyType2State_Num,
	};

private:
	CollisionObject enemyType2Collision;
	CollisionObject enemyType2JumpCollision;
	Player* m_player;
	AttackCollision* m_attackCollision;
	EnEnemyType2State m_enemyType2State = enEnemyType2State_Idle;
	IEnemyType2State* m_currentState = nullptr;
	IEnemyType2State* m_stateList[enEnemyType2State_Num];

	Vector3 m_pos;
	Vector3 m_colPos;
	Vector3 m_colJumpPos;
	Vector3 toPlayer;
	Vector3 toPlayerDir;
	Quaternion m_rot;

	float disToPlayer;

	bool isDeadFlag = false;
	bool isAttackFlag = false;

};

