#include "stdafx.h"

#include "Enemy.h"
#include "EnemyState.h"
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
    m_enemy->GetModel()->PlayAnimation(m_enemy->enAnimationClip_Idle);
}

void EnemyIdleState::Update() {}

void EnemyIdleState::Exit() {}

bool EnemyIdleState::RequestState(uint32_t& request)
{
    if (m_enemy->GetDisToPlayer() < 200.0f)
    {
        request = EnemyMoveState ::ID();
        return true;
    }

    if (m_enemy->GetDisToPlayer() < 100.0f)
    {
        request = EnemyAttackState::ID();
        return true;
    }

    if (m_enemy->IsDead() == true && m_enemy->GetDeadReason() == m_enemy->enDeadReason_Jump)
    {
        request = EnemyJumpDeadState::ID();
        return true;
    }

    if (m_enemy->IsDead() == true && m_enemy->GetDeadReason() == m_enemy->enDeadReason_Punch)
    {
        request = EnemyAttackDeadState::ID();
        return true;
    }

    return false;
}

void EnemyMoveState::Enter()
{
    m_enemy->GetModel()->PlayAnimation(m_enemy->enAnimationClip_Idle);
}

void EnemyMoveState::Update()
{
    // 待機状態でも重力の影響を受ける
    Vector3 gravity = Vector3(0.0f, GRAVITY, 0.0f);

    Vector3 toPlayerDir = m_enemy->GetToPlayer();
    toPlayerDir.Normalize();
    Vector3 position = m_enemy->GetPosition() + toPlayerDir * 1.0f;

    m_enemy->SetPosition(position);
}

void EnemyMoveState::Exit() {}

bool EnemyMoveState::RequestState(uint32_t& request)
{
    if (m_enemy->GetDisToPlayer() > 200.0f)
    {
        request = EnemyIdleState::ID();
        return true;
    }

    if(m_enemy->GetDisToPlayer() < 100.0f)
    {
        request = EnemyAttackState::ID();
        return true;
    }

    return false;
}

void EnemyAttackState::Enter()
{
    m_enemy->GetModel()->PlayAnimation(m_enemy->enAnimationClip_Attack);
    m_enemy->SetAttackFlag(true);
}

void EnemyAttackState::Update()
{
    if (!m_enemy->GetModel()->IsPlayingAnimation())
    {
        m_enemy->SetAttackFlag(false);
    }
}

void EnemyAttackState::Exit() {}

bool EnemyAttackState::RequestState(uint32_t& request)
{
    if (!m_enemy->GetModel()->IsPlayingAnimation())
    {
        request = EnemyIdleState::ID();
        return true;
    }
    return false;
}

void EnemyJumpDeadState::Enter()
{
    m_enemy->m_enemyModel.PlayAnimation(m_enemy->enAnimationClip_JumpDead);
}

void EnemyJumpDeadState::Update()
{
    if (!m_enemy->m_enemyModel.IsPlayingAnimation())
    {
        DeleteGO(m_enemy);
    }
}

void EnemyJumpDeadState::Exit() {}

bool EnemyJumpDeadState::RequestState(uint32_t& request)
{
    return false;
}

void EnemyAttackDeadState::Enter()
{
    m_enemy->m_enemyModel.PlayAnimation(m_enemy->enAnimationClip_AttackDead);
}

void EnemyAttackDeadState::Update()
{
    if (!m_enemy->m_enemyModel.IsPlayingAnimation())
    {
        DeleteGO(m_enemy);
    }
}

void EnemyAttackDeadState::Exit() {}

bool EnemyAttackDeadState::RequestState(uint32_t& request)
{
    return false;
}
