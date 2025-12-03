#pragma once

class Player;
class StarCounter;

/// <summary>
/// 星オブジェクト
/// </summary>
class Star : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Star() {};

private:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Star() {};

    /// <summary>
    /// 開始処理
    /// </summary>
    bool Start();

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// 初期化
    /// </summary>
    void Init();

    /// <summary>
    /// 回転
    /// </summary>
    void Rotation();

    /// <summary>
    /// 描画処理
    /// </summary>
    void Render(RenderContext& rc);

private:
    Vector3 m_pos;       // 座標
    Quaternion m_rot;    // 回転
    ModelRender m_model; // モデル
    Vector3 m_toPlayer;  // プレイヤーへのベクトル

    Player* m_player = nullptr;           // プレイヤー
    StarCounter* m_starCounter = nullptr; // 星カウンター

    float m_distanceToPlayer; // プレイヤーまでの距離
};
