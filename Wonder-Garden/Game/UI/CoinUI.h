#pragma once

class CountCointer;

/// <summary>
/// コインUI
/// </summary>
class CoinUI : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CoinUI() = default;

private:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~CoinUI() = default;

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
    /// フォント初期化
    /// </summary>
    void InitFont();

    /// <summary>
    /// スプライト初期化
    /// </summary>
    void InitSprite();

    /// <summary>
    /// コインテキスト更新
    /// </summary>
    void UpdateCoinText();

private:
    CountCointer* m_countCointer = nullptr; // コインカウンター

    FontRender m_font;     // フォント
    SpriteRender m_sprite; // スプライト
};
