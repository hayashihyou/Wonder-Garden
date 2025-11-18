#include "stdafx.h"
#include "Warp.h"
#include "Player/Player.h"
#include "GameCamera.h"

namespace
{
    const Vector3 PIPE_POS = {300, 5, 1300};
    const Vector3 PIPE2_POS = {-2200, 5, 660};
}

bool Warp::Start()
{
    m_player = FindGO<Player>("Player");
    m_gameCamera = FindGO<GameCamera>("GameCamera");


    m_pipePos = PIPE_POS;
    m_pipe2Pos = PIPE2_POS;

    m_pipeCollision.Update();
    m_pipe2Collision.Update();

    m_pipeCollision.CreateCapsule(m_pipePos, m_pipeRot, 30.0f, 5.0f);
    m_pipe2Collision.CreateCapsule(m_pipe2Pos, m_pipeRot, 30.0f, 5.0f);
    return true;
}

void Warp::Update()
{
    CheckWarp();
}

void Warp::CheckWarp()
{
    if (m_pipeCollision.IsHit(*m_player->GetCharCon()))
    {
        m_player->GetModel()->SetPosition(m_pipe2Pos);
        m_player->GetCharCon()->SetPosition(m_pipe2Pos);
        m_player->GetCharCon()->GetPosition();
        m_player->GetModel()->Update();
        m_gameCamera->Update();
    }
}

