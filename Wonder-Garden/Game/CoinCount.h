#pragma once

/// <summary>
/// コインカウント
/// </summary>
class CountCointer : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CountCointer() = default;

    /// <summary>
    /// カウント
    /// </summary>
    void Count();

    /// <summary>
    /// コイン数取得
    /// </summary>
    int GetCount() { return m_count; }

private:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~CountCointer() = default;

    /// <summary>
    /// 開始
    /// </summary>
    bool Start();

private:
    int m_count = 0; // コイン数
};
