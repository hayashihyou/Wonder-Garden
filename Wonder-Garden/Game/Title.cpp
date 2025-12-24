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
    DeleteGO(m_player);
    DeleteGO(m_gameCamera); 
    DeleteGO(m_titlePipe);
}


bool Title::Start()
{
    m_player = NewGO<Player>(0, "Player");
    m_gameCamera = NewGO<GameCamera>(0, "GameCamera");
    m_titlePipe = NewGO<TitlePipe>(0, "TitlePipe");

    InitModel();
    InitSprite();

    SoundManager::GetInstance().PlayBGM(SoundManager::SoundNumber::TitleBGM);
    
    return true;
}

void Title::Update()
{
    // Bボタンが押されたらゲームシーンへ移行
    if (m_titlePipe->GetPipeCollision().IsHit(*m_player->GetCharCon()))
    {
        // 決定SE再生
        SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::SystemDecisionSE, 0.7f, false);

        NewGO<Game>(0, "Game");
        DeleteGO(this);
    }

    if (m_player->GetPosition().y <= -400.0f)
    {
        m_player->SetPosition({0.0f, 50.0f, 0.0f});
        m_player->GetModel()->SetPosition(m_player->GetPosition());
        m_player->GetModel()->Update();
        m_player->GetCharCon()->SetPosition(m_player->GetPosition());
    }
        
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
    m_modelScale = {2.0f, 2.0f, 2.0f};
    m_titleModel.SetPosition(m_modelPos);
    m_titleModel.SetRotation(m_modelRot);
    m_titleModel.SetScale(m_modelScale);
    m_titleModel.Update();
    m_physicsStaticObject.CreateFromModel(m_titleModel.GetModel(), m_titleModel.GetModel().GetWorldMatrix());
}
