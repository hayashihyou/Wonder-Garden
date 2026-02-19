#include "stdafx.h"

#include "Fade.h"
#include "GameCamera.h"
#include "GameClear.h"
#include "GameOver.h"
#include "Player/Player.h"

Fade::~Fade()
{
    DeleteGO(m_player);
    DeleteGO(m_gameCamera);
}

bool Fade::Start()
{
    m_player = FindGO<Player>("Player");
    m_gameCamera = FindGO<GameCamera>("GameCamera");

    m_fadeSprite.Init("Assets/texture/FadeIn/FadeIn.DDS", 9000.0f, 9000.0f);
    test.Init("Assets/texture/FadeIn/Fade.DDS", 1280.0f, 1080.0f);

    m_state = EnState::FadeIn;
    m_scale = {30.0f, 30.0f, 1.0f};

    m_fadeSprite.SetPosition(m_position);
    m_fadeSprite.SetScale(m_scale);
    m_fadeSprite.Update();
    test.SetPosition(testPos);
    test.SetScale(testScl);
    test.Update();

    return true;
}

void Fade::Update()
{
    switch (m_state)
    {
    case EnState::FadeIn:
        m_scale.x -= 0.3f;
        m_scale.y -= 0.3f;

        if (m_scale.x <= 0.3f)
        {
            m_scale = {0.3f, 0.3f, 1.0f};
            m_fadeTime -= g_gameTime->GetFrameDeltaTime();
            m_isFade = true;
        }

        if (m_fadeTime <= 0.0f)
        {
            m_fadeTime = 1.0f;
            m_state = None;
        }

        break;

    case EnState::FadeOut:
        m_scale.x += 0.3f;
        m_scale.y += 0.3f;

        if (m_scale.x >= 0.3f)
        {
            m_state = Finished;
        }

        break;

    case EnState::None:
        if (m_player->IsClear())
        {
            m_isGameClear = true;
            m_state = FadeOut;
        }

        else if (m_player->GetPosition().y <= -400.0f || m_player->IsGameOver())
        {
            m_isGameOver = true;
            m_state = FadeOut;
        }
        break;

    case EnState::Finished:

        m_isFade = false;

        m_scale.x += 0.3f;
        m_scale.y += 0.3f;

        if (m_scale.x >= 30.0f)
        {
            DeleteGO(this);
        }

        if (m_isGameClear && m_gameClear == nullptr)
        {
            m_gameClear = NewGO<GameClear>(0, "GameClear");
        }

        else if (m_isGameOver && m_gameOver == nullptr)
        {
            m_gameOver = NewGO<GameOver>(0, "GameOver");
        }
        break;
    }

    m_fadeSprite.SetScale(m_scale);
    m_fadeSprite.Update();
}
void Fade::Render(RenderContext& rc)
{
    m_fadeSprite.Draw(rc);

    if (m_isFade)
    {
        test.Draw(rc);
    }
}
