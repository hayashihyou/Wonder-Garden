#pragma once

enum EnEffcetType
{
    Enemy_Hit,
    Boss_Hit,
    Cannon_Fire,
    Player_Attack,
    Boss_Attack,
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
    int PlayEffect(Vector3 position, Quaternion rotation, Vector3 scale, int num);
    void StopEffect(int id);

    void SetPosition(int ID, Vector3 position) { m_effect[ID]->SetPosition(position);}
    void SetRotation(int ID, Quaternion rotation) { m_effect[ID]->SetRotation(rotation); }


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
