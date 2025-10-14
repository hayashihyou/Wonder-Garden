#pragma once
#include "CharacterBase.h"

class Player;
class AttackCollision;
class EnemyType2 : public CharacterBase
{
public:
	EnemyType2() {};

public:

private:
	~EnemyType2() {};
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void PlayAnimation();
	void HitPunch();
	void HitJump();

	void HP()override;
	void Attack()override;
	void Move()override;

private:
	enum EnAnimationClip
	{
		enAnimationClip_Idle,
		enAnimationClip_Attack,
		enAnimationClip_AttackDead,
		enAnimationClip_JumpDead,
		enAnimationClip_Num
	};

private:
	ModelRender m_enemyType2Model;
	AnimationClip m_animationClips[enAnimationClip_Num];
	CollisionObject enemyType2Collision;
	CollisionObject enemyType2JumpCollision;
	Player* m_player;
	AttackCollision* m_attackCollision;

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

