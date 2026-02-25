#pragma once
class KillCounter : public IGameObject
{
public:

    KillCounter(){};
    ~KillCounter(){};
    bool Start();
    void Update();
    void Render(RenderContext& rc){};
    void TotalCount();

public:

    void EnemyCount();
    void EnemyType2Count();
    void BossCount();


public:
    int GetTotalCount() { return m_totalCount; }
    int GetEnemyCount() { return m_enemyCount; }
    int GetEnemyType2Count() { return m_enemyType2Count; }
    int GetBossCount() { return m_bossCount; }


private:
    int m_totalCount= 0;
    int m_enemyCount = 0;
    int m_enemyType2Count = 0;
    int m_bossCount = 0;
};
