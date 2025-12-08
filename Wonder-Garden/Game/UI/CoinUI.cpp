#include "stdafx.h"

#include "CoinCount.h"
#include "CoinUI.h"

bool CoinUI::Start()
{
    m_countCointer = FindGO<CountCointer>("CoinCounter");

    // フォント初期化
    InitFont();

    // スプライト初期化
    InitSprite();

    return true;
}

void CoinUI::Update()
{
    UpdateCoinText();
}

void CoinUI::Render(RenderContext& rc)
{
    m_sprite.Draw(rc);
    m_font.Draw(rc);
}

void CoinUI::InitFont()
{
    m_font.SetPosition(Vector3(250.0f, 510.0f, 0.0f)); // 位置
    m_font.SetScale(1.5f);                             // 大きさ
    m_font.SetColor(Vector4::Black);         // 色
}

void CoinUI::InitSprite()
{
    m_sprite.Init("Assets/texture/coin.DDS", 100.0f, 100.0f);
    m_sprite.SetPosition(Vector3(200.0f, 475.0f, 0.0f));
    m_sprite.Update();
}

void CoinUI::UpdateCoinText()
{
    wchar_t coinCountText[256];
    swprintf_s(coinCountText, 256, L"%d", m_countCointer->GetCount());
    m_font.SetText(coinCountText);
}
