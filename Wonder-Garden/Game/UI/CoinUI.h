#pragma once

class CoinCounter;

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
    /// スプライト初期化
    /// </summary>
    void InitSprite();


    /// <summary>
    /// コインのテキストの初期化
    /// </summary>
    void InitText();


    /// <summary>
    /// コインテキスト更新
    /// </summary>
    void UpdateCoinText();

private:
    CoinCounter* m_coinCounter = nullptr; // コインカウンター
    SpriteRender m_sprite;          // スプライト
    SpriteRender m_coinTextOnes;    //1の位のコインの取得枚数のテキスト
    SpriteRender m_coinTextTens;    //10の位のコインの取得枚数のテキスト
    SpriteRender m_coinTextMark;    //取得枚数の記号

    int m_lastOnes = -1;
    int m_lastTens = -1;

};
