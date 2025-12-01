#include "stdafx.h"

#include "AttackCollision.h"
#include "EnemyType2.h"
#include "EnemyType2State.h"
#include "Player/Player.h"

namespace
{
    const Vector3 POS_Y = {0, 35, 0};
    const Vector3 JUMPPOS = {0, 45, 0};

    const float ATTACK_COOL_TIME = 1.0f;
} // namespace

EnemyType2::~EnemyType2()
{
    DeleteGO(enemyType2Collision);
    DeleteGO(enemyType2JumpCollision);
}

bool EnemyType2::Start()
{
    m_animationClips[enAnimationClip_Idle].Load("Assets/animData/enemy/stone/StoneMonstorIdle.tka");
    m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Attack].Load("Assets/animData/enemy/stone/StoneMonstorAttack.tka");
    m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);
    m_animationClips[enAnimationClip_AttackDead].Load("Assets/animData/enemy/stone/StoneMonstorDeath.tka");
    m_animationClips[enAnimationClip_AttackDead].SetLoopFlag(false);
    m_animationClips[enAnimationClip_JumpDead].Load("Assets/animData/enemy/stone/StoneMonstorDamage.tka");
    m_animationClips[enAnimationClip_AttackDead].SetLoopFlag(false);

    m_enemyType2Model.Init("Assets/modelData/enemy/stone/StoneMonster.tkm", m_animationClips, enAnimationClip_Num);
    m_colPos = m_pos + POS_Y;

    m_colJumpPos = m_pos + JUMPPOS;

    m_enemyType2Model.SetPosition(m_pos);
    m_enemyType2Model.SetRotation(m_rot);
    m_enemyType2Model.Update();

    enemyType2Collision = NewGO<CollisionObject>(0);
    enemyType2Collision->CreateSphere(m_colPos, m_rot, 25.0f);
    enemyType2Collision->SetIsEnableAutoDelete(false);

    enemyType2JumpCollision = NewGO<CollisionObject>(0);
    enemyType2JumpCollision->CreateSphere(m_colJumpPos, m_rot, 20.0f);
    enemyType2JumpCollision->SetIsEnableAutoDelete(false);

    // 状態追加
    m_stateList.emplace(EnemyType2IdleState::ID(), new EnemyType2IdleState(this));
    m_stateList.emplace(EnemyType2AttackState::ID(), new EnemyType2AttackState(this));
    m_stateList.emplace(EnemyType2AttackDeadState::ID(), new EnemyType2AttackDeadState(this));
    m_stateList.emplace(EnemyType2JumpDeadState::ID(), new EnemyType2JumpDeadState(this));
    // 初期状態設定
    m_enemyType2State = EnemyType2IdleState::ID();
    auto it = m_stateList.find(m_enemyType2State);
    if (it != m_stateList.end())
    {
        it->second->Enter();
    }

    return true;
}

void EnemyType2::Update()
{
    if (m_player == nullptr)
    {
        m_player = FindGO<Player>("Player");
    }

    m_attackCollision = FindGO<AttackCollision>("AttackCollision");

    AttackFlag();

    Rotation();

    UpdateChangeState();

    m_attackCoolTime -= g_gameTime->GetFrameDeltaTime();
    if (m_attackCoolTime <= 0.0f)
        m_attackCoolTime = 0.0f;
}

void EnemyType2::HP()
{
    if (hp <= 0)
    {
        hp = 0;
        isDeadFlag = true;
    }
}

void EnemyType2::Attack()
{
    if (m_attackCoolTime > 0.0f)
        return;

    MakeCollision();

    m_attackCoolTime = ATTACK_COOL_TIME;
}

void EnemyType2::AttackFlag()
{
    toPlayer = m_player->GetPosition() - m_pos;

    disToPlayer = toPlayer.Length();
    if (disToPlayer < 100)
    {
        isAttackFlag = true;
    }
    else
    {
        isAttackFlag = false;
    }

    toPlayerDir = toPlayer;
    toPlayerDir.Normalize();
    m_transform.m_localPosition = m_pos;
    m_enemyType2Model.Update();
}

void EnemyType2::MakeCollision()
{
    m_enemyType2Attack = NewGO<AttackCollision>(0);
    m_enemyType2Attack->InitTransform(m_pos, m_attackPos, m_transform);
    m_enemyType2Attack->CreateCollision();
    m_enemyType2Attack->Update();
}

void EnemyType2::SetAttack(bool attack)
{
    isAttackFlag = attack;
}

void EnemyType2::SetDead(bool dead)
{
    isDeadFlag = dead;
}

void EnemyType2::Rotation()
{
    m_rot.SetRotationYFromDirectionXZ(toPlayerDir);
    m_transform.m_localRotation = m_rot;
    m_enemyType2Model.SetRotation(m_rot);
}

void EnemyType2::UpdateChangeState()
{
    auto it = m_stateList.find(m_enemyType2State);
    if (it == m_stateList.end())
    {
        // 処理できない
        return;
    }
    auto* currentState = it->second;

    uint32_t request;
    if (currentState->RequestState(request))
    {
        currentState->Exit();
        m_enemyType2State = request;
        auto it = m_stateList.find(m_enemyType2State);
        if (it != m_stateList.end())
        {
            currentState = it->second;
            currentState->Enter();
        }
    }
    currentState->Update();
}

void EnemyType2::Render(RenderContext& rc)
{
    m_enemyType2Model.Draw(rc);
}

void EnemyType2::DamagePunch(int damageAmount)
{
    Damage(damageAmount, enDeadReason_Punch);
}

void EnemyType2::DamageReceiveHead(int damageAmount)
{
    Damage(damageAmount, enDeadReason_Jump);
}

void EnemyType2::Damage(int damageAmount, int reason)
{
    hp -= damageAmount;
    HP();

    m_deadReason = (EnDeadReason) reason;
}
