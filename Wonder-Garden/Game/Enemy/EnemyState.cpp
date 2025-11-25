#include "stdafx.h"
#include "EnemyState.h"
#include "Enemy.h"
#include "Player/Player.h"

namespace
{
    const float GRAVITY = 0.98f;
}

EnemyStatePattern::EnemyStatePattern() : StatePatternBase() {}

EnemyStatePattern::~EnemyStatePattern() {}

void EnemyStatePattern::Update()
{
    K2_ASSERT(m_currentState != nullptr, "カレントステートねえぞこの野郎");
    if (m_currentState)
    {
        uint32_t request;
        if (m_currentState->RequestState(request))
        {
            m_currentState->Exit();
            m_currentState = FindState(request);
            m_currentState->Enter();
        }
        m_currentState->Update();
    }
}

void EnemyIdleState::Enter()
{
	m_enemy->m_enemyModel.PlayAnimation(m_enemy->enAnimationClip_Idle);
}

void EnemyIdleState::Update()
{
    // 待機状態でも重力の影響を受ける
    Vector3 position = Vector3(0.0f, -GRAVITY, 0.0f);
    m_enemy->SetPosition(position);
}

void EnemyIdleState::Exit()
{

}

bool EnemyIdleState::RequestState(uint32_t& request)
{
    if (m_enemy->GetDisToPlayer() < 150.0f)
    {
        request = EnemyMoveState ::ID();
        return true;
    }

    return false;
}

void EnemyMoveState::Enter() {}

void EnemyMoveState::Update() {}

void EnemyMoveState::Exit() {}

bool EnemyMoveState::RequestState(uint32_t& request)
{
    return false;
}

void EnemyAttackState::Enter()
{
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

bool EnemyAttackState::RequestState(uint32_t& request)
{
    return false;
}

void EnemyJumpDeadState::Enter()
{
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

bool EnemyJumpDeadState::RequestState(uint32_t& request)
{
    return false;
}

void EnemyAttackDeadState::Enter()
{
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

bool EnemyAttackDeadState::RequestState(uint32_t& request)
{
    return false;
}
