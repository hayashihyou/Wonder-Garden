#include "stdafx.h"

#include <time.h>

#include "AttackCollision.h"
#include "Boss.h"
#include "BossState.h"
#include "Player/Player.h"
#include "KillCounter.h"
#include "SoundManager.h"
#include "EffectManager.h"

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
     m_attack = rand() % 3;

    if (m_attack == enNormalAttack)
    {
        m_boss->GetModelRender()->PlayAnimation(m_boss->enAnimationClip_Attack);
        m_attackPos = BOSS_ATK_POSITION;
    }

    if (m_attack == enDoubleHitAttack)
    {
        m_boss->GetModelRender()->PlayAnimation(m_boss->enAnimationClip_Attack2);
        m_attackPos = BOSS_ATK_POSITION;
    }

    if (m_attack == enJumpAttack)
    {
        m_boss->GetModelRender()->PlayAnimation(m_boss->enAnimationClip_JumpAttack);
        m_attackPos = BOSS_ATK_POSITION;
        m_attackPos.z += 200.0f;
        
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

        if (m_attack == enJumpAttack && m_effect == nullptr)
        {
            Vector3 offset = m_attackPos;
            m_boss->GetRotation().Apply(offset);
            CreateEffect(m_boss->GetPosition() + offset, m_boss->GetRotation(), EnEffcetType::Boss_Attack);
        }
    }

    else
    {
        // 当たり判定破棄
        m_boss->DeleteAttackCollision();
    }
}

void BossAttackState::Exit()
{
    if (m_effect != nullptr)
    {
        m_effect->Stop();
        m_effect = nullptr;
    }
}

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
    m_boss->GetAttackCollision()->InitTransform(m_attackPos, m_boss->GetToPlayer(), *m_boss->GetTransform());
    m_boss->GetAttackCollision()->CreateCollision(ATK_COL_SIZE);
    m_boss->GetAttackCollision()->Update();
}

void BossAttackState::CreateEffect(Vector3 position, Quaternion rotation, int num)
{
    m_effect = NewGO<EffectEmitter>(0);
    m_effect->SetPosition(position);
    m_effect->SetRotation(rotation);
    m_effect->SetScale({150.0f, 150.0f, 150.0f});
    m_effect->Init(num);
    m_effect->Play();
}

void BossDeadState::Enter()
{
    m_killCounter = FindGO<KillCounter>("KillCounter");
    m_killCounter->BossCount();
    m_boss->GetModelRender()->PlayAnimation(m_boss->enAnimationClip_Dead);
    m_boss->DeleteCollision();
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
