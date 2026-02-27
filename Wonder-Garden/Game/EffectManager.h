#pragma once

enum EnEffcetType
{
    Enemy_Hit,
    Boss_Hit,
    Boss_Attack,
    Cannon_Fire,
    Cannon_Star,
    Player_Attack,
    Player_Land,
    Game_Clear,
};

class EffectManager 
{
private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EffectManager();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EffectManager();


    std::map<int,EffectEmitter*> m_effect;
    Vector3 m_position;
    Quaternion m_rotation;
    int ID = 0;


public:
    bool Start();
    EffectEmitter* PlayEffect(Vector3 position, Quaternion rotation, Vector3 scale, int num);
    void StopEffect(int id);


    /**
    * シングルトン関連
    */
private:
    static EffectManager* m_instance;


public:
    static void Create()
    {
        if (m_instance == nullptr)
        {
            m_instance = new EffectManager;
        }
    }

    static EffectManager* Get() { return m_instance; }

    static void Delete()
    {
        if (m_instance)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }
};
