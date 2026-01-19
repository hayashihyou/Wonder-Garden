#include "stdafx.h"
#include "Warp.h"
#include "Player/Player.h"
#include "GameCamera.h"
#include "SoundManager.h"

namespace
{
    const Vector3 PIPE_POS = {300, 5, 1300};
    const Vector3 PIPE2_POS = {-2200, 5, 660};
    const Vector3 TITLE_PIPE_POS = {-200.0f, -10.0f, -50.0f};
    const Vector3 TITLE_PIPE_SCALE = {1.0f, 1.0f, 1.0f};

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

        // ワープ音再生
        SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::WarpPipeSE);
    }
}


bool TitlePipe::Start()
{
    m_modelRender.Init("Assets/stage/pipe_title.tkm");
    m_pipePos = TITLE_PIPE_POS;
    m_pipeScale = TITLE_PIPE_SCALE;
    m_modelRender.SetPosition(m_pipePos);
    m_modelRender.SetScale(m_pipeScale);
    m_modelRender.Update();
    m_pipeCollision.CreateSphere(m_pipePos,m_pipeRot, 15.0f);
    m_pipeCollision.Update();

    m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());


    return true;
}


void TitlePipe::Update()
{
    m_modelRender.Update();
    m_pipeCollision.Update();
}

void TitlePipe::Render(RenderContext& rc)
{
    m_modelRender.Draw(rc);
}
