#pragma once

class Player;

/// <summary>
/// ゲームカメラ
/// </summary>
class GameCamera : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameCamera() {};

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameCamera() {};

    /// <summary>
    /// スタート処理
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
    /// 注視点の計算
    /// </summary>
    /// <returns> 注視点の位置 </returns>
    Vector3 CalcTarget();

    /// <summary>
    /// 回転
    /// </summary>
    void Rotation(float inputX, float inputY);

    /// <summary>
    /// カメラの角度を抑制
    /// </summary>
    void SuppressCameraAngle();

private:
    Player* m_player = nullptr; // プレイヤー
    Vector3 m_toCameraPos;      // 注視点からカメラ位置までのベクトル
    Transform m_transform;      // トランスフォーム
};
