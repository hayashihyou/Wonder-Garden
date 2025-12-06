#pragma once
/**
 *TransformとIGameObjectを持った当たり判定のオブジェクト
 */

class Player;
class AttackCollision : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    AttackCollision(){};


    /// <summary>
    /// デストラクタ
    /// </summary>
    ~AttackCollision();


    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();


    /// <summary>
    /// 攻撃判定の生成
    /// </summary>
    /// <param name="size"></param>
    void CreateCollision(float size);


    /// <summary>
    ///　攻撃判定の座標と向きを初期化
    /// </summary>
    /// <param name="position"></param>
    /// <param name="forward"></param>
    /// <param name="parentTransform"></param>
    void InitTransform(Vector3 position, Vector3 forward, Transform& parentTransform);


    /// <summary>
    /// 当たり判定が消えるまでの時間
    /// </summary>
    void TimeLimit();


    CollisionObject* GetCollision() { return m_punchCollision; }


public:
    CollisionObject* m_punchCollision = nullptr;    // 攻撃判定


private:
    Transform m_transform;                          // トランスフォーム    


private:
    float deleteTimer = 1.0f;                       // 消えるまでの時間


};
