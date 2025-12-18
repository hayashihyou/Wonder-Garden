#pragma once

class Player;
class GameCamera;
class Warp : public IGameObject
{
public:
    Warp(){}
    ~Warp() {}

    bool Start();
    void Update();

private:
    /// <summary>
    /// 土管に入ってワープしてるか
    /// </summary>
    void CheckWarp();


private:
    Player* m_player = nullptr;
    GameCamera* m_gameCamera = nullptr;
    CollisionObject m_pipeCollision;
    CollisionObject m_pipe2Collision;

private:
    Vector3 m_pipePos;
    Vector3 m_pipe2Pos;
    Quaternion m_pipeRot;
};


class TitlePipe : public Warp
{
public:
    TitlePipe() {};
    ~TitlePipe() {};

    bool Start();
    void Update();
    void Render(RenderContext& rc);


private:
    ModelRender m_modelRender;

    Vector3 m_pipePos;
    Vector3 m_pipeScale;
};
