#include "stdafx.h"
#include "EnemyType2.h"

namespace
{
    const Vector3 POS_Y = { 0,60,0 };
}

bool EnemyType2::Start()
{
    m_animationClips[enAnimationClip_Idle].Load("Assets/animData/enemy/eye/eye_Idle.tka");
    m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);

    m_enemyType2Model.Init("Assets/modelData/enemy/eye/eye.tkm");
    m_pos = { -200,0,0 };
    m_colPos = m_pos + POS_Y;

    m_enemyType2Model.SetPosition(m_pos);
    m_enemyType2Model.SetRotation(m_rot);
    m_enemyType2Model.Update();

    m_enemyType2Collison.CreateSphere(m_colPos, m_rot, 40.0f);
    return true;
}

void EnemyType2::Update()
{
    PlayAnimation();
}

void EnemyType2::HP()
{
}

void EnemyType2::Attack()
{
}

void EnemyType2::Move()
{
}

void EnemyType2::PlayAnimation()
{
    m_enemyType2Model.PlayAnimation(enAnimationClip_Idle);
    m_enemyType2Model.Update();
}

void EnemyType2::Render(RenderContext& rc)
{
    m_enemyType2Model.Draw(rc);
}
