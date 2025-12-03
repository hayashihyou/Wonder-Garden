#pragma once

/// <summary>
/// スターの取得数
/// </summary>
class StarCounter : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    StarCounter() {};

    /// <summary>
    /// スターの取得数を増やす
    /// </summary>
    void AddStarCount();

    /// <summary>
    /// スターの取得数取得
    /// </summary>
    int GetStarCount() { return m_starCount; }

private:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~StarCounter() {};

private:
    int m_starCount = 0; // スターの取得数
};
