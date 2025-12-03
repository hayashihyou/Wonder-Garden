#pragma once

/// <summary>
/// ゲームオーバー
/// </summary>
class GameOver : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameOver() {};

private:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameOver() {};

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
    /// 初期化
    /// </summary>
    void Init();

private:
    SpriteRender m_gameOverSprite; // ゲームオーバー画像
};
