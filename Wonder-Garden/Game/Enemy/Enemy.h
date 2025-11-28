#pragma once
#include "CharacterBase.h"

class Player;
class EnemyStatePattern;
class AttackCollision;
class Enemy : public CharacterBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Enemy(){};


    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Enemy();


    /// <summary>
    /// スタート
    /// </summary>
    /// <returns></returns>
    bool Start();


    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();


    /// <summary>
    /// 描画処理
    /// </summary>
    /// <param name="rc"></param>
    void Render(RenderContext& rc);


public:
    enum EnDeadReason
    {
        enDeadReason_None,
        enDeadReason_Jump,
        enDeadReason_Punch,
    };

    enum EnAnimationClip
    {
        enAnimationClip_Idle,
        enAnimationClip_Attack,
        enAnimationClip_JumpDead,
        enAnimationClip_AttackDead,
        enAnimationClip_Num,
    };

   


public:
    /// <summary>
    /// 位置を保持
    /// </summary>
    /// <param name="pos"></param>
    void SetPosition(Vector3 pos) { m_position = pos; };

   
    /// <summary>
    /// 攻撃状態の保持
    /// </summary>
    /// <param name="attack"></param>
    void SetAttackFlag(bool attack) { isAttack = attack; }


    /// <summary>
    /// 死んでる状態の保持
    /// </summary>
    /// <param name="dead"></param>
    void SetDeadFlag(bool dead) { isDead = dead; }


public:
    /// <summary>
    /// 位置を取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetPosition() { return m_position; }


    /// <summary>
    /// 敵とプレイヤーとの距離を取得
    /// </summary>
    Vector3 GetToPlayer() { return m_toPlayer; }


    /// <summary>
    /// 敵とプレイヤーとの距離の長さを取得
    /// </summary>
    /// <returns></returns>
    float GetDisToPlayer() { return m_disToPlayer; }


    /// <summary>
    /// 当たり判定の取得
    /// </summary>
    /// <returns></returns>
    CollisionObject* GetColision() { return enemyCollisionObject; }


     /// <summary>
    /// プレイヤーに頭から踏まれる当たり判定の取得
    /// </summary>
    /// <returns></returns>
    CollisionObject* GetHeadCollision() { return enemyJumpCollision; }

    /// <summary>
    /// モデルを取得
    /// </summary>
    /// <returns></returns>
    ModelRender* GetModel() { return &m_enemyModel; }

    EnDeadReason GetDeadReason() { return m_deadReason; }

    bool IsDead() { return isDead; }


public:
    PhysicsStaticObject m_enemyCollision;
    ModelRender m_enemyModel;
    AttackCollision* m_attackCollision = nullptr;
    AttackCollision* enemyAttack = nullptr;

    bool isStopMove = false;


private:
    void Rotation();
    void HP() override;
    void Attack() override{}; 
    void Move() override{};


public:
    void DamagePunch(int damageAmount);
    void DamageReceiveHead(int damageAmount);
    void Damge(int damageAmount, int reason);

private:
    AnimationClip m_animationClips[enAnimationClip_Num];
    CollisionObject* enemyCollisionObject = nullptr;
    CollisionObject* enemyJumpCollision = nullptr;
    Quaternion m_rotation;
    Player* m_player;
    EnemyStatePattern* m_enemyStatePattern;
    EnDeadReason m_deadReason = enDeadReason_None;


    Vector3 m_position;
    Vector3 m_colPos;
    Vector3 m_colJumpPos;
    Vector3 m_toPlayer;
    Vector3 toPlayerDir;


    float m_disToPlayer;
    float m_attackCoolTimer = 1.0f;


    bool isAttack = false;
    bool isDead = false;
};
