#pragma once

/// <summary>
/// タイトル画面
/// </summary>
class Title : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Title() {};

private:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Title() {};

    /// <summary>
    /// 開始処理
    /// </summary>
    bool Start();

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// 描画処理
    /// </summary>
    void Render(RenderContext& rc);

    /// <summary>
    /// 画像初期化
    /// </summary>
    void InitSprite();

private:
    SpriteRender m_titleSprite; // タイトル画面スプライト
};
