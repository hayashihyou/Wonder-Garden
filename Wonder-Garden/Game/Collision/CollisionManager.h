#pragma once



class CollisionManager
{
private:
    CollisionManager();
    ~CollisionManager();

public:
    void CreateEffect(Vector3 position);
    void Update();

    /**
     * シングルトン関連
     */
private:
    static CollisionManager* m_isntace;
    EffectEmitter* m_effect = nullptr;

public:
    static void Create()
    {
        if (m_isntace == nullptr)
        {
            m_isntace = new CollisionManager();
        }
    }
    static CollisionManager* Get()
    {
        return m_isntace;
    } 
    static void Delete()
    {
        if (m_isntace)
        {
            delete m_isntace;
            m_isntace = nullptr;
        }
    }
};
