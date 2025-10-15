#include "stdafx.h"
#include "EnemyState.h"
#include "Enemy.h"

void EnemyIdleState::Enter()
{
	m_enemy = FindGO<Enemy>("Enemy");
	m_enemy->m_enemyModel.PlayAnimation(m_enemy->enAnimationClip_Idle);
}

void EnemyIdleState::Update()
{

}

void EnemyIdleState::Exit()
{

}

void EnemyAttackState::Enter()
{
	m_enemy = FindGO<Enemy>("Enemy");
	m_enemy->m_enemyModel.PlayAnimation(m_enemy->enAnimationClip_Attack);
	m_enemy->SetAttackFlag(true);
}

void EnemyAttackState::Update()
{
	if (!m_enemy->m_enemyModel.IsPlayingAnimation())
	{
		m_enemy->SetAttackFlag(false);
		m_enemy->isStopMove = false;
	}
}

void EnemyAttackState::Exit()
{

}

void EnemyJumpDeadState::Enter()
{
	m_enemy = FindGO<Enemy>("Enemy");
	m_enemy->m_enemyModel.PlayAnimation(m_enemy->enAnimationClip_JumpDead);
	m_enemy->SetDeadFlag(true);
}

void EnemyJumpDeadState::Update()
{
	if (!m_enemy->m_enemyModel.IsPlayingAnimation())
	{
		m_enemy->isStopMove = false;
		DeleteGO(m_enemy);
	}
}

void EnemyJumpDeadState::Exit()
{

}

void EnemyAttackDeadState::Enter()
{
	m_enemy = FindGO<Enemy>("Enemy");
	m_enemy->m_enemyModel.PlayAnimation(m_enemy->enAnimationClip_AttackDead);
	m_enemy->SetDeadFlag(true);

}

void EnemyAttackDeadState::Update()
{
	if (!m_enemy->m_enemyModel.IsPlayingAnimation())
	{
		m_enemy->isStopMove = false;
		DeleteGO(m_enemy);

	}
}

void EnemyAttackDeadState::Exit()
{

}