#include "stdafx.h"

#include "Magic.h"
#include "EnemyType2.h"
#include "EnemyType2State.h"
#include "SoundManager.h"

namespace
{
    const Vector3 ATK_POSITION = Vector3(0.0f, 30.0f, 20.0f);
    const float ATK_COL_SIZE = 15.0f;
}

void EnemyType2IdleState::Enter()
{
    m_enemyType2->GetModelRender()->PlayAnimation(m_enemyType2->enAnimationClip_Idle);
}

void EnemyType2IdleState::Update()
{
    Vector3 toPlayerDir = m_enemyType2->GetToPlayer();
    toPlayerDir.Normalize();
    Quaternion rotation = m_enemyType2->GetRotation();
    rotation.SetRotationYFromDirectionXZ(toPlayerDir);
    m_enemyType2->SetRotation(rotation);
}

void EnemyType2IdleState::Exit() {}

bool EnemyType2IdleState::RequestState(uint32_t& request)
{
    if (m_enemyType2->GetDisToPlayer() < 100.0f && m_enemyType2->IsAttack() == false)
    {
        request = EnemyType2AttackState::ID();
        return true;
    }

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

    return false;
}

void EnemyType2AttackState::Enter()
{
    m_enemyType2->GetModelRender()->PlayAnimation(m_enemyType2->enAnimationClip_Attack);

    // 攻撃音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyAttackSE);
}

void EnemyType2AttackState::Update()
{
    if (m_enemyType2->IsAttack())
    {
        if (m_enemyType2->GetAttackCollision() != nullptr)
        {
            return;    
        }

        MakeAttackCollision();
    }

    else
    {
        if (m_enemyType2->GetAttackCollision() != nullptr)
        {
            m_enemyType2->DeleteAttackCollision();
        }
    }
}

void EnemyType2AttackState::Exit() {}

bool EnemyType2AttackState::RequestState(uint32_t& request)
{
    if (!m_enemyType2->GetModelRender()->IsPlayingAnimation())
    {
        request = EnemyType2IdleState::ID();
        return true;
    }

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

    return false;
}

void EnemyType2AttackState::MakeAttackCollision()
{
    m_enemyType2->SetAttackCollision(NewGO<Magic>(0, "Magic"));
    m_enemyType2->GetAttackCollision()->CreateCollision(ATK_COL_SIZE);
    m_enemyType2->GetAttackCollision()->Update();
}

void EnemyType2AttackDeadState::Enter()
{
    // 攻撃音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyDeathSE);

    m_enemyType2->GetModelRender()->PlayAnimation(m_enemyType2->enAnimationClip_AttackDead);
}

void EnemyType2AttackDeadState::Update()
{
    if (!m_enemyType2->GetModelRender()->IsPlayingAnimation())
    {
        m_enemyType2->DeleteAttackCollision();
        DeleteGO(m_enemyType2);
    }
}

void EnemyType2AttackDeadState::Exit() {}

bool EnemyType2AttackDeadState::RequestState(uint32_t& request)
{
    return false;
}

void EnemyType2JumpDeadState::Enter()
{
    // 攻撃音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyDeathSE);

    m_enemyType2->GetModelRender()->PlayAnimation(m_enemyType2->enAnimationClip_JumpDead);
}

void EnemyType2JumpDeadState::Update()
{
    if (!m_enemyType2->GetModelRender()->IsPlayingAnimation())
    {
        m_enemyType2->DeleteAttackCollision();
        DeleteGO(m_enemyType2);
    }
}

void EnemyType2JumpDeadState::Exit() {}

bool EnemyType2JumpDeadState::RequestState(uint32_t& request)
{
    return false;
}
