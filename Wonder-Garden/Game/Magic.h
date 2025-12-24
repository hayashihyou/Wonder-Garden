#pragma once

class EnemyType2;
class Magic : public IGameObject
{
public:
    Magic(){};
    ~Magic(){};

    void CreateCollision(float size);


    void Update();


    void TimeLimit();


public:
    CollisionObject* m_magicCollision = nullptr;


private:
    Vector3 m_moveDirection;
    Vector3 m_moveSpeed = {0.0f, 0.0f, 1.0f};
    Transform m_transform;
    EnemyType2* m_enemyType2 = nullptr;

    float m_lifeTime = 5.0f;                        //魔法の存在時間
};
