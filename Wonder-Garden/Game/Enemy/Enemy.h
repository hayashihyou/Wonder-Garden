#pragma once
#include "CharacterBase.h"

class Player;
class IEnemyState;
class AttackCollision;
class Enemy : public CharacterBase
{
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
        enAnimationClip_Move,
        enAnimationClip_Attack,
        enAnimationClip_JumpDead,
        enAnimationClip_AttackDead,
        enAnimationClip_Num,
    };


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

    void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

    /// <summary>
    /// プレイヤーのパンチ攻撃を受けたときのダメージ処理
    /// </summary>
    /// <param name="damageAmount"></param>
    void DamagePunch(int damageAmount);


    /// <summary>
    /// プレイヤーのジャンプ攻撃を受けたときのダメージ処理
    /// </summary>
    /// <param name="damageAmount"></param>
    void DamageReceiveHead(int damageAmount);


    /// <summary>
    /// 被ダメージ処理
    /// </summary>
    /// <param name="damageAmount"></param>
    /// <param name="reason"></param>
    void Damge(int damageAmount, int reason);


    /// <summary>
    /// 攻撃判定の削除
    /// </summary>
    void DeleteAttackCollision();


public:
    /// <summary>
    /// 位置を保持
    /// </summary>
    /// <param name="pos"></param>
    void SetPosition(Vector3 pos) { m_position = pos; };


    /// <summary>
    /// 向きの保持
    /// </summary>
    /// <param name="rot"></param>
    void SetRotation(Quaternion rot) { m_rotation = rot; };

   
    /// <summary>
    /// 攻撃状態の保持
    /// </summary>
    /// <param name="attack"></param>
    void SetAttack(bool attack) { m_isAttackFlag = attack; }


    /// <summary>
    /// 攻撃判定の保持
    /// </summary>
    /// <param name="collision"></param>
    void SetCollision(AttackCollision* collision) { m_attackCollision = collision; }


    /// <summary>
    /// 死んでる状態の保持
    /// </summary>
    /// <param name="dead"></param>
    void SetDeadFlag(bool dead) { m_isDeadFlag = dead; }


    /// <summary>
    /// 当たり判定の削除
    /// </summary>
    void DeleteCollision()
    {
        DeleteGO(enemyCollisionObject);
        enemyCollisionObject = nullptr;
    }


public:
    /// <summary>
    /// 位置を取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetPosition() { return m_position; }


    /// <summary>
    /// 敵とプレイヤーとのベクトルを取得
    /// </summary>
    Vector3 GetToPlayer() { return m_toPlayer; }


    /// <summary>
    /// 敵の正面の向きを取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetForward() { return m_forward; }


    /// <summary>
    /// 向きの取得
    /// </summary>
    /// <returns></returns>
    Quaternion GetRotation() { return m_rotation; }


    /// <summary>
    /// 敵とプレイヤーとの距離を取得
    /// </summary>
    /// <returns></returns>
    float GetDisToPlayer() { return m_disToPlayer; }


    /// <summary>
    /// 攻撃判定の取得
    /// </summary>
    /// <returns></returns>
    AttackCollision* GetAttackCollision() { return m_attackCollision; }


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


    /// <summary>
    /// トランスフォームの取得
    /// </summary>
    /// <returns></returns>
    Transform* GetTransform() { return &m_transform; }


    /// <summary>
    /// 死亡理由の取得
    /// </summary>
    /// <returns></returns>
    EnDeadReason GetDeadReason() { return m_deadReason; }


    /// <summary>
    /// 攻撃しているか確認するためのフラグの取得
    /// </summary>
    /// <returns></returns>
    bool IsAttack() { return m_isAttackFlag; }


    /// <summary>
    /// 死亡しているか確認するためのフラグの取得
    /// </summary>
    /// <returns></returns>
    bool IsDead() { return m_isDeadFlag; }


public:
    PhysicsStaticObject m_enemyCollision;
    ModelRender m_enemyModel;


private:
    /// <summary>
    /// 攻撃後のクールタイムの更新
    /// </summary>
    void AttackCoolTimeUpdate();


    /// <summary>
    /// 敵の状態の更新
    /// </summary>
    void UpdateChangeState();


    void HP() override;
    void Attack() override{}; 
    void Move() override{};


public:
    


private:
    AnimationClip m_animationClips[enAnimationClip_Num];
    AttackCollision* m_attackCollision = nullptr;
    CollisionObject* enemyCollisionObject = nullptr;
    CollisionObject* enemyJumpCollision = nullptr;
    Quaternion m_rotation;
    Player* m_player;
    EnDeadReason m_deadReason = enDeadReason_None;


    uint32_t m_enemyState;
    std::map<uint32_t, IEnemyState*> m_stateList;


    Vector3 m_position;
    Vector3 m_colPos;
    Vector3 m_colJumpPos;
    Vector3 m_toPlayer;
    Vector3 toPlayerDir;
    Vector3 m_forward;


    float m_disToPlayer;
    float m_attackCoolTimer = 1.0f;


    bool m_isAttackFlag = false;
    bool m_isDeadFlag = false;
};
