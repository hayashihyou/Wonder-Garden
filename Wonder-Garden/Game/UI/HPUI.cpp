#include "stdafx.h"
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
    static const HPIconInfo HP_ICON_INFO_LIST[] =
    {
        HPIconInfo("Assets/texture/HP.DDS", 1.0f),
        HPIconInfo("Assets/texture/HP_1.DDS", 0.875f),
        HPIconInfo("Assets/texture/HP_2.DDS", 0.75f),
        HPIconInfo("Assets/texture/HP_3.DDS", 0.625f),
        HPIconInfo("Assets/texture/HP_4.DDS", 0.5f),
        HPIconInfo("Assets/texture/HP_5.DDS", 0.375f),
        HPIconInfo("Assets/texture/HP_6.DDS", 0.25f),
        HPIconInfo("Assets/texture/HP_7.DDS", 0.125f),
        HPIconInfo("Assets/texture/HP_8.DDS", 0.0f)
    };

    int GetHPIconType(const float hpRatio)
    {
        for (int i=0;i< Maximum;i++)
        {
            auto& info = HP_ICON_INFO_LIST[i];
            if (info.ratio <= hpRatio)
            {
                return i;
            }
        }
        return HP0;
    }
}


HPUI::HPUI()
{

}


HPUI::~HPUI()
{

}


bool HPUI::Start()
{
    for (int i = 0; i < Maximum; i++)
    {
        std::unique_ptr<SpriteRender> render = std::make_unique<SpriteRender>();
        render->Init(HP_ICON_INFO_LIST[i].path.c_str(), 500.0f, 300.0f);
        render->SetPosition(Vector3(0.0f, 400.0f, 0.0f));
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
}
