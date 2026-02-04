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
    static CollisionManager* m_instance;

public:
    static void Create()
    {
        if (m_instance == nullptr)
        {
            m_instance = new CollisionManager();
        }
    }
    static CollisionManager* Get()
    {
        return m_instance;
    } 
    static void Delete()
    {
        if (m_instance)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }
};
