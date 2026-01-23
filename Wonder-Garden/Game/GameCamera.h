#pragma once

class Player;
class Boss;
class Star;
class BossBarsUI;

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
    void SuppressCameraAngle(Vector3 oldPos);


    /// <summary>
    /// ボス戦前のムービー部分の際のカメラ処理
    /// </summary>
    void BossCamera();


    /// <summary>
    /// スター生成時のカメラ処理
    /// </summary>
    void StarCamera();


    /// <summary>
    /// 土管移動時のカメラ処理
    /// </summary>
    void WarpCamera();


public:
    void SetBossCamera(bool bossFlag) { m_isBossCamera = bossFlag; }
    void SetStarCamera(bool starFlag) { m_isStarCamera = starFlag; }
    void SetWarpCamera(bool warpFlag) { m_isWarpCamera = warpFlag; }

    bool GetBossCamera() const { return m_isBossCamera; }
    bool GetStarCamera() const { return m_isStarCamera; }
    bool GetWarpCamera() const { return m_isWarpCamera; }

    void DokanStart();


private:
    Player* m_player = nullptr; // プレイヤー
    Boss* m_boss = nullptr;     // ボス
    Star* m_star = nullptr;     // スター
    BossBarsUI* m_bossBarsUI = nullptr; // ボスの体力ゲージUI
    Vector3 m_toCameraPos;      // 注視点からカメラ位置までのベクトル
    Transform m_transform;      // トランスフォーム

    Vector3 m_bossTargetPos;     // ボスの注視点位置
    Vector3 m_bossCameraPos;     // ボスのカメラ位置
    Vector3 m_starTargetPos;     // スターの注視点位置
    Vector3 m_starCameraPos;     // スターのカメラ位置
    Vector3 m_warpTargetPos;     // 土管移動時の注視点位置
    Vector3 m_warpCameraPos;     // 土管移動時のカメラ位置
    Vector3 m_cameraPosition;    // カメラ位置
    Vector3 m_targetPosition;    // 注視点位置

    float time = 0.0f;
    Vector3 cameraOffset = Vector3::Zero;

    bool m_isBossCamera = false;    // ボス戦前のムービー部分のカメラフラグ
    bool m_changeCamera = false;   // カメラ切り替えフラグ
    bool m_isStarCamera = false;   // スター取得時のカメラフラグ
    bool m_isWarpCamera = false;   // 土管移動時のカメラフラグ
};
