#include "stdafx.h"

#include "AttackCollision.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyState.h"
#include "Player/Player.h"

namespace
{
    const Vector3 COLPOS_Y = Vector3{0, 20, 0};
    const Vector3 COLJUMPPOS_Y = Vector3{0, 35, 0};

    const float ATTACK_COOLTIME = 3.0f;
}

Enemy::~Enemy()
{
    DeleteGO(enemyCollisionObject);
    DeleteGO(enemyJumpCollision);
}

bool Enemy::Start()
{
    m_player = FindGO<Player>("Player");


    m_animationClips[enAnimationClip_Idle].Load("Assets/animData/enemy/slime/slime_Idle.tka");
    m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Move].Load("Assets/animData/enemy/slime/slime_Move.tka");
    m_animationClips[enAnimationClip_Move].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Attack].Load("Assets/animData/enemy/slime/slime_Attack.tka");
    m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);
    m_animationClips[enAnimationClip_JumpDead].Load("Assets/animData/enemy/slime/slime_Dead.tka");
    m_animationClips[enAnimationClip_JumpDead].SetLoopFlag(false);
    m_animationClips[enAnimationClip_AttackDead].Load("Assets/animData/enemy/slime/slime_Dead2.tka");
    m_animationClips[enAnimationClip_AttackDead].SetLoopFlag(false);


    m_enemyModel.Init("Assets/modelData/enemy/slime/slime.tkm", m_animationClips, enAnimationClip_Num);

    m_enemyModel.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName)
    {
        OnAnimationEvent(clipName, eventName);
    });

    m_colPos = m_position + COLPOS_Y;
    m_colJumpPos = m_position + COLJUMPPOS_Y;
    m_enemyModel.SetPosition(m_position);
    m_enemyModel.SetRotation(m_rotation);
    m_enemyModel.Update();

    enemyCollisionObject = NewGO<CollisionObject>(0);
    enemyCollisionObject->CreateSphere(m_colPos, m_rotation, 40.0f);
    enemyCollisionObject->SetIsEnableAutoDelete(false);
    enemyJumpCollision = NewGO<CollisionObject>(0);
    enemyJumpCollision->CreateSphere(m_colJumpPos, m_rotation, 25.0f);
    enemyJumpCollision->SetIsEnableAutoDelete(false);

    // 状態追加
    m_stateList.emplace(EnemyIdleState::ID(), new EnemyIdleState(this));
    m_stateList.emplace(EnemyMoveState::ID(), new EnemyMoveState(this));
    m_stateList.emplace(EnemyAttackState::ID(), new EnemyAttackState(this));
    m_stateList.emplace(EnemyAttackDeadState::ID(), new EnemyAttackDeadState(this));
    m_stateList.emplace(EnemyJumpDeadState::ID(), new EnemyJumpDeadState(this));
    // 初期状態設定
    m_enemyState = EnemyIdleState::ID();
    auto it = m_stateList.find(m_enemyState);
    if (it != m_stateList.end())
    {
        it->second->Enter();
    } 

    return true;
}

void Enemy::Update()
{
    m_toPlayer = m_player->GetPosition() - m_position;
    m_disToPlayer = m_toPlayer.Length();

    m_colPos = m_position + COLPOS_Y;
    m_colJumpPos = m_position + COLJUMPPOS_Y;

    m_transform.m_localPosition = m_position;
    m_transform.m_localRotation = m_rotation;

    AttackCoolTimeUpdate();
    UpdateChangeState();

    if (enemyCollisionObject)
    {
        enemyCollisionObject->SetPosition(m_colPos);
    }
    enemyJumpCollision->SetPosition(m_colJumpPos);
    m_enemyModel.SetPosition(m_position);
    m_enemyModel.SetRotation(m_rotation);


    m_enemyModel.Update();
}

void Enemy::HP()
{
    if (hp <= 0)
    {
        hp = 0;
        m_isDeadFlag = true;
    }
}

void Enemy::Render(RenderContext& rc)
{
    m_enemyModel.Draw(rc);
}

void Enemy::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
    if (wcscmp(eventName, L"attack_start") == 0)
    {
        m_isAttackFlag = true;
    }
    else if (wcscmp(eventName, L"attack_end") == 0)
    {
        m_isAttackFlag = false;
    }
}

void Enemy::AttackCoolTimeUpdate()
{
    if (m_isAttackFlag)
    {
        m_attackCoolTimer -= g_gameTime->GetFrameDeltaTime();
    }

    if (m_attackCoolTimer <= 0.0f)
    {
        m_isAttackFlag = false;
        m_attackCoolTimer = ATTACK_COOLTIME;
    }
}

void Enemy::UpdateChangeState()
{
    auto it = m_stateList.find(m_enemyState);
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
        m_enemyState = request;
        auto it = m_stateList.find(m_enemyState);
        if (it != m_stateList.end())
        {
            currentState = it->second;
            currentState->Enter();
        }
    }
    currentState->Update();
}


void Enemy::DamagePunch(int damageAmount)
{
    Damge(damageAmount, enDeadReason_Punch);
}

void Enemy::DamageReceiveHead(int damageAmount)
{
    Damge(damageAmount, enDeadReason_Jump);
}

void Enemy::Damge(int damageAmount, int reason)
{
    hp -= damageAmount;
    HP();

    m_deadReason = (EnDeadReason)reason;
}

void Enemy::DeleteAttackCollision()
{
    if (m_attackCollision != nullptr)
    {
        DeleteGO(m_attackCollision);
        m_attackCollision = nullptr;
    }
}
