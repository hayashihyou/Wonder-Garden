#include "stdafx.h"

#include "Player/Player.h"
#include "Star.h"
#include "StarCounter.h"

namespace
{
    const float ROTATION_SPEED = 3.0f;                        // 回転速度
    const float GET_STAR_DISTANCE = 120.0f;                   // 星取得距離
    const Vector3 STAR_POSITION = {2300.0f, 300.0f, 2730.0f}; // 星の座標
} // namespace

bool Star::Start()
{
    m_player = FindGO<Player>("Player");

    // 初期化
    Init();

    return true;
}

void Star::Update()
{
    m_toPlayer = m_player->GetPosition() - m_pos;
    m_distanceToPlayer = m_toPlayer.Length();

    // 星取得判定
    if (m_distanceToPlayer <= GET_STAR_DISTANCE)
    {
        m_starCounter = FindGO<StarCounter>("StarCounter");
        m_starCounter->AddStarCount();
        DeleteGO(this);
    }

    // 回転
    Rotation();

    // モデル更新
    m_model.Update();
}

void Star::Init()
{
    m_model.Init("Assets/modelData/star.tkm");
    m_pos = STAR_POSITION;
    m_model.SetPosition(m_pos);
    m_model.Update();
}

void Star::Rotation()
{
    m_rot.AddRotationDegY(ROTATION_SPEED);
    m_model.SetRotation(m_rot);
}

void Star::Render(RenderContext& rc)
{
    m_model.Draw(rc);
}
