#include "stdafx.h"

#include "Boss.h"
#include "BossState.h"
#include "SoundManager.h"

void BossIdleState::Enter()
{
    m_boss = FindGO<Boss>("Boss");
    m_boss->GetModelRender()->PlayAnimation(m_boss->enAnimationClip_Idle);
}

void BossIdleState::Update() {}

void BossIdleState::Exit() {}

bool BossIdleState::RequestState(uint32_t& request)
{
    if (m_boss->IsDead())
    {
        request = BossDeadState::ID();
        return true;
    }
    if (m_boss->IsAttack())
    {
        request = BossAttackState::ID();
        return true;
    }
    return false;
}

void BossAttackState::Enter()
{
    m_boss = FindGO<Boss>("Boss");
    m_boss->GetModelRender()->PlayAnimation(m_boss->enAnimationClip_Attack);
    m_boss->SetAttack(true);

    // 攻撃音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyAttackSE);
}

void BossAttackState::Update()
{
    m_boss->Attack();
    if (!m_boss->GetModelRender()->IsPlayingAnimation())
    {
        m_boss->SetAttack(false);
    }
}

void BossAttackState::Exit() {}

bool BossAttackState::RequestState(uint32_t& request)
{
    if (!m_boss->GetModelRender()->IsPlayingAnimation())
    {
        request = BossIdleState::ID();
        return true;
    }
    return false;
}

void BossDeadState::Enter()
{
    m_boss = FindGO<Boss>("Boss");
    m_boss->GetModelRender()->PlayAnimation(m_boss->enAnimationClip_Dead);
    m_boss->SetDead(true);
}

void BossDeadState::Update()
{
    if (!m_boss->GetModelRender()->IsPlayingAnimation())
    {
        // 攻撃音再生
        SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyDeathSE);

        DeleteGO(m_boss);
    }
}

void BossDeadState::Exit() {}

bool BossDeadState::RequestState(uint32_t& request)
{
    return false;
}
