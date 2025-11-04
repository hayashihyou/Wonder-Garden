#pragma once
#include "CharacterBase.h"


class IPlayerState;
class Enemy;
class AttackCollision;
class Player : public CharacterBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player() {};

    /// <summary>
    /// プレイヤーの攻撃状態を保持
    /// </summary>
    /// <param name="attackFlag"></param>
    void SetAttack(bool attackFlag) { m_attackFlag = attackFlag; }

    /// <summary>
    /// 被弾状態を保持
    /// </summary>
    /// <param name="damage"></param>
    void SetDamage(bool damage) { m_damageFlag = damage; };

    /// <summary>
    /// 死んだ状態を保持
    /// </summary>
    /// <param name="dead"></param>
    void SetDead(bool dead) { m_deadFlag = dead; };

    void DamagePunch(int damageAmount);
    void Damage(int damageAmount);

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
		enPlayerState_Num,
	};

public:
    AttackCollision* punchCollision;                //攻撃の当たり判定
	ModelRender m_playerModel;                      //プレイヤーのモデル
	CharacterController m_characterController;      //キャラコン

public:
	Vector3 moveSpeed;          //移動速度
	Vector3 playerPos;          //位置
    Quaternion m_rot;           //向き
	int hp = 8;                 //体力
    int maxHp = 8;

    bool m_invincibleFlag = false;  //無敵(点滅表示)を作るフラグ
    bool m_gameoverFlag = false;    //ゲームオーバーフラグ

private:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player() {};
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
	///回転処理
	/// </summary>
	void Rotation();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);

	/// <summary>
	/// 攻撃判定の生成
	/// </summary>
	void MakeAttackCollision();

	/// <summary>
	/// ステータス管理
	/// </summary>
	void ManagerState();

	/// <summary>
	/// ステータスの変更
	/// </summary>
	void UpdateChangeState();

    /// <summary>
    /// 無敵中か確認
    /// </summary>
    void CheckInvincible();

	void HP()override;
	void Attack()override;
	void Move()override;

private:

	AnimationClip m_animationClips[enAnimationClip_Num];    //アニメーション
	CharacterBase* m_characterBase;                         //キャラクターベース
	IPlayerState* m_currentState = nullptr;                 //ステートマシン
	IPlayerState* m_stateList[enPlayerState_Num];           //ステートマシンのリスト
	Enemy* m_enemy;                                        
    CollisionObject m_playerHitCollision;                   //プレイヤー自身の当たり判定
	Quaternion m_colRot;                                    //当たり判定の向き
    Vector3 m_colPos;                                       //当たり判定の位置
    const Vector3 m_atkColPos = {0, 30, 50};                //攻撃した時の当たり判定の位置

private:
	int playerState = enPlayerState_Idle;                   //プレイヤー自身のステータス
	int m_atk = 2;                                          //攻撃力
    int m_drawTimer = 0;                                    //点滅表示する為のタイマー

    float m_invincibleTimer = 3.0f;                         //無敵時間

	bool m_attackFlag = false;	                            //攻撃中か確認するフラグ
	bool m_isStopMove = false;                              //攻撃時や死亡時、プレイヤーの移動を止めるフラグ
    bool m_deadFlag = false;                                //死亡してるかどうかの確認
    bool m_damageFlag = false;                              //ダメージを受けているかの確認
    bool m_drawFlag = false;                                //点滅表示する為のフラグ
};
