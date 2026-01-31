#include "stdafx.h"

#include <time.h>

#include "AttackCollision.h"
#include "Boss.h"
#include "BossState.h"
#include "Player/Player.h"
#include "SoundManager.h"

namespace
{
    const float ATK_COL_SIZE = 60.0f;
    const Vector3 BOSS_ATK_POSITION = {0, 30, 200};
} // namespace

void BossIdleState::Enter()
{
    m_boss->GetModelRender()->PlayAnimation(m_boss->enAnimationClip_Idle);
}

void BossIdleState::Update() {}

void BossIdleState::Exit() {}

bool BossIdleState::RequestState(uint32_t& request)
{
    if (m_boss->GetDisToPlayer() < 500.0f)
    {
        request = BossMoveState::ID();
        return true;
    }

    if (m_boss->GetDisToPlayer() < 150.0f && m_boss->IsAttack() == false)
    {
        request = BossAttackState::ID();
        return true;
    }

    if (m_boss->GetHP() == 0)
    {
        request = BossDeadState::ID();
        return true;
    }

    return false;
}

void BossMoveState::Enter()
{
    m_boss->GetModelRender()->PlayAnimation(m_boss->enAnimationClip_Walk);
}

void BossMoveState::Update()
{
    // 移動処理
    Vector3 toPlayerDir = m_boss->GetToPlayer();
    toPlayerDir.Normalize();
    Vector3 position = m_boss->GetPosition() + toPlayerDir * 4.0f;
    Quaternion rotation = m_boss->GetRotation();
    rotation.SetRotationYFromDirectionXZ(toPlayerDir);
    m_boss->SetPosition(position);
    m_boss->SetRotation(rotation);
}

void BossMoveState::Exit() {}

bool BossMoveState::RequestState(uint32_t& request)
{
    if (m_boss->GetDisToPlayer() > 500.0f)
    {
        request = BossIdleState::ID();
        return true;
    }

    if (m_boss->GetDisToPlayer() < 150.0f && m_boss->IsAttack() == false)
    {
        request = BossAttackState::ID();
        return true;
    }

    if (m_boss->GetHP() == 0)
    {
        request = BossDeadState::ID();
        return true;
    }

    return false;
}

void BossAttackState::Enter()
{
    srand(time(nullptr));
    int attack = rand() % 3;

    if (attack == enNormalAttack)
    {
        m_boss->GetModelRender()->PlayAnimation(m_boss->enAnimationClip_Attack);
    }

    if (attack == enDoubleHitAttack)
    {
        m_boss->GetModelRender()->PlayAnimation(m_boss->enAnimationClip_Attack2);
    }

    if (attack == enJumpAttack)
    {
        m_boss->GetModelRender()->PlayAnimation(m_boss->enAnimationClip_JumpAttack);
    }

    // 攻撃音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyAttackSE);
}

void BossAttackState::Update()
{
    if (m_boss->IsAttack())
    {
        if (m_boss->GetAttackCollision() != nullptr)
        {
            return;
        }

        // 攻撃判定生成
        MakeAttackCollision();
    }

    else
    {
        // 当たり判定破棄
        m_boss->DeleteAttackCollision();
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

    if (m_boss->GetHP() == 0)
    {
        request = BossDeadState::ID();
        m_boss->DeleteAttackCollision();
        return true;
    }

    return false;
}

void BossAttackState::MakeAttackCollision()
{
    m_boss->SetCollision(NewGO<AttackCollision>(0));
    m_boss->GetAttackCollision()->InitTransform(BOSS_ATK_POSITION, m_boss->GetToPlayer(), *m_boss->GetTransform());
    m_boss->GetAttackCollision()->CreateCollision(ATK_COL_SIZE);
    m_boss->GetAttackCollision()->Update();
}

void BossDeadState::Enter()
{
    m_boss->GetModelRender()->PlayAnimation(m_boss->enAnimationClip_Dead);
}

void BossDeadState::Update()
{
    if (!m_boss->GetModelRender()->IsPlayingAnimation())
    {
        m_boss->SetDead(true);
    }
}

void BossDeadState::Exit() {}

bool BossDeadState::RequestState(uint32_t& request)
{
    if (m_boss->IsDead() == true)
    {
        m_boss->SetDead(false);
        request = BossDownState::ID();
        return true;
    }
    return false;
}

void BossDownState::Enter()
{
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::EnemyDeathSE);
}

void BossDownState::Update() {}

void BossDownState::Exit() {}

bool BossDownState::RequestState(uint32_t& request)
{
    return false;
}
