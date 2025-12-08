#pragma once

#include "Level3DRender/LevelRender.h"
#include "nature/SkyCube.h"

class Coin;
class CountCointer;
class CoinUI;
class Player;
class IEnemyState;
class Enemy;
class EnemyType2;
class EnemyManager;
class Boss;
class Stage;
class Star;
class StarCounter;
class Title;
class GameCamera;
class GameClear;
class GameOver;
class HPUI;
class Warp;
class Cannon;
class EffectManager;

class Game : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Game();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Game();

    /// <summary>
    /// スタート処理
    /// </summary>
    /// <returns></returns>
    bool Start();

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// 星の生成
    /// </summary>
    void CreateStar();

    /// <summary>
    /// 描画処理
    /// </summary>
    /// <param name="rc"></param>
    void Render(RenderContext& rc);

private:
    Coin* m_coin = nullptr;
    CountCointer* m_countCointer = nullptr;
    CoinUI* m_coinUI = nullptr;
    Player* m_player = nullptr;
    IEnemyState* m_iState = nullptr;
    Enemy* m_enemy = nullptr;
    EnemyType2* m_enemyType2 = nullptr;
    Boss* m_boss = nullptr;
    Stage* m_stage = nullptr;
    SkyCube* m_skyCube = nullptr;
    Star* m_star = nullptr;
    StarCounter* m_starCounter = nullptr;
    Title* m_title = nullptr;
    GameCamera* m_gameCamera = nullptr;
    HPUI* m_hpUI = nullptr;
    Warp* m_warp = nullptr;
    Cannon* m_cannon = nullptr;
    EffectManager* m_effectManager = nullptr;
    LevelRender m_levelRender;
};
