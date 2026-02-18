#include "stdafx.h"

#include "Fade.h"
#include "GameClear.h"
#include "GameOver.h"
#include "Player/Player.h"

bool Fade::Start()
{
    m_player = FindGO<Player>("Player");

    m_fadeSprite.Init("Assets/texture/FadeIn/FadeIn.DDS", 9000.0f, 9000.0f);

    m_state = EnState::FadeIn;
    m_scale = {30.0f, 30.0f, 1.0f};

    m_fadeSprite.SetPosition(m_position);
    m_fadeSprite.SetScale(m_scale);
    m_fadeSprite.Update();

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

        else if (m_player->IsGameOver())
        {
            m_isGameOver = true;
            m_state = FadeOut;
        }
        break;

    case EnState::Finished:

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
}

//void Fade::FadeIn()
//{
//    if (m_scale.x < 10.0f)
//    {
//        m_scale += {0.2f, 0.2f, 0.0f};
//    }
//    else
//    {
//        DeleteGO(this);
//    }
//
//    m_fadeSprite.SetScale(m_scale);
//    m_fadeSprite.Update();
//}

//void Fade::FadeOut()
//{
//    if (m_scale.x > 0.5f)
//    {
//        m_scale -= {0.3f, 0.3f, 0.0f};
//    }
//
//    else
//    {
//        m_scale = Vector3::Zero;
//        m_isFade = true;
//    }
//
//    m_fadeSprite.SetScale(m_scale);
//    m_fadeSprite.Update();
//}
