#pragma once
#include "CharacterBase.h"

class Player;
class IBossState;
class AttackCollision;

class Boss : public CharacterBase
{
public:
    enum EnDeadReason
    {
        enDeadReason_None,
        enDeadReason_Jump,
        enDeadReason_Punch,
    };

    enum enBossAnimationClip
    {
        enAnimationClip_Idle,
        enAnimationClip_Walk,
        enAnimationClip_Attack,
        enAnimationClip_Attack2,
        enAnimationClip_JumpAttack,
        enAnimationClip_Damage,
        enAnimationClip_Dead,
        enAnimationClip_Num,
    };

public:
    Boss(){};
    ~Boss();
    bool Start();
    void Update();
    void Render(RenderContext& rc);
    void AttackFlag();
    void UpdateChangeState();

    void HP() override;
    void Attack() override;
    void Move() override{};
    void SetPosition(Vector3 position) { m_position = position; }
    void SetAttack(bool attack);
    void SetDead(bool dead);
    Vector3 GetPosition() { return m_position; };

    void DamagePunch(int damageAmount);
    void DamageReceiveHead(int damageAmount);
    void Damage(int damageAmount, int reason);

public:
    ModelRender* GetModelRender() { return &m_bossModel; }
    EnDeadReason GetDeadReason() { return m_deadReason; }
    bool IsDead() { return isDeadFlag; }
    bool IsAttack() { return isAttackFlag; }

    CollisionObject* GetCollision() { return m_bossCollision; }
    CollisionObject* GetHeadCollision() { return m_bossHeadCollision; }

private:
    ModelRender m_bossModel;
    AnimationClip m_animationClips[enAnimationClip_Num];

    bool isDeadFlag = false;

    Vector3 m_position;
    Vector3 m_colPos;
    Quaternion m_rot;
    Vector3 m_scale;
    Vector3 toPlayer;
    CollisionObject* m_bossCollision = nullptr;
    CollisionObject* m_bossHeadCollision = nullptr;
    Player* m_player = nullptr;
    AttackCollision* m_attackCollision = nullptr;

    uint32_t m_currentStateId;
    std::map<uint32_t, IBossState*> m_stateMap;
    EnDeadReason m_deadReason = enDeadReason_None;

    float disToPlayer;
    bool isAttackFlag = false;
};
