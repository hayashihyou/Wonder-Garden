#include "stdafx.h"
#include "Coin.h"
#include "CoinCount.h"
#include "UI/CoinUI.h"
#include "Player/Player.h"

bool Coin::Start()
{
    m_modelRender.Init("Assets/item/coin.tkm");

    m_modelRender.SetPosition(m_position);
    m_modelRender.SetRotation(m_rotation);
    m_modelRender.Update();

    return true;
}

void Coin::Update()
{
    if (m_player == nullptr)
    {
        m_player = FindGO<Player>("Player");
    }

    CoinGet();
    Rotation();

    m_modelRender.Update();
}

void Coin::CoinGet()
{
    Vector3 toPlayer = m_player->GetPosition() - m_position;
    float disToPlayer = toPlayer.Length();
    if (disToPlayer < 30.0f)
    {
        m_coinCount = FindGO<CoinCount>("CoinCount");
        m_coinCount->AddCoinCount();
        int hp = m_player->GetHP() + 1;
        m_player->SetHP(hp);
        DeleteGO(this);
    }

     m_modelRender.SetPosition(m_position);
}

void Coin::Rotation()
{
    m_rotation.AddRotationDegY(5.0f);
    m_modelRender.SetRotation(m_rotation);
}

void Coin::Render(RenderContext& rc)
{
    m_modelRender.Draw(rc);
}
