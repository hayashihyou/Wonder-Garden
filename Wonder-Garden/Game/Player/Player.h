#pragma once
#include "CharacterBase.h"

class Enemy;
class AttackCollision;
class PlayerStatePattern;

class Player : public CharacterBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Player(){};

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Player(){};

    /// <summary>
    /// スタート処理
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
    /// 被ダメージ計算
    /// </summary>
    /// <param name="damageAmount"></param>
    void Damage(int damageAmount);

     /// <summary>
    /// 攻撃判定の削除
    /// </summary>
    void DeleteAttackCollision();

public:
    /// <summary>
    /// プレイヤーの座標の保持
    /// </summary>
    /// <param name="position"></param>
    void SetPosition(const Vector3& position) { m_position = position; }

    /// <summary>
    /// プレイヤーの攻撃状態を保持
    /// </summary>
    /// <param name="attackFlag"></param>
    void SetAttack(bool attackFlag) { m_isAttack = attackFlag; }

    /// <summary>
    /// 被弾状態を保持
    /// </summary>
    /// <param name="damage"></param>
    void SetDamage(bool damage) { m_isDamage = damage; }

    /// <summary>
    /// 死んだ状態を保持
    /// </summary>
    /// <param name="dead"></param>
    void SetDead(bool dead) { m_isDead = dead; }

    /// <summary>
    /// ゲームオーバーのフラグを保持
    /// </summary>
    /// <param name="gameover"></param>
    void SetGameOverFlag(bool gameover) { m_isGameOver = gameover; }

    /// <summary>
    /// 大砲の発射状態の保持
    /// </summary>
    /// <param name="fireflag"></param>
    void SetFireFlag(bool fireflag) { m_isFire = fireflag; }

    /// <summary>
    /// プレイヤーが移動を停止しているか確認するフラグの保持
    /// </summary>
    /// <param name="stopmove"></param>
    void SetStopMove(bool stopmove) { m_isStopMove = stopmove; }

    void SetHP(int hp) { m_hp = hp; }

    void SetJumpPower(float jump) { m_jumpPower = jump; }

    void SetInvisTimer(float time) { m_invincibleTimer = time; }

    void SetCollision(AttackCollision* collision) { m_punchCollision = collision; }

    void SetMoveSpeed(float movespeed) { m_moveSpeed = movespeed; }

    /// <summary>
    /// 大砲の中に入った時のフラグ
    /// </summary>
    void SetCannonFlag(bool cannonReady) { m_isCannonReady = cannonReady; }

public:
    /// <summary>
    /// モデルを取得
    /// </summary>
    /// <returns></returns>
    ModelRender* GetModel() { return &m_playerModel; }

    /// <summary>
    /// 攻撃判定をコリジョンを取得
    /// </summary>
    /// <returns></returns>
    AttackCollision* GetCollision() { return m_punchCollision; }

    /// <summary>
    /// キャラコンの取得
    /// </summary>
    /// <returns></returns>
    CharacterController* GetCharCon() { return &m_characterController; }

    Transform* GetTransform() { return &m_transform; }

public:
    /// <summary>
    /// プレイヤーの移動方向を取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetMoveDir() { return m_moveDirection; }

    Vector3 GetForward() { return m_forward; }

    /// <summary>
    /// プレイヤーの位置を取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetPosition() { return m_position; }

    /// <summary>
    /// プレイヤーの重力の取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetGravity() { return m_gravity; }

    /// <summary>
    /// プレイヤーの向きを取得
    /// </summary>
    /// <returns></returns>
    Quaternion GetRotation() { return m_rotation; }

    void UpdateRotationY(const Vector3& direction) { m_rotation.SetRotationYFromDirectionXZ(direction); }

    float GetInvisTimer() { return m_invincibleTimer; }

    /// <summary>
    /// 移動速度の取得
    /// </summary>
    /// <returns></returns>
    float GetMoveSpeed() { return m_moveSpeed; }

     /// <summary>
    /// プレイヤーのジャンプ力を取得
    /// </summary>
    /// <returns></returns>
    float GetJumpPower() { return m_jumpPower; }

    /// <summary>
    /// 外部からの力を取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetForce() { return m_addForce; }

    /// <summary>
    /// 現在のHPを取得
    /// </summary>
    /// <returns></returns>
    int GetHP() { return m_hp; }

    /// <summary>
    /// 最大HPを取得
    /// </summary>
    /// <returns></returns>
    int GetMaxHP() { return maxHp; }

    /// <summary>
    /// ゲームオーバーのフラグの取得
    /// </summary>
    /// <returns></returns>
    bool IsGameOver() { return m_isGameOver; }

    /// <summary>
    /// ジャンプ中のフラグを取得
    /// </summary>
    /// <returns></returns>
    bool IsJump() { return m_isJump; }

    /// <summary>
    /// 攻撃中のフラグを取得
    /// </summary>
    /// <returns></returns>
    bool IsAttack() { return m_isAttack; }

    /// <summary>
    /// ダメージを受けたか確認
    /// </summary>
    /// <returns></returns>
    bool IsDamage() { return m_isDamage; }

    /// <summary>
    /// 死亡したか確認
    /// </summary>
    /// <returns></returns>
    bool IsDead() { return m_isDead; }

    /// <summary>
    /// 走っているか確認
    /// </summary>
    /// <returns></returns>
    bool IsRun() { return m_isRun; }


    /// <summary>
    /// 大砲が発射したかどうか
    /// </summary>
    bool IsFire() { return m_isFire; }


    /// <summary>
    /// 大砲の中にいる状態の取得
    /// </summary>
    /// <returns></returns>
    bool IsCannon() { return m_isCannonReady; }


public:
    /// <summary>
    /// 外部からの力を保持す
    /// </summary>
    /// <param name="addForce"></param>
    void SetAddForce(const Vector3& addForce) { m_addForce = addForce; }

public:
    /// <summary>
    /// アニメーションの種類
    /// </summary>
    enum EnAnimationClip
    {
        enAnimationClip_Idle,
        enAnimationClip_Walk,
        enAnimationClip_Run,
        enAnimationClip_Jump,
        enAnimationClip_Attack,
        enAnimationClip_Damage,
        enAnimationClip_Dead,
        enAnimationClip_Num,
    };

    /// <summary>
    /// プレイヤーの状態
    /// </summary>
    enum EnPlayerState
    {
        enPlayerState_Idle,
        enPlayerState_Walk,
        enPlayerState_Run,
        enPlayerState_Jump,
        enPlayerState_Attack,
        enPlayerState_Damage,
        enPlayerState_Dead,
        enPlayerState_Fire,
        enPlayerState_Num,
    };

private:
    /// <summary>
    /// 回転処理
    /// </summary>
    void Rotation();

    /// <summary>
    /// 無敵中か確認
    /// </summary>
    void CheckInvincible();

    void HP() override;
    void Attack() override;
    void Move() override;

private:
    CharacterController m_characterController;           // キャラコン
    AttackCollision* m_punchCollision;                   // 攻撃の当たり判定
    ModelRender m_playerModel;                           // プレイヤーのモデル
    AnimationClip m_animationClips[enAnimationClip_Num]; // アニメーション
    PlayerStatePattern* m_playerStatePattern;

private:
    float m_moveSpeed;                     // 移動速度
    float m_jumpPower;                     // ジャンプ力
    Vector3 m_moveDirection;                 // 移動方向
    Vector3 m_forward;                       // 前方向
    Vector3 m_position;                    // 位置
    Vector3 m_addForce;                    // 外部から加えられる力
    Vector3 m_gravity{0.0f, 150.0f, 0.0f}; // 重力
    Quaternion m_rotation;                 // 向き

    int m_atk = 2; // 攻撃力
    int m_hp = 8;    // 体力
    int maxHp = 8; // 最大体力

    float m_drawTimer = 0;          // 点滅表示する為のタイマー
    float m_invincibleTimer = 0.0f; // 無敵時間

    bool m_isAttack = false;     // 攻撃中か確認するフラグ
    bool m_isStopMove = false;   // 攻撃時や死亡時、プレイヤーの移動を止めるフラグ
    bool m_isDead = false;       // 死亡してるかどうかの確認
    bool m_isDamage = false;     // ダメージを受けているかの確認
    bool m_isDraw = false;       // 点滅表示する為のフラグ
    bool m_isInvincible = false; // 無敵(点滅表示)を作るフラグ
    bool m_isGameOver = false;   // ゲームオーバーフラグ
    bool m_isFire = false;
    bool m_isJump = false;
    bool m_isRun = false;
    bool m_isCannonReady = false;
};
