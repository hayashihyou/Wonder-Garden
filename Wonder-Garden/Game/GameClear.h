#pragma once

class UICanvas;
class UIIcon;

/// <summary>
/// ゲームクリア
/// </summary>
class GameClear : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameClear();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameClear();

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
    std::unique_ptr<UICanvas> m_uiCanvas = nullptr;

    UIIcon* m_gameClear;
    UIIcon* m_clearText;
    UIIcon* m_pushText;
    UIIcon* m_coinTexture;
    UIIcon* m_coinCountMark;


private:
    Vector3 m_textureScale = {2.5f, 2.5f, 1.0f};

    float m_elapsedTime = 0.0f;
    bool m_isEasing = true;
    bool m_isScaled = false;
};
