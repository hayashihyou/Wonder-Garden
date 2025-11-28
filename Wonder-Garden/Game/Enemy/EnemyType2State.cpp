#include "stdafx.h"
#include "EnemyType2State.h"
#include "EnemyType2.h"
#include "SoundManager.h"

void EnemyType2IdleState::Enter()
{
    m_enemyType2->GetModelRender()->PlayAnimation(m_enemyType2->enAnimationClip_Idle);
}

void EnemyType2IdleState::Update()
{
}

void EnemyType2IdleState::Exit()
{
}

bool EnemyType2IdleState::RequestState(uint32_t& request)
{
    if (m_enemyType2->IsDead())
    {
        if (m_enemyType2->GetDeadReason() == EnemyType2::enDeadReason_Punch)
        {
            request = EnemyType2AttackDeadState::ID();
        }
        else
        {
            request = EnemyType2JumpDeadState::ID();
        }
        return true;
    }
    if (m_enemyType2->IsAttack())
    {
        request = EnemyType2AttackState::ID();
        return true;
    }

    return false;
}

void EnemyType2AttackState::Enter()
{
    m_enemyType2->GetModelRender()->PlayAnimation(m_enemyType2->enAnimationClip_Attack);
	//m_enemyType2->SetAttack(true);

    // 攻撃音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyAttackSE);
}

void EnemyType2AttackState::Update()
{
    m_enemyType2->Attack();

	if (!m_enemyType2->GetModelRender()->IsPlayingAnimation())
	{
		m_enemyType2->SetAttack(false);
	}
}

void EnemyType2AttackState::Exit()
{
}

bool EnemyType2AttackState::RequestState(uint32_t& request)
{
    if (!m_enemyType2->GetModelRender()->IsPlayingAnimation())
    {
        request = EnemyType2IdleState::ID();
        return true;
    }
    return false;
}

void EnemyType2AttackDeadState::Enter()
{
    // 攻撃音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyDeathSE);

	m_enemyType2->GetModelRender()->PlayAnimation(m_enemyType2->enAnimationClip_AttackDead);
	//m_enemyType2->SetDead(true);
}

void EnemyType2AttackDeadState::Update()
{
    if (!m_enemyType2->GetModelRender()->IsPlayingAnimation())
	{
		DeleteGO(m_enemyType2);
	}
}

void EnemyType2AttackDeadState::Exit()
{
}

bool EnemyType2AttackDeadState::RequestState(uint32_t& request)
{
    return false;
}

void EnemyType2JumpDeadState::Enter()
{
    // 攻撃音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyDeathSE);

	m_enemyType2->GetModelRender()->PlayAnimation(m_enemyType2->enAnimationClip_JumpDead);
	//m_enemyType2->SetDead(true);
}

void EnemyType2JumpDeadState::Update()
{
    if (!m_enemyType2->GetModelRender()->IsPlayingAnimation())
	{
		DeleteGO(m_enemyType2);
	}
}

void EnemyType2JumpDeadState::Exit()
{
}

bool EnemyType2JumpDeadState::RequestState(uint32_t& request)
{
    return false;
}
