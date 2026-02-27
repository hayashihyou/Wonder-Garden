#pragma once

/// <summary>
/// サウンドマネージャー
/// </summary>
class SoundManager : public IGameObject
{
public:
    /// <summary>
    /// サウンド番号
    /// </summary>
    enum SoundNumber
    {
        TitleBGM,
        InGameBGM,
        PlayerRunningSE,
        PlayerJumpSE,
        PlayerPunchSE,
        PlayerDamageSE,
        GetCoinSE,
        GetStarSE,
        CannonFireSE,
        CannonStarSE,
        WarpPipeSE,
        SystemDecisionSE,
        EnemyAttackSE,
        EnemyDeathSE,
    };

public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SoundManager();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SoundManager();

    /// <summary>
    /// BGM再生
    /// </summary>
    void PlayBGM(SoundNumber soundNumber, float volume = 0.5f, bool isLoop = true);

    /// <summary>
    /// SE再生
    /// </summary>
    void PlaySE(SoundNumber soundNumber, float volume = 0.7f, bool isLoop = false);


    /// <summary>
    /// 再生中のBGMを停止
    /// </summary>
    void DeleteCurrentBGM();


    /// <summary>
    /// 再生中のSEを停止
    /// </summary>
    void DeleteCurrentSE();


private:
    void Init();


private:
    /// <summary>
    /// 現在再生中のBGM
    /// </summary>
    SoundSource* m_currentBGM = nullptr;


/// <summary>
/// シングルトン関連
/// </summary>
private:
    /// <summary>
    /// シングルトン用インスタンス
    /// </summary>
    static SoundManager* s_instance;


public:
    // シングルトン取得
    static SoundManager& GetInstance() { return *s_instance; }
};
