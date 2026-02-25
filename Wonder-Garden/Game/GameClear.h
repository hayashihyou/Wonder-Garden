#pragma once

class CoinCounter;
class KillCounter;
class Score;
class UICanvas;
class UIIcon;
class UIDigit;

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


    /// <summary>
    /// コインを何枚集めたか確認する
    /// </summary>
    void ResultCoin();


    /// <summary>
    /// 敵を何体倒したか
    /// </summary>
    void ResultEnemy();


    /// <summary>
    /// 集めたコインと倒した敵でスコアを計算
    /// </summary>
    void ResultScore();


private:
    std::unique_ptr<UICanvas> m_uiCanvas = nullptr;
    CoinCounter* m_coinCount = nullptr;
    KillCounter* m_killCount = nullptr;
    Score* m_score = nullptr;
    SpriteRender m_gameClear;

    UIIcon* m_clearText;             //クリア画面テキスト
    UIIcon* m_pushText;              //Aボタンを押してねのテキスト
    UIIcon* m_coinTexture;           //コインのアイコン
    UIIcon* m_coinCountMark;         //枚数数える×のマーク
    UIIcon* m_enemyCountMark;        //スライムを倒した数の×のマーク
    UIIcon* m_enemyType2CountMark;   //岩型のモンスターを倒した数の×のマーク
    UIIcon* m_bossCountMark;         //ボスの倒した数の×のマーク
    UIIcon* m_enemyTexture;          //スライムのアイコン
    UIIcon* m_enemyType2Texture;     //岩型のモンスターのアイコン
    UIIcon* m_bossTexture;           //ボスのアイコン
    UIIcon* m_scoreText;             //スコアのテキスト
    UIDigit* m_coinUIDigit;          //取得コイン数
    UIDigit* m_enemyUIDigit;         //倒したエネミーの数
    UIDigit* m_enemyType2UIDigit;    //倒したエネミー2の数
    UIDigit* m_bossUIDigit;          //倒したボスの数
    UIDigit* m_scoreUIDigit;         //スコア表示


private:
    Vector3 m_textureScale = {2.5f, 2.5f, 1.0f};

    int m_coinTotal = 0;
    int m_enemyTotal = 0;
    int m_enemyType2Total = 0;
    int m_bossTotal = 0;
    int m_scoreTotal = 0;
    float m_fadeTime = 1.0f;
    float m_coinTime = 1.0f;
    float m_enemyTime = 1.0f;
    float m_enemyType2Time = 1.0f;
    float m_bossTime = 1.0f;
    float m_scoreTime = 1.0f;
    float m_elapsedTime = 0.0f;
    bool m_isEasing = true;
    bool m_isScaled = false;
};
