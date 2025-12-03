#pragma once

/// <summary>
/// ステージ
/// </summary>
class Stage : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Stage() {};

private:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Stage() {};

    /// <summary>
    /// 開始処理
    /// </summary>
    bool Start();

    /// <summary>
    /// 初期化
    /// </summary>
    void Init();

    /// <summary>
    /// 描画
    /// </summary>
    void Render(RenderContext& rc);

    ModelRender m_stageModel;                  // ステージモデル
    PhysicsStaticObject m_physicsStaticObject; // 物理静的オブジェクト
};
