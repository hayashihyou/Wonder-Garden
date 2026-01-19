#include "stdafx.h"

#include "Enemy/Boss.h"
#include "Player/Player.h"
#include "Star.h"
#include "StarCounter.h"
#include "cmath"
#include <SoundManager.h>

namespace
{
    const float ROTATION_SPEED = 3.0f;                        // 回転速度
    const float GET_STAR_DISTANCE = 120.0f;                   // 星取得距離
    const Vector3 STAR_POSITION = {2300.0f, 300.0f, 3400.0f}; // 星の座標
} // namespace

bool Star::Start()
{
    m_player = FindGO<Player>("Player");
    m_boss = FindGO<Boss>("Boss");

    // 初期化
    Init();

    return true;
}

void Star::Update()
{
    CreateStar();

    m_toPlayer = m_player->GetPosition() - m_position;
    m_distanceToPlayer = m_toPlayer.Length();

    // 星取得判定
    if (m_distanceToPlayer <= GET_STAR_DISTANCE)
    {
        SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::GetStarSE, 0.7f, false);
        m_starCounter = FindGO<StarCounter>("StarCounter");
        m_starCounter->AddStarCount();
        DeleteGO(this);
    }

    // 回転
    Rotation();

    m_model.SetPosition(m_position);
    m_model.SetRotation(m_rot);
    // モデル更新
    m_model.Update();
}

void Star::Init()
{
    m_model.Init("Assets/modelData/star.tkm");
    m_position = m_boss->GetPosition();
    m_position.y += 100.0f;
    m_starPosition = STAR_POSITION;
    m_model.SetPosition(m_position);
    m_model.Update();
}

void Star::Rotation()
{
    m_rot.AddRotationDegY(ROTATION_SPEED);
    m_model.SetRotation(m_rot);
}

void Star::CreateStar()
{

    // もしゴール地点よりX座標が小さければX座標を増やす
    if (m_starPosition.x > m_position.x)
    {
        m_position.x += 10.0f;

        m_position.y += 2.0f;
        if (m_position.x >= m_starPosition.x)
        {
            m_position.x = m_starPosition.x;
        }

        if (m_position.y >= m_starPosition.y)
        {
            m_position.y -= 4.0f;
        }
    }

    if (m_starPosition.x < m_position.x)
    {
        m_position.x -= 10.0f;


        m_position.y += 2.0f;
        if (m_position.x <= m_starPosition.x)
        {
            m_position.x = m_starPosition.x;
        }

        if (m_position.y >= m_starPosition.y)
        {
            m_position.y -= 4.0f;
        }
    }

    if (m_starPosition.z > m_position.z)
    {
        m_position.z += 10.0f;

        m_position.y += 2.0f;
        if (m_position.z >= m_starPosition.z)
        {
            m_position.z = m_starPosition.z;
        }

        if (m_position.y >= m_starPosition.y)
        {
            m_position.y -= 4.0f;
        }
    }

    if (m_starPosition.z < m_position.z)
    {
        m_position.z -= 10.0f;

        m_position.y += 2.0f;

        if (m_position.z <= m_starPosition.z)
        {
            m_position.z = m_starPosition.z;
        }

        if (m_position.y >= m_starPosition.y)
        {
            m_position.y -= 4.0f;
        }
    }

    if (m_starPosition.x == m_position.x && m_starPosition.z == m_position.z)
    {
        if (!m_isHopMove)
        {
            m_hopMoveStartPos = m_position;     //  ホップ移動開始位置を保存
        }

        m_isHopMove = true;

        //末尾の値でバウンドの緩急を調整できる(小さい数字だとゆっくりで大きい数字だと素早く動く)
        m_t += g_gameTime->GetFrameDeltaTime()*3;

        float velY;

        //2πまでバウンドさせる
        if (m_t <= 2 * 3.14159)
        {
            // 減衰率
            float damping = std::exp(-m_t);

            // ホップ
            // abs::絶対値
            float hop = abs(sin(m_t));

            m_position.y = m_hopMoveStartPos.y + (hop * damping )* 300;
        }
    }

    m_model.SetPosition(m_position);
}

void Star::Render(RenderContext& rc)
{
    m_model.Draw(rc);
}
