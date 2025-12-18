#include "stdafx.h"

#include "Title.h"
#include "Game.h"
#include "SoundManager.h"
#include "Player/Player.h"
#include "GameCamera.h"
#include "Gimmic/Warp.h"


namespace
{
    const float STAGE_ROT = 0.01f;
}

Title::~Title()
{
    DeleteGO(m_playerTitle);
    DeleteGO(m_titlePipe);
    DeleteGO(m_titleGameCamera);
}


bool Title::Start()
{
    InitModel();
    InitSprite();

    SoundManager::GetInstance().PlayBGM(SoundManager::SoundNumber::TitleBGM);

    return true;
}

void Title::Update()
{
    if (m_playerTitle == nullptr)
    {
        m_playerTitle = NewGO<PlayerTitle>(0, "TitlePlayer");
    }

    if (m_titlePipe == nullptr)
    {
        m_titlePipe = NewGO<TitlePipe>(0, "TitlePipe");
    }

    if (m_titleGameCamera == nullptr)
    {
        m_titleGameCamera = NewGO<TitleGameCamera>(0, "TitleGameCamera");
    }

    m_modelRot.AddRotationY(STAGE_ROT);

    // Bボタンが押されたらゲームシーンへ移行
    if (g_pad[0]->IsTrigger(enButtonB))
    {
        // 決定SE再生
        SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::SystemDecisionSE, 0.7f, false);

        NewGO<Game>(0, "Game");
        DeleteGO(this);
    }

    m_titleModel.SetRotation(m_modelRot);
    m_titleModel.Update();
}

void Title::Render(RenderContext& rc)
{
    m_titleModel.Draw(rc);
    m_titleSprite.Draw(rc);
}

void Title::InitSprite()
{
    m_titleSprite.Init("Assets/texture/Title.DDS", 1920.0f, 1080.0f);
    m_spritePos = {0.0f, 200.0f, 0.0f};
    m_titleSprite.SetPosition(m_spritePos);
    m_titleSprite.Update();
}

void Title::InitModel()
{
    m_titleModel.Init("Assets/stage/TitleStage.tkm");
    m_modelPos = {0.0f, 0.0f, 0.0f};
    m_modelRot = Quaternion::Identity;
    m_titleModel.SetPosition(m_modelPos);
    m_titleModel.SetRotation(m_modelRot);
    m_titleModel.Update();
}
