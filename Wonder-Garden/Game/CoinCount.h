#pragma once

/// <summary>
/// コインカウント
/// </summary>
class CoinCounter : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CoinCounter() = default;

    /// <summary>
    /// カウント
    /// </summary>
    void Count();

    /// <summary>
    /// コイン数1の位取得
    /// </summary>
    int GetCountOnes() { return m_countOnes; }


    /// <summary>
    /// コイン数10の位取得
    /// </summary>
    /// <returns></returns>
    int GetCountTens() { return m_countTens; }
    

private:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~CoinCounter() = default;

    /// <summary>
    /// 開始
    /// </summary>
    bool Start();

private:
    int m_countOnes = 0; // コイン数1の位
    int m_countTens = 0; // コイン数10の位
};
