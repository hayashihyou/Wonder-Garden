#include "stdafx.h"
#include "CoinUI.h"
#include "CoinCount.h"

bool CoinUI::Start()
{
    m_coinCount = FindGO<CoinCount>("CoinCount");

    m_spriteRender.Init("Assets/texture/coin.DDS", 100.0f, 100.0f);
    m_spriteRender.SetPosition(Vector3(200.0f, 475.0f, 0.0f));
    m_spriteRender.Update();

    return true;
}

void CoinUI::Update()
{
    wchar_t coinText[256];
    swprintf_s(coinText, 256, L"%d", m_coinCount->GetCoinCount());
    m_fontRender.SetText(coinText);                          // 表示
    m_fontRender.SetPosition(Vector3(250.0f, 510.0f, 0.0f)); // 場所
    m_fontRender.SetScale(1.5f);                             // 大きさ
    m_fontRender.SetColor({0.0f, 0.0f, 0.0f, 1.0f});         // 色
}

void CoinUI::Render(RenderContext& rc)
{
    m_spriteRender.Draw(rc);
    m_fontRender.Draw(rc);
}
