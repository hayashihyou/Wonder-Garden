#pragma once

class Player;
class GameClear;
class GameOver;
class GameCamera;

class Fade : public IGameObject 
{
public:

    enum EnState
    {
        None,
        FadeIn,
        FadeOut,
        Finished,
    };

    /// <summary>
    /// コンストラクタ
    /// </summary>
    Fade(){};


    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Fade();


    /// <summary>
    /// スタート
    /// </summary>
    /// <returns></returns>
    bool Start();


    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();


    /// <summary>
    /// 描画処理
    /// </summary>
    /// <param name="rc"></param>
    void Render(RenderContext& rc);


public:
    /// <summary>
    /// フェードインしたかの状態の保持
    /// </summary>
    /// <param name="fade"></param>
    void SetFade(bool fade) { m_isFade = fade; }


public:
    /// <summary>
    /// フェードインしたかの状態の取得
    /// </summary>
    /// <returns></returns>
    bool IsFade() { return m_isFade; }


private:
    EnState m_state = EnState::None;

    SpriteRender m_fadeSprite;           //スプライトレンダー
    SpriteRender m_fadeBack;                   //フェードを完全にしたときの黒い背景
    Player* m_player = nullptr;          //プレイヤー
    GameClear* m_gameClear = nullptr;    //ゲームクリア
    GameOver* m_gameOver = nullptr;      //ゲームオーバー
    GameCamera* m_gameCamera = nullptr;  //ゲームカメラ

    Vector3 m_position = Vector3::Zero;
    Vector3 testPos = Vector3::Zero;
    Vector3 m_scale = {30.0f, 30.0f, 1.0f};
    Vector3 testScl = {10.0f, 10.0f, 1.0f};

    bool m_isFade = false;                //フェードインしたか確認
    bool m_isGameClear = false;           //ゲームクリアしたか
    bool m_isGameOver = false;            //ゲームオーバーしたか

    float m_fadeTime = 1.0f;              //画面遷移のクールタイム
};
