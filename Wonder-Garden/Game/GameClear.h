#pragma once

/// <summary>
/// ゲームクリア
/// </summary>
class GameClear : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameClear() {};

private:
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameClear() {};

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
    SpriteRender m_gameClearSprite; // ゲームクリア画像
};
