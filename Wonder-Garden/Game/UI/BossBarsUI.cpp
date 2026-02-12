#include "stdafx.h"
#include "BossBarsUI.h"
#include "GameCamera.h"

namespace
{
    const Vector3 BOSS_ALERT_POSITION = Vector3(0.0f, -350.0f, 0.0f);
}

bool BossBarsUI::Start()
{
    m_gameCamera = FindGO<GameCamera>("GameCamera");

    m_bossBar.Init("Assets/texture/Boss_Battle/Boss_Bar.DDS",1920.0f,1080.0f);
    m_bossAlertFrame.Init("Assets/texture/Boss_Battle/Boss_Frame.DDS",1920.0f,1080.0f);
    m_bossAlert.Init("Assets/texture/Boss_Battle/Boss_Caution.DDS", 960.0f, 540.0f);

    m_position = Vector3(0.0f,0.0f,0.0f);

    m_bossBar.SetPosition(m_position);
    m_bossAlertFrame.SetPosition(BOSS_ALERT_POSITION);
    m_bossAlert.SetPosition(BOSS_ALERT_POSITION);

    m_bossBar.SetMulColor(Vector4(1.0f,1.0f,1.0f,0.5f));
    m_bossAlertFrame.SetMulColor(Vector4(1.0f,1.0f,1.0f,0.5f));
    m_bossAlert.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));

    m_bossBar.Update();
    m_bossAlertFrame.Update();
    m_bossAlert.Update();

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
    
    m_bossBar.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, alpha));
    m_bossAlertFrame.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, alpha));
    m_bossAlert.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, alpha));

    m_bossBar.SetPosition(m_position);
    m_bossAlertFrame.SetPosition(BOSS_ALERT_POSITION);
    m_bossAlert.SetPosition(BOSS_ALERT_POSITION);

    m_bossBar.Update();
    m_bossAlertFrame.Update();
    m_bossAlert.Update();
}

void BossBarsUI::Render(RenderContext& rc)
{
    m_bossBar.Draw(rc);
    m_bossAlertFrame.Draw(rc);
    m_bossAlert.Draw(rc);
}
