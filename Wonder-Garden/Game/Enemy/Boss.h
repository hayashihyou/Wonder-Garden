#pragma once
#include "CharacterBase.h"

class Player;
class IBossState;
class AttackCollision;

class Boss : public CharacterBase
{
public:
	Boss() {};
	void SetAttack(bool attack);
	void SetDead(bool dead);
    Vector3 GetPosition() { return m_pos; };

    void DamagePunch(int damageAmount);
    void DamageReceiveHead(int damageAmount);
    void Damage(int damageAmount, int reason);

public:
	enum enBossAnimationClip
	{
		enAnimationClip_Idle,
		enAnimationClip_Attack,
		enAnimationClip_Dead,
		enAnimationClip_Num,
	};

public:
	ModelRender m_bossModel;
	AnimationClip m_animationClips[enAnimationClip_Num];

    CollisionObject* GetCollision() { return m_bossCollision; }
    CollisionObject* GetHeadCollision() { return m_bossHeadCollision; }

	bool isDeadFlag = false;

private:
	~Boss() ;
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void AttackFlag();
	void ManagerState();
	void UpdateChangeState();

	void HP() override;
	void Attack() override;
	void Move() override {};

private:
	enum EnBossState
	{
		enBossState_Idle,
		enBossState_Attack,
		enBossState_Dead,
		enBossState_Num,
	};

    enum EnDeadReason
    {
        enDeadReason_None,
        enDeadReason_Jump,
        enDeadReason_Punch,
    };

private:
	Vector3 m_pos;
	Vector3 m_colPos;
	Quaternion m_rot;
	Vector3 m_scale;
	Vector3 toPlayer;
	CollisionObject* m_bossCollision = nullptr;
	CollisionObject* m_bossHeadCollision = nullptr;
	Player* m_player = nullptr;
	AttackCollision* m_attackCollision = nullptr;
	IBossState* m_stateList[enBossState_Num];
	IBossState* m_currentState = nullptr;
    EnDeadReason m_deadReason = enDeadReason_None;

	float disToPlayer;
	bool isAttackFlag = false;
};
