#pragma once
#include "CharacterBase.h"

class Player;
class AttackCollision;
class IEnemyType2State;

class EnemyType2 : public CharacterBase
{
public:
    enum EnEnemyType2AnimationClip
    {
        enAnimationClip_Idle,
        enAnimationClip_Attack,
        enAnimationClip_AttackDead,
        enAnimationClip_JumpDead,
        enAnimationClip_Num
    };

    enum EnDeadReason
    {
        enDeadReason_None,
        enDeadReason_Jump,
        enDeadReason_Punch,
    };

public:
    EnemyType2(){};
    ~EnemyType2();
    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;

    void SetAttack(bool attack) { m_isAttackFlag = attack; }
    void SetDead(bool dead) { m_isDeadFlag = dead; }
    void SetPosition(Vector3 position) { m_position = position; }
    void SetRotation(Quaternion rotation) { m_rotation = rotation; }
    void SetCollision(AttackCollision* collision) { m_attackCollision = collision; }


    Vector3 GetPosition() { return m_position; };
    Vector3 GetToPlayer() { return toPlayerDir; };
    float GetDisToPlayer() { return disToPlayer; };

    void DamagePunch(int damageAmount);
    void DamageReceiveHead(int damageAmount);
    void Damage(int damageAmount, int reason);

    void Rotation();
    void MakeCollision();
    void UpdateChangeState();

    void HP() override;
    void Attack() override{};
    void Move() override{};

public:
    CollisionObject* GetCollision() { return enemyType2Collision; }
    CollisionObject* GetHeadCollision() { return enemyType2Collision; }

    ModelRender* GetModelRender() { return &m_enemyType2Model; }
    EnDeadReason GetDeadReason() { return m_deadReason; }

    bool IsAttack() { return m_isAttackFlag; }
    bool IsDead() { return m_isDeadFlag; }

    AttackCollision* GetAttackCollision() { return m_attackCollision; }
    Transform* GetTransform() { return &m_transform; }

private:
    ModelRender m_enemyType2Model;
    AnimationClip m_animationClips[enAnimationClip_Num];
    AttackCollision* m_enemyType2Attack = nullptr;

    CollisionObject* enemyType2Collision = nullptr;
    CollisionObject* enemyType2JumpCollision = nullptr;
    Player* m_player;
    AttackCollision* m_attackCollision;

    uint32_t m_enemyType2State;
    std::map<uint32_t, IEnemyType2State*> m_stateList;

    EnDeadReason m_deadReason = enDeadReason_None;

    Vector3 m_position;
    Vector3 m_colPos;
    Vector3 m_colJumpPos;
    Vector3 toPlayer;
    Vector3 toPlayerDir;
    Quaternion m_rotation;

    float disToPlayer;
    float m_attackCoolTime = 1.0f;

    bool m_isDeadFlag = false;
    bool m_isAttackFlag = false;
};
