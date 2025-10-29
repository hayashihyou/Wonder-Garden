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
	void SetDeadFlag(bool dead);
    void SetPosition(Vector3 pos) { m_pos = pos; };

    Vector3 GetPosition()
    {
        return m_pos;
    }

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
	/// 敵の状態
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
    AttackCollision* m_attackCollision = nullptr; 
    AttackCollision* enemyAttack = nullptr;

	bool isStopMove = false;

private:
    ~Enemy();
	bool Start();
	void Rotation();
	void Update();
	void Render(RenderContext& rc);
    void MakeAttackCollision();
	void ManagerState();
	void UpdateChangeState();

	void HP()override;
	void Attack()override;
	void Move()override;

public:
    CollisionObject* GetColision() { return enemyCollisionObject; }
    CollisionObject* GetHeadCollision() { return enemyJumpCollision; }


public:
    void DamagePunch(int damageAmount);
    void DamageReceiveHead(int damageAmount);
    void Damge(int damageAmount, int reason);


private:
    enum EnDeadReason
    {
        enDeadReason_None,
        enDeadReason_Jump,
        enDeadReason_Punch,
    };

private:

	AnimationClip m_animationClips[enAnimationClip_Num];
	EnEnemyState m_enemyState = enEnemyState_Idle;
	CollisionObject* enemyCollisionObject = nullptr;
    CollisionObject* enemyJumpCollision = nullptr;
	Quaternion m_rot;
	Player* m_player;
	IEnemyState* m_currentState = nullptr;
	IEnemyState* m_stateList[enEnemyState_Num];
    EnDeadReason m_deadReason = enDeadReason_None;

	Vector3 m_pos;
	Vector3 m_colPos;
	Vector3 m_colJumpPos;
	Vector3 toPlayer;
	Vector3 toPlayerDir;
	Vector3 currentToPlayer;
    const Vector3 attackCol = {0,30,0};

    int checkCollision = 10; //誰の当たり判定か確認する変数

	float disToPlayer;
    float m_attackCoolTimer = 2.0f;

	bool isAttack = false;
	bool isDead = false;
};

