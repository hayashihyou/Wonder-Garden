#pragma once
#include "CharacterBase.h"

class Player;
class IBossState;
class AttackCollision;

class Boss : public CharacterBase
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
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Boss(){};


    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Boss();


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
    /// ボスの状態の遷移
    /// </summary>
    void UpdateChangeState();


    void HP() override;


    void Attack() override{};


    void Move() override{};


    /// <summary>
    /// プレイヤーのパンチ攻撃を受けたときの処理
    /// </summary>
    /// <param name="damageAmount"></param>
    void DamagePunch(int damageAmount);


    /// <summary>
    /// プレイヤーのジャンプ攻撃を受けたときの処理
    /// </summary>
    /// <param name="damageAmount"></param>
    void DamageReceiveHead(int damageAmount);


    /// <summary>
    /// ボスがダメージを受けたときの処理
    /// </summary>
    /// <param name="damageAmount"></param>
    /// <param name="reason"></param>
    void Damage(int damageAmount, int reason);


public:
    /// <summary>
    /// 位置を保持
    /// </summary>
    /// <param name="position"></param>
    void SetPosition(Vector3 position) { m_position = position; }


    /// <summary>
    /// 向きを保持
    /// </summary>
    /// <param name="rotation"></param>
    void SetRotation(Quaternion rotation) { m_rotation = rotation; }


    /// <summary>
    /// 攻撃判定の保持
    /// </summary>
    /// <param name="collision"></param>
    void SetCollision(AttackCollision* collision) { m_attackCollision = collision; }


    /// <summary>
    /// 攻撃後のクールタイムの保持
    /// </summary>
    /// <param name="time"></param>
    void SetAttackCoolTime(float time) { m_attackCoolTime = time; }


    /// <summary>
    /// 攻撃状態か確認するフラグの保持
    /// </summary>
    /// <param name="attack"></param>
    void SetAttack(bool attack) { m_isAttackFlag = attack; }


    /// <summary>
    /// 死亡状態か確認するフラグの保持
    /// </summary>
    /// <param name="dead"></param>
    void SetDead(bool dead) { m_isDeadFlag = dead; }


public:
    /// <summary>
    /// モデルの取得
    /// </summary>
    /// <returns></returns>
    ModelRender* GetModelRender() { return &m_bossModel; }


    /// <summary>
    /// ボスの死亡理由の取得
    /// </summary>
    /// <returns></returns>
    EnDeadReason GetDeadReason() { return m_deadReason; }


    /// <summary>
    /// プレイヤーに対しての当たり判定の取得
    /// </summary>
    /// <returns></returns>
    CollisionObject* GetCollision() { return m_bossCollision; }


    /// <summary>
    /// プレイヤーのジャンプによる攻撃に対する当たり判定の取得
    /// </summary>
    /// <returns></returns>
    CollisionObject* GetHeadCollision() { return m_bossHeadCollision; }


    /// <summary>
    /// 攻撃判定の取得
    /// </summary>
    /// <returns></returns>
    AttackCollision* GetAttackCollision() { return m_attackCollision; }


    Transform* GetTransform() { return &m_transform; }


    /// <summary>
    /// 位置の取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetPosition() { return m_position; }


    /// <summary>
    /// プレイヤーからボスまでのベクトルの取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetToPlayer() { return toPlayer; }


    /// <summary>
    /// プレイヤーからボスまでの距離の取得
    /// </summary>
    /// <returns></returns>
    float GetDisToPlayer() { return disToPlayer; }


    /// <summary>
    /// 攻撃後のクールタイムの取得
    /// </summary>
    /// <returns></returns>
    float GetAttackCoolTime() { return m_attackCoolTime; }


    /// <summary>
    /// ボスのHPの取得
    /// </summary>
    /// <returns></returns>
    int GetHP() { return hp; }


    /// <summary>
    /// ボスの最大HPの取得
    /// </summary>
    /// <returns></returns>
    int GetMaxHP() { return maxHp; }


    /// <summary>
    /// 死亡しているか確認するフラグの取得
    /// </summary>
    /// <returns></returns>
    bool IsDead() { return m_isDeadFlag; }


    /// <summary>
    /// 攻撃状態か確認するフラグの取得
    /// </summary>
    /// <returns></returns>
    bool IsAttack() { return m_isAttackFlag; }

    /// <summary>
    /// 攻撃判定の削除
    /// </summary>
    void DeleteAttackCollision();

    /// <summary>
    /// ダメージをうけたか取得
    /// </summary>
    bool GetDamaged() const { return m_damaged; }

    /// <summary>
    /// ダメージをうけたか設定
    /// </summary>
    void SetDamaged(bool damaged) { m_damaged = damaged; }


private:
    Player* m_player = nullptr;                             //プレイヤー
    ModelRender m_bossModel;                                //モデル
    EnDeadReason m_deadReason = enDeadReason_None;          //死亡理由
    AnimationClip m_animationClips[enAnimationClip_Num];    //アニメーションクリップ
    CollisionObject* m_bossCollision = nullptr;             //当たり判定
    CollisionObject* m_bossHeadCollision = nullptr;         //頭部当たり判定
    AttackCollision* m_attackCollision = nullptr;           //攻撃判定
    uint32_t m_currentStateId;                              //現在の状態ID
    std::map<uint32_t, IBossState*> m_stateMap;             //状態マップ


    Vector3 m_position;                                     //位置
    Vector3 m_colPosition;                                  //当たり判定位置
    Quaternion m_rotation;                                  //回転
    Vector3 m_scale;                                        //スケール
    Vector3 toPlayer;                                       //プレイヤーまでのベクトル


    float disToPlayer;                                      //プレイヤーまでの距離
    float m_attackCoolTime = 5.0f;                          //攻撃後のクールタイム
    int maxHp = 10;                                          //ボスの最大体力
    int hp = 10;                                             //ボスの体力
    bool m_isAttackFlag = false;                            //攻撃状態か確認するフラグ
    bool m_isDeadFlag = false;                              //死亡状態か確認するフラグ
    bool m_damaged;                                         // ダメージをうけた
};
