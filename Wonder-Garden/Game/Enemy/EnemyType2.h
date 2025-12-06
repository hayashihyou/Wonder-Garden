#pragma once
#include "CharacterBase.h"

class Player;
class AttackCollision;
class IEnemyType2State;

class EnemyType2 : public CharacterBase
{
public:
    /// <summary>
    /// 死亡理由
    /// </summary>
    enum EnDeadReason
    {
        enDeadReason_None,
        enDeadReason_Jump,
        enDeadReason_Punch,
    };


    /// <summary>
    /// アニメーションクリップ
    /// </summary>
    enum EnEnemyType2AnimationClip
    {
        enAnimationClip_Idle,
        enAnimationClip_Attack,
        enAnimationClip_AttackDead,
        enAnimationClip_JumpDead,
        enAnimationClip_Num
    };


public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyType2(){};


    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EnemyType2();


    /// <summary>
    /// スタート
    /// </summary>
    /// <returns></returns>
    bool Start() override;


    /// <summary>
    /// 更新処理
    /// </summary>
    void Update() override;


    /// <summary>
    /// 描画処理
    /// </summary>
    /// <param name="rc"></param>
    void Render(RenderContext& rc) override;


    void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);


    void HP() override;


    void Attack() override{};


    void Move() override{};

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
    void Damage(int damageAmount, int reason);


    /// <summary>
    /// 攻撃判定の削除
    /// </summary>
    void DeleteAttackCollision();



public:
    /// <summary>
    /// 位置を保持
    /// </summary>
    /// <param name="position"></param>
    void SetPosition(Vector3 position) { m_position = position; }


    /// <summary>
    /// 回転を保持
    /// </summary>
    /// <param name="rotation"></param>
    void SetRotation(Quaternion rotation) { m_rotation = rotation; }


    /// <summary>
    /// 攻撃状態か確認するフラグの保持
    /// </summary>
    /// <param name="attack"></param>
    void SetAttack(bool attack) { m_isAttackFlag = attack; }


    /// <summary>
    /// 死亡しているか確認するフラグの保持
    /// </summary>
    /// <param name="dead"></param>
    void SetDead(bool dead) { m_isDeadFlag = dead; }


    /// <summary>
    /// 攻撃判定クラスの保持
    /// </summary>
    /// <param name="collision"></param>
    void SetAttackCollision(AttackCollision* collision) { m_attackCollision = collision; }


public:
    /// <summary>
    /// 位置の取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetPosition() { return m_position; };


    /// <summary>
    /// 敵とプレイヤーまでのベクトルの取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetToPlayer() { return toPlayer; };


    /// <summary>
    /// 敵とプレイヤーまでの距離の取得
    /// </summary>
    /// <returns></returns>
    float GetDisToPlayer() { return disToPlayer; };


    /// <summary>
    /// 当たり判定の取得
    /// </summary>
    /// <returns></returns>
    CollisionObject* GetCollision() { return enemyType2Collision; }


    /// <summary>
    /// プレイヤーのジャンプ攻撃に対する当たり判定の取得
    /// </summary>
    /// <returns></returns>
    CollisionObject* GetHeadCollision() { return enemyType2Collision; }


    /// <summary>
    /// モデルの取得
    /// </summary>
    /// <returns></returns>
    ModelRender* GetModelRender() { return &m_enemyType2Model; }


    /// <summary>
    /// 死亡理由の取得
    /// </summary>
    /// <returns></returns>
    EnDeadReason GetDeadReason() { return m_deadReason; }


    /// <summary>
    /// 攻撃判定の取得
    /// </summary>
    /// <returns></returns>
    AttackCollision* GetAttackCollision() { return m_attackCollision; }


    /// <summary>
    /// トランスフォームの取得
    /// </summary>
    /// <returns></returns>
    Transform* GetTransform() { return &m_transform; }


    /// <summary>
    /// 攻撃後のクールタイムの取得
    /// </summary>
    /// <returns></returns>
    float GetAttackCoolTime() { return m_attackCoolTime; }


    /// <summary>
    /// 攻撃中か確認するフラグの取得
    /// </summary>
    /// <returns></returns>
    bool IsAttack() { return m_isAttackFlag; }


    /// <summary>
    /// 死亡しているか確認するフラグの取得
    /// </summary>
    /// <returns></returns>
    bool IsDead() { return m_isDeadFlag; }


private:
    /// <summary>
    /// 攻撃後のクールタイムの更新
    /// </summary>
    void AttackCoolTimeUpdate();


    /// <summary>
    /// 状態遷移の更新
    /// </summary>
    void UpdateChangeState();


private:
    ModelRender m_enemyType2Model;                          //モデル
    AnimationClip m_animationClips[enAnimationClip_Num];    //アニメーションクリップ
    EnDeadReason m_deadReason = enDeadReason_None;          //死亡理由
    AttackCollision* m_enemyType2Attack = nullptr;          //攻撃判定 
    CollisionObject* enemyType2Collision = nullptr;         //当たり判定
    CollisionObject* enemyType2JumpCollision = nullptr;     //ジャンプ攻撃用当たり判定
    Player* m_player;                                       //プレイヤー
    AttackCollision* m_attackCollision;                     //攻撃判定


    uint32_t m_enemyType2State;                             //現在の状態ID
    std::map<uint32_t, IEnemyType2State*> m_stateList;      //状態マップ


    Vector3 m_position;                                     //位置
    Vector3 m_colPos;                                       //当たり判定位置
    Vector3 m_colJumpPos;                                   //ジャンプ攻撃用当たり判定位置
    Vector3 toPlayer;                                       //プレイヤーまでのベクトル
    Quaternion m_rotation;                                  //回転


    float disToPlayer;                                      //プレイヤーまでの距離
    float m_attackCoolTime;                                 //攻撃後のクールタイム
    bool m_isDeadFlag = false;                              //死亡しているか確認するフラグ
    bool m_isAttackFlag = false;                            //攻撃状態か確認するフラグ
};
