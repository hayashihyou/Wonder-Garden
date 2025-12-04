#include "stdafx.h"

#include "AttackCollision.h"
#include "Enemy/Boss.h"
#include "Enemy/BossState.h"
#include "Player/Player.h"

namespace
{
    Vector3 COLPOS_Y = {0, 30, 0};
}

Boss::~Boss()
{
    DeleteGO(m_bossCollision);
    DeleteGO(m_bossHeadCollision);
}

bool Boss::Start()
{
    m_animationClips[enAnimationClip_Idle].Load("Assets/animData/boss/boss_Idle.tka");
    m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Walk].Load("Assets/animData/boss/boss_Walk.tka");
    m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Attack].Load("Assets/animData/boss/boss_Attack.tka");
    m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);
    m_animationClips[enAnimationClip_Attack2].Load("Assets/animData/boss/boss_Attack2.tka");
    m_animationClips[enAnimationClip_Attack2].SetLoopFlag(false);
    m_animationClips[enAnimationClip_JumpAttack].Load("Assets/animData/boss/boss_JumpAttack.tka");
    m_animationClips[enAnimationClip_JumpAttack].SetLoopFlag(false);
    m_animationClips[enAnimationClip_Damage].Load("Assets/animData/boss/boss_Damage.tka");
    m_animationClips[enAnimationClip_Damage].SetLoopFlag(false);
    m_animationClips[enAnimationClip_Dead].Load("Assets/animData/boss/boss_Dead.tka");
    m_animationClips[enAnimationClip_Dead].SetLoopFlag(false);

    m_bossModel.Init("Assets/modelData/boss/boss.tkm", m_animationClips, enAnimationClip_Num);

    m_bossModel.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName)
    {
        OnAnimationEvent(clipName, eventName);
    });

    auto a = m_animationClips[enAnimationClip_JumpAttack].GetNumAnimationEvent();

    m_scale = {1, 1, 1};

    m_colPosition = m_position + COLPOS_Y;

    m_bossModel.SetPosition(m_position);
    m_bossModel.SetRotation(m_rotation);
    m_bossModel.SetScale(m_scale);
    m_bossModel.Update();

    m_bossCollision = NewGO<CollisionObject>(0);
    m_bossCollision->CreateSphere(m_colPosition, m_rotation, 70.0);
    m_bossCollision->SetIsEnableAutoDelete(false);

    m_bossHeadCollision = NewGO<CollisionObject>(0);
    m_bossHeadCollision->CreateSphere(m_colPosition, m_rotation, 70.0);
    m_bossHeadCollision->SetIsEnableAutoDelete(false);

    m_stateMap.emplace(BossIdleState::ID(), new BossIdleState(this));
    m_stateMap.emplace(BossMoveState::ID(), new BossMoveState(this));
    m_stateMap.emplace(BossAttackState::ID(), new BossAttackState(this));
    m_stateMap.emplace(BossDeadState::ID(), new BossDeadState(this));

    // 初期状態設定
    m_currentStateId = BossIdleState::ID();
    auto it = m_stateMap.find(m_currentStateId);
    if (it != m_stateMap.end())
    {
        it->second->Enter();
    }

    return true;
}

void Boss::Update()
{
    if (m_player == nullptr)
    {
        m_player = FindGO<Player>("Player");
    }

    if (m_isAttackFlag == true)
    {
        if (m_attackCoolTime > 0.0f)
        {
            m_attackCoolTime -= g_gameTime->GetFrameDeltaTime();
        }
    }

    if (m_attackCoolTime <= 0.0f)
    {
        m_isAttackFlag = false;
        m_attackCoolTime = 5.0f;
    }

    m_attackCollision = FindGO<AttackCollision>("AttackCollision");

    toPlayer = m_player->GetPosition() - m_position;
    disToPlayer = toPlayer.Length();

    m_colPosition = m_position + COLPOS_Y;

    m_transform.m_localPosition = m_position;
    m_transform.m_localRotation = m_rotation;

    UpdateChangeState();

    m_bossModel.SetPosition(m_position);
    m_bossModel.SetRotation(m_rotation);
    m_bossCollision->SetPosition(m_colPosition);
    m_bossHeadCollision->SetPosition(m_colPosition);
    m_bossModel.Update();
}

void Boss::HP()
{
    if (hp <= 0)
    {
        hp = 0;
    }
}

void Boss::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
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

void Boss::UpdateChangeState()
{
    auto it = m_stateMap.find(m_currentStateId);
    if (it == m_stateMap.end())
    {
        // 処理できない
        return;
    }
    auto* currentState = it->second;

    uint32_t request;
    if (currentState->RequestState(request))
    {
        currentState->Exit();
        m_currentStateId = request;
        auto it = m_stateMap.find(m_currentStateId);
        if (it != m_stateMap.end())
        {
            currentState = it->second;
            currentState->Enter();
        }
    }
    currentState->Update();
}

void Boss::Render(RenderContext& rc)
{
    m_bossModel.Draw(rc);
}

void Boss::DamagePunch(int damageAmount)
{
    Damage(damageAmount, enDeadReason_Punch);
}

void Boss::DamageReceiveHead(int damageAmount)
{
    Damage(damageAmount, enDeadReason_Jump);
}

void Boss::Damage(int damageAmount, int reason)
{
    hp -= damageAmount;
    HP();

    m_deadReason = (EnDeadReason) reason;
}
