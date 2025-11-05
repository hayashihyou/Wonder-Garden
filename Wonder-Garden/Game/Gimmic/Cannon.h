#pragma once

class Player;
class Cannon : public IGameObject
{
public:
    Cannon() {}
    ~Cannon() {}
    bool Start();
    void Update();

private:
    void CheckNearCannon();

private:
    Player* m_player = nullptr;
    CollisionObject m_cannonCollision;

private:
    Vector3 position;
    Quaternion rotation;
};
