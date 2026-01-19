#include "stdafx.h"

#include "AttackCollision.h"
#include "Enemy.h"
#include "EnemyState.h"
#include "Player/Player.h"
#include <SoundManager.h>

namespace
{
    const float GRAVITY = 0.98f;
    const float ATK_COL_SIZE = 15.0f;
    const Vector3 ATK_POSITION = Vector3(0.0f, 10.0f, 30.0f);
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
    m_enemy->GetModel()->PlayAnimation(m_enemy->enAnimationClip_Move);
}

void EnemyMoveState::Update()
{
    Vector3 toPlayerDir = m_enemy->GetToPlayer();
    toPlayerDir.Normalize();
    Vector3 position = m_enemy->GetPosition() + toPlayerDir * 1.5f;
    Quaternion rotation = m_enemy->GetRotation();
    rotation.SetRotationYFromDirectionXZ(toPlayerDir);
    m_enemy->SetPosition(position);
    m_enemy->SetRotation(rotation);
}

void EnemyMoveState::Exit() {}

bool EnemyMoveState::RequestState(uint32_t& request)
{
    if (m_enemy->GetDisToPlayer() > 200.0f)
    {
        request = EnemyIdleState::ID();
        return true;
    }

    if (m_enemy->GetDisToPlayer() < 100.0f && m_enemy->IsAttack() == false)
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

void EnemyAttackState::Enter()
{
    m_enemy->GetModel()->PlayAnimation(m_enemy->enAnimationClip_Attack);
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyAttackSE, 0.7f, false);
}

void EnemyAttackState::Update()
{
    if (m_enemy->IsAttack())
    {
        if (m_enemy->GetAttackCollision() != nullptr)
        {
            return;
        }

        MakeAttackCollision();
    }

    else
    {
        if (m_enemy->GetAttackCollision() != nullptr)
        {
            m_enemy->DeleteAttackCollision();
        }
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

void EnemyAttackState::MakeAttackCollision()
{
    // 攻撃用の当たり判定を作成
    m_enemy->SetCollision(NewGO<AttackCollision>(0, "AttackCollision"));
    m_enemy->GetAttackCollision()->InitTransform(ATK_POSITION, m_enemy->GetToPlayer(), *m_enemy->GetTransform());
    m_enemy->GetAttackCollision()->CreateCollision(ATK_COL_SIZE);
    m_enemy->GetAttackCollision()->Update();
}

void EnemyJumpDeadState::Enter()
{
    m_enemy->m_enemyModel.PlayAnimation(m_enemy->enAnimationClip_JumpDead);
}

void EnemyJumpDeadState::Update()
{
    if (!m_enemy->m_enemyModel.IsPlayingAnimation())
    {
        m_enemy->DeleteAttackCollision();
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
        SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyDeathSE, 0.7f, false);
        m_enemy->DeleteAttackCollision();
        DeleteGO(m_enemy);
    }
}

void EnemyAttackDeadState::Exit() {}

bool EnemyAttackDeadState::RequestState(uint32_t& request)
{
    return false;
}
