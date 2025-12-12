#pragma once

class Player;
class Boss;
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
    /// ボスを倒した後、星を生成する処理
    /// </summary>
    void CreateStar();

    /// <summary>
    /// 描画処理
    /// </summary>
    void Render(RenderContext& rc);


public:
    /// <summary>
    /// 星の座標を取得
    /// </summary>
    /// <param name="pos"></param>
    Vector3 GetPosition() { return m_position; }


    /// <summary>
    /// スターのゴール座標を取得
    /// </summary>
    /// <param name="pos"></param>
    Vector3 GetStarPosition() { return m_starPosition; }


private:
    Vector3 m_position;  // 座標
    Vector3 m_toPlayer;  // プレイヤーへのベクトル
    Vector3 m_starPosition;

    Quaternion m_rot;    // 回転
    ModelRender m_model; // モデル

    Player* m_player = nullptr;           // プレイヤー
    Boss* m_boss = nullptr;               // ボス
    StarCounter* m_starCounter = nullptr; // 星カウンター

    float m_distanceToPlayer; // プレイヤーまでの距離


    //追加
    Vector3 m_verocity; // 速度
    float m_t=0;
    Vector3 m_hopMoveStartPos;// ホップ移動開始位置
    bool m_isHopMove = false;// ホップ移動中かどうか
};
