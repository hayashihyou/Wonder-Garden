#include "stdafx.h"

#include "AttackCollision.h"
#include "EnemyType2.h"
#include "EnemyType2State.h"
#include "Player/Player.h"

namespace
{
    const Vector3 POS_Y = {0, 35, 0};
    const Vector3 JUMPPOS = {0, 45, 0};

    const float ATTACK_COOL_TIME = 5.0f;
}

EnemyType2::~EnemyType2()
{
    DeleteGO(enemyType2Collision);
    DeleteGO(enemyType2JumpCollision);
}

bool EnemyType2::Start()
{
    m_player = FindGO<Player>("Player");

    m_animationClips[enAnimationClip_Idle].Load("Assets/animData/enemy/stone/StoneMonstorIdle.tka");
    m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Attack].Load("Assets/animData/enemy/stone/StoneMonstorAttack.tka");
    m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);
    m_animationClips[enAnimationClip_AttackDead].Load("Assets/animData/enemy/stone/StoneMonstorDeath.tka");
    m_animationClips[enAnimationClip_AttackDead].SetLoopFlag(false);
    m_animationClips[enAnimationClip_JumpDead].Load("Assets/animData/enemy/stone/StoneMonstorDamage.tka");
    m_animationClips[enAnimationClip_AttackDead].SetLoopFlag(false);

    m_enemyType2Model.Init("Assets/modelData/enemy/stone/StoneMonster.tkm", m_animationClips, enAnimationClip_Num);

    m_enemyType2Model.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName)
    {
        OnAnimationEvent(clipName, eventName);
    });

    m_colPos = m_position + POS_Y;
    m_colJumpPos = m_position + JUMPPOS;

    m_enemyType2Model.SetPosition(m_position);
    m_enemyType2Model.SetRotation(m_rotation);
    m_enemyType2Model.Update();

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

    enemyType2Collision = NewGO<CollisionObject>(0);
    enemyType2Collision->CreateSphere(m_colPos, m_rotation, 25.0f);
    enemyType2Collision->SetIsEnableAutoDelete(false);

    enemyType2JumpCollision = NewGO<CollisionObject>(0);
    enemyType2JumpCollision->CreateSphere(m_colJumpPos, m_rotation, 20.0f);
    enemyType2JumpCollision->SetIsEnableAutoDelete(false);

    return true;
}

void EnemyType2::Update()
{
    toPlayer = m_player->GetPosition() - m_position;
    disToPlayer = toPlayer.Length();

    m_colPos = m_position + POS_Y;
    m_colJumpPos = m_position + JUMPPOS;

    m_transform.m_localPosition = m_position;
    m_transform.m_localRotation = m_rotation;

    AttackCoolTimeUpdate();
    UpdateChangeState();

    enemyType2Collision->SetPosition(m_colPos);
    enemyType2JumpCollision->SetPosition(m_colJumpPos);
    m_enemyType2Model.SetPosition(m_position);
    m_enemyType2Model.SetRotation(m_rotation);
    m_enemyType2Model.Update();
}


void EnemyType2::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
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
void EnemyType2::HP()
{
    if (hp <= 0)
    {
        hp = 0;
        m_isDeadFlag = true;
    }
}

void EnemyType2::AttackCoolTimeUpdate()
{
    if (m_isAttackFlag)
    {
        m_attackCoolTime-=g_gameTime->GetFrameDeltaTime();
    }

    if (m_attackCoolTime <= 0.0f)
    {
        m_isAttackFlag = false;
        m_attackCoolTime = ATTACK_COOL_TIME;
    }
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

void EnemyType2::DeleteAttackCollision()
{
    if (m_attackCollision != nullptr)
    {
        DeleteGO(m_attackCollision);
        m_attackCollision = nullptr;
    }
}
