#include "stdafx.h"
#include "BossState.h"
#include "Boss.h"
#include "SoundManager.h"

void BossIdleState::Enter()
{
	m_boss = FindGO<Boss>("Boss");
	m_boss->m_bossModel.PlayAnimation(m_boss->enAnimationClip_Idle);
}

void BossIdleState::Update()
{
}

void BossIdleState::Exit()
{
}

void BossAttackState::Enter()
{
	m_boss = FindGO<Boss>("Boss");
	m_boss->m_bossModel.PlayAnimation(m_boss->enAnimationClip_Attack);
	m_boss->SetAttack(true);

    // 攻撃音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyAttackSE);
}

void BossAttackState::Update()
{
	if (!m_boss->m_bossModel.IsPlayingAnimation())
	{
		m_boss->SetAttack(false);
	}
}

void BossAttackState::Exit()
{
}

void BossDeadState::Enter()
{
	m_boss = FindGO<Boss>("Boss");
	m_boss->m_bossModel.PlayAnimation(m_boss->enAnimationClip_Dead);
	m_boss->SetDead(true);
}

void BossDeadState::Update()
{
	if (!m_boss->m_bossModel.IsPlayingAnimation())
	{
        // 攻撃音再生
        SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyDeathSE);

		DeleteGO(m_boss);
	}
}

void BossDeadState::Exit()
{
}
