#include "stdafx.h"
#include "EnemyType2State.h"
#include "EnemyType2.h"
#include "SoundManager.h"

void EnemyType2IdleState::Enter()
{
	m_enemyType2->m_enemyType2Model.PlayAnimation(m_enemyType2->enAnimationClip_Idle);
}

void EnemyType2IdleState::Update()
{
}

void EnemyType2IdleState::Exit()
{
}

void EnemyType2AttackState::Enter()
{
	m_enemyType2->m_enemyType2Model.PlayAnimation(m_enemyType2->enAnimationClip_Attack);
	m_enemyType2->SetAttack(true);

    // 攻撃音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyAttackSE);
}

void EnemyType2AttackState::Update()
{
	if (!m_enemyType2->m_enemyType2Model.IsPlayingAnimation())
	{
		m_enemyType2->SetAttack(false);
	}
}

void EnemyType2AttackState::Exit()
{
}

void EnemyType2AttackDeadState::Enter()
{
    // 攻撃音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyDeathSE);

	m_enemyType2->m_enemyType2Model.PlayAnimation(m_enemyType2->enAnimationClip_AttackDead);
	m_enemyType2->SetDead(true);
}

void EnemyType2AttackDeadState::Update()
{
	if (!m_enemyType2->m_enemyType2Model.IsPlayingAnimation())
	{
		DeleteGO(m_enemyType2);
	}
}

void EnemyType2AttackDeadState::Exit()
{
}

void EnemyType2JumpDeadState::Enter()
{
    // 攻撃音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyDeathSE);

	m_enemyType2->m_enemyType2Model.PlayAnimation(m_enemyType2->enAnimationClip_JumpDead);
	m_enemyType2->SetDead(true);
}

void EnemyType2JumpDeadState::Update()
{
	if (!m_enemyType2->m_enemyType2Model.IsPlayingAnimation())
	{
		DeleteGO(m_enemyType2);
	}
}

void EnemyType2JumpDeadState::Exit()
{
}
