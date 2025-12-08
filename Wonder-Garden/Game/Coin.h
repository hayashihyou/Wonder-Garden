#pragma once

class CountCointer;
class Player;

/// <summary>
/// コイン
/// </summary>
class Coin : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Coin() = default;

    /// <summary>
    /// 位置設定
    /// </summary>
    /// <param name="position"> 位置 </param>
    void SetPosition(Vector3 position) { m_position = position; }

    /// <summary>
    /// 回転設定
    /// </summary>
    /// <param name="rotation"> 回転 </param>
    void SetRotation(Quaternion rotation) { m_rotation = rotation; }

private:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Coin() = default;

    /// <summary>
    /// 開始
    /// </summary>
    bool Start();

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Render(RenderContext& rc);

    /// <summary>
    /// モデル更新
    /// </summary>
    void UpdateModel();

    /// <summary>
    /// アイドルステートの更新
    /// </summary>
    void UpdateIdleState();

    /// <summary>
    /// 取得アニメーション中ステートの更新
    /// </summary>
    void UpdatePlayingGetAnimationState();

    /// <summary>
    /// コイン取得ステートの更新
    /// </summary>
    void UpdateGetCoinState();

    /// <summary>
    /// 回転処理
    /// </summary>
    void Rotation();

    /// <summary>
    /// 体力アップ
    /// </summary>
    void HealHp();

private:
    /// <summary>
    /// 状態
    /// </summary>
    enum State
    {
        IDLE,                  // 待機
        PLAYING_GET_ANIMATION, // 取得アニメーション中
        GET_COIN,              // コイン取得
    };
    State m_currentState = IDLE; // 現在の状態

    CountCointer* m_countCointer = nullptr; // コインをカウント
    Player* m_player = nullptr;             // プレイヤー

    ModelRender m_model;              // モデル
    Vector3 m_position;               // 位置
    Quaternion m_rotation;            // 回転
    float m_rotationSpeed;            // 回転速度
    float m_getAnimationTimer = 0.0f; // 取得アニメーションタイマー
};
