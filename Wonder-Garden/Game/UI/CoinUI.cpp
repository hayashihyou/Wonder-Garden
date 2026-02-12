#include "stdafx.h"

#include "CoinCount.h"
#include "CoinUI.h"

bool CoinUI::Start()
{
    m_coinCounter = FindGO<CoinCounter>("CoinCounter");

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
    m_coinTextOnes.Draw(rc);
    m_coinTextTens.Draw(rc);
}

void CoinUI::InitSprite()
{
    m_sprite.Init("Assets/texture/Coin/coin.DDS", 100.0f, 100.0f);
    m_sprite.SetPosition(Vector3(-850.0f, 475.0f, 0.0f));
    m_coinTextOnes.SetPosition(Vector3(-725.0f, 475.0f, 0.0f));
    m_coinTextTens.SetPosition(Vector3(-775.0f, 475.0f, 0.0f));
    m_sprite.Update();
    m_coinTextOnes.Update();
    m_coinTextTens.Update();
}

void CoinUI::UpdateCoinText()
{
    int counts[2] = {m_coinCounter->GetCountOnes(), m_coinCounter->GetCountTens()};
    SpriteRender* sprites[2] = {&m_coinTextOnes, &m_coinTextTens};
    int* lastValues[2] = {&m_lastOnes, &m_lastTens};

    //１の位と１０の位の２回分処理をする
    for (int i = 0; i < 2; i++)
    {
        //コインの取得枚数に変化があったら
        if (counts[i] != *lastValues[i])
        {
            char filePath[64];
            // 0～9の数値をファイル名に埋め込む
            sprintf_s(filePath, "Assets/texture/Coin/CoinCount_%d.DDS", counts[i]);
            sprites[i]->Init(filePath, 100.0f, 100.0f);
            *lastValues[i] = counts[i];
        }
    }
}
