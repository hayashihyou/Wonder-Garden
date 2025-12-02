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
    void UpdateChangeState();
    void Rotation();

    void HP() override;
    void Attack() override{};
    void Move() override{};

    void DamagePunch(int damageAmount);
    void DamageReceiveHead(int damageAmount);
    void Damage(int damageAmount, int reason);

public:
    void SetPosition(Vector3 position) { m_position = position; }
    void SetRotation(Quaternion rotation) { m_rotation = rotation; }
    void SetAttackCoolTime(float time) { m_attackCoolTime = time; }
    void SetAttack(bool attack) { m_isAttackFlag = attack; }
    void SetDead(bool dead) { m_isDeadFlag = dead; }

public:
    ModelRender* GetModelRender() { return &m_bossModel; }
    EnDeadReason GetDeadReason() { return m_deadReason; }
    CollisionObject* GetCollision() { return m_bossCollision; }
    CollisionObject* GetHeadCollision() { return m_bossHeadCollision; }

    Vector3 GetPosition() { return m_position; }
    Vector3 GetToPlayer() { return toPlayer; }
    float GetDisToPlayer() { return disToPlayer; }
    float GetAttackCoolTime() { return m_attackCoolTime; }
    bool GetAttackFlag() { return m_isAttackFlag; }
    bool IsDead() { return m_isDeadFlag; }
    bool IsAttack() { return m_isAttackFlag; }

private:
    Player* m_player = nullptr;
    ModelRender m_bossModel;
    EnDeadReason m_deadReason = enDeadReason_None;
    AnimationClip m_animationClips[enAnimationClip_Num];
    CollisionObject* m_bossCollision = nullptr;
    CollisionObject* m_bossHeadCollision = nullptr;
    AttackCollision* m_attackCollision = nullptr;
    uint32_t m_currentStateId;
    std::map<uint32_t, IBossState*> m_stateMap;

    Vector3 m_position;
    Vector3 m_colPosition;
    Quaternion m_rotation;
    Vector3 m_scale;
    Vector3 toPlayer;

    float disToPlayer;
    float m_attackCoolTime = 5.0f;
    bool m_isAttackFlag = false;
    bool m_isDeadFlag = false;
};
