#pragma once

class Enemy;
class EnemyType2;

class EnemyManager
{
private:
    EnemyManager();
    ~EnemyManager();

private:
    std::array<Enemy*, 5> m_enemy;
    std::array<EnemyType2*, 5> m_enemyType2;


    
public:
    void Setup();
    void Update();

private:
    /** 自身のインスタンス */
    static EnemyManager* m_instance;


public:
    /** BattleManagerクラスのインスタンスを作成 */
    static void CreateInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new EnemyManager();
        }
    }
    /** BattleManagerクラスのインスタンスを削除 */
    static void DeleteInstance()
    {
        if (m_instance != nullptr)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }
    /** BattleManagerクラスのインスタンスを取得 */
    static EnemyManager* GetInstance() { return m_instance; }
};
