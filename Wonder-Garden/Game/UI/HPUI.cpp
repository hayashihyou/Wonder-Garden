#include "stdafx.h"

#include "Enemy/Boss.h"
#include "HPUI.h"

namespace
{
    enum HPIconType
    {
        HPMax,
        HP7,
        HP6,
        HP5,
        HP4,
        HP3,
        HP2,
        HP1,
        HP0,
        Maximum,
    };

    struct HPIconInfo
    {
        std::string path;
        float ratio;
        //
        HPIconInfo(const std::string& s, const float r) : path(s), ratio(r) {}
    };
    static const HPIconInfo HP_ICON_INFO_LIST[] = {
        HPIconInfo("Assets/texture/HP.DDS", 1.0f),    HPIconInfo("Assets/texture/HP_1.DDS", 0.875f),
        HPIconInfo("Assets/texture/HP_2.DDS", 0.75f), HPIconInfo("Assets/texture/HP_3.DDS", 0.625f),
        HPIconInfo("Assets/texture/HP_4.DDS", 0.5f),  HPIconInfo("Assets/texture/HP_5.DDS", 0.375f),
        HPIconInfo("Assets/texture/HP_6.DDS", 0.25f), HPIconInfo("Assets/texture/HP_7.DDS", 0.125f),
        HPIconInfo("Assets/texture/HP_8.DDS", 0.0f)};

    int GetHPIconType(const float hpRatio)
    {
        for (int i = 0; i < Maximum; i++)
        {
            auto& info = HP_ICON_INFO_LIST[i];
            if (info.ratio <= hpRatio)
            {
                return i;
            }
        }
        return HP0;
    }
} // namespace

HPUI::HPUI() {}

HPUI::~HPUI() {}

bool HPUI::Start()
{
    m_boss = FindGO<Boss>("Boss");

    for (int i = 0; i < Maximum; i++)
    {
        std::unique_ptr<SpriteRender> render = std::make_unique<SpriteRender>();
        render->Init(HP_ICON_INFO_LIST[i].path.c_str(), 450.0f, 250.0f);
        render->SetPosition(Vector3(0.0f, 425.0f, 0.0f));
        render->Update();
        m_hpList.push_back(std::move(render));
    }
    return true;
}

void HPUI::Update()
{
    int index = GetHPIconType(m_hpRatio);
    m_hpList[index]->Update();
}

void HPUI::Render(RenderContext& rc)
{
    int index = GetHPIconType(m_hpRatio);
    m_hpList[index]->Draw(rc);

    if (m_boss->GetBattleFlag() == true)
    {
        m_HPBarBack.Draw(rc);
        m_HPBarDamage.Draw(rc);
        m_HPBar.Draw(rc);
        m_HPBarFrame.Draw(rc);
    }
}

void HPUI::InitHPBar()
{
    m_HPBarBack.Init("Assets/texture/Boss_HPBar_Back.DDS", 550.0f, 80.0f);
    m_HPBarDamage.Init("Assets/texture/Boss_HPBar_Damage.DDS", 550.0f, 80.0f);
    m_HPBar.Init("Assets/texture/Boss_HPBar.DDS", 550.0f, 80.0f);
    m_HPBarFrame.Init("Assets/texture/Boss_HPBarFrame_Trans.DDS", 650.0f, 130.0f);

    m_HPBarBack.SetScale(Vector3(1.0f, 1.0f, 1.0f));
    m_HPBarDamage.SetScale(Vector3(1.0f, 1.0f, 1.0f));
    m_HPBar.SetScale(Vector3(0.0f, 1.0f, 1.0f));
    m_HPBarFrame.SetScale(Vector3(1.0f, 1.0f, 1.0f));

    m_HPBarBack.SetMulColor(Vector4::Black);
    m_HPBarBack.SetPosition(Vector3(335.0f, 450.0f, 0.0f));
    m_HPBarBack.SetPivot(Vector2(0.0f, 0.5f));

    m_HPBarDamage.SetMulColor(Vector4::Red);
    m_HPBarDamage.SetPosition(Vector3(335.0f, 450.0f, 0.0f));
    m_HPBarDamage.SetPivot(Vector2(0.0f, 0.5f));

    m_HPBar.SetMulColor(Vector4::Green);
    m_HPBar.SetPosition(Vector3(335.0f, 450.0f, 0.0f));
    m_HPBar.SetPivot(Vector2(0.0f, 0.5f));

    m_HPBarFrame.SetPosition(Vector3(285.0f, 450.0f, 0.0f));
    m_HPBarFrame.SetPivot(Vector2(0.0f, 0.5f));

    m_HPBarBack.Update();
    m_HPBarDamage.Update();
    m_HPBar.Update();
    m_HPBarFrame.Update();
}

void HPUI::ChangeState()
{
    if (m_boss->GetAppear())
    {
        m_hpBarState = enAPPEAR;
    }

    else
    {
        m_hpBarState = enNormal;
    }
}

void HPUI::UpdateHPBar()
{
    switch (m_hpBarState)
    {
    case enAPPEAR:
    {
        scal = m_HPBar.GetScale();
        scal.x += 0.01f;

        if (scal.x >= 1.0f)
        {
            scal.x = 1.0f;
            m_boss->SetAppear(false);
            m_hpBarState = enNormal;
        }

        m_HPBar.SetScale(scal);
        m_HPBar.Update();
    }
    break;

    case enNormal:
    {
        if (m_boss->GetDamaged())
        {
            int currentHP = m_boss->GetHP();
            int maxHP = m_boss->GetMaxHP();
            float wari = (float) currentHP / (float) maxHP;
            scal = m_HPBar.GetScale();
            Vector3 hpBarScal = m_HPBarDamage.GetScale();

            scal.x = wari;

            if (scal.x <= 0.0f)
            {
                scal.x = 0.0f;
            }

            if (hpBarScal.x >= scal.x)
            {
                hpBarScal.x -= 0.01f;
            }

            m_HPBar.SetScale(scal);
            m_HPBarDamage.SetScale(hpBarScal);
            m_HPBar.Update();
            m_HPBarDamage.Update();

            // 現在のHPまでバーを縮めたらダメージフラグをfalseにする
            if (hpBarScal.x == scal.x)
            {
                m_boss->SetDamaged(false);
            }
        }
        break;
    }
    default:
        break;
    }
}
