#pragma once

class Player;
class GameCamera;
class Cannon : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Cannon() {}

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Cannon() {}

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
    /// <returns></returns>
    void Render(RenderContext& rc);


    void SetPosition(Vector3 pos) { position = pos; }

    void SetRotation(Quaternion rot) { rotation = rot; }

private:
    /// <summary>
    /// 大砲にプレイヤーが近づいたか
    /// </summary>
    void CheckNearCannon();

    /// <summary>
    /// 大砲の発射
    /// </summary>
    void Fire();

private:
    Player* m_player = nullptr;
    GameCamera* m_gameCamera = nullptr;
    CollisionObject m_cannonCollision;
    ModelRender m_cannonModel;

private:
    Vector3 position;
    Vector3 modelPos;
    Vector3 scale;
    Quaternion modelRot;
    Quaternion rotation;

    bool changeFlag = false;        // 位置の変更をしたか確認するフラグ　されたらtrue。
    bool m_isCannonReady = false;   //
};
