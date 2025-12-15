#include "stdafx.h"
#include "BossBarsUI.h"
#include "GameCamera.h"

bool BossBarsUI::Start()
{
    m_gameCamera = FindGO<GameCamera>("GameCamera");

    m_bossBarSprite.Init("Assets/texture/Boss_Bar.DDS",1920.0f,1080.0f);
    m_position = Vector3(0.0f,0.0f,0.0f);
    m_bossBarSprite.SetPosition(m_position);
    m_bossBarSprite.SetMulColor(Vector4(1.0f,1.0f,1.0f,0.5f));
    m_bossBarSprite.Update();

    return true;
}

void BossBarsUI::Update()
{
    if (m_gameCamera->GetBossCamera() == false)
    {
        DeleteGO(this);
        return;
    }

    m_elapsedTime += g_gameTime->GetFrameDeltaTime();
    float percent = m_elapsedTime / 0.5f;
    float alpha = 0.0f;
    if (m_isAdd)
    {
        alpha = Math::Lerp(percent, 0.5f, 1.0f);
    }
    else
    {
        alpha = Math::Lerp(percent, 1.0f, 0.5f);
    }
    if (percent >= 1.0f)
    {
        m_elapsedTime = 0.0f;
        m_isAdd = !m_isAdd;
    }
    
    m_bossBarSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, alpha));

    m_bossBarSprite.SetPosition(m_position);
    m_bossBarSprite.Update();
}

void BossBarsUI::Render(RenderContext& rc)
{
    m_bossBarSprite.Draw(rc);
}
