#pragma once

class CoinCount;
class Player;
class Coin : public IGameObject
{
public:
    Coin(){};
    ~Coin(){};
    bool Start();
    void Update();
    void Render(RenderContext& rc);

public:
    void SetPosition(Vector3 position) { m_position = position; }

    void SetRotation(Quaternion rotation) { m_rotation = rotation; }

private:
    void CoinGet();
    void Rotation();

private:
    ModelRender m_modelRender;
    CoinCount* m_coinCount = nullptr;
    Player* m_player = nullptr;

private:
    Vector3 m_position;
    Quaternion m_rotation;
};
