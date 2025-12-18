#pragma once

#include "nature/SkyCube.h"

class PlayerTitle;
class TitleGameCamera;
class TitlePipe;

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
    ~Title() ;

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


    /// <summary>
    /// モデル初期化
    /// </summary>
    void InitModel();

private:
    SpriteRender m_titleSprite; // タイトル画面スプライト
    ModelRender m_titleModel;   // タイトル画面用モデル
    SkyCube* m_skyCube = nullptr;        // スカイキューブ
    PlayerTitle* m_playerTitle = nullptr; // タイトル画面用プレイヤー
    TitleGameCamera* m_titleGameCamera = nullptr; // タイトル画面用カメラ
    TitlePipe* m_titlePipe = nullptr;     // タイトル画面用土管

    Vector3 m_spritePos;
    Vector3 m_modelPos;
    Quaternion m_modelRot;
};
