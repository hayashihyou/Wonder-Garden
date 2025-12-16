#pragma once

class GameCamera;

class BossBarsUI:public IGameObject
{
public:
    BossBarsUI(){};
    ~BossBarsUI(){};
    bool Start();
    void Update();
    void Render(RenderContext& rc);


private:
    SpriteRender m_bossBar;
    SpriteRender m_bossAlert;
    SpriteRender m_bossAlertFrame;
    GameCamera* m_gameCamera = nullptr;

    Vector3 m_position;

    float m_elapsedTime = 0.0f;
    bool m_isAdd = true;
};
