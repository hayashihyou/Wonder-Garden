#include "stdafx.h"

#include "AttackCollision.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyState.h"
#include "Player/Player.h"

namespace
{
    const Vector3 COLPOS_Y = Vector3{0, 20, 0};
    const Vector3 COLJUMPPOS_Y = Vector3{0, 35, 0};

    const float ATTACK_COOLTIME = 1.0f;
}

Enemy::~Enemy()
{
    DeleteGO(enemyCollisionObject);
    DeleteGO(enemyJumpCollision);
}

bool Enemy::Start()
{
    m_enemyStatePattern = new EnemyStatePattern;


    m_animationClips[enAnimationClip_Idle].Load("Assets/animData/enemy/slime/slime_Idle.tka");
    m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Attack].Load("Assets/animData/enemy/slime/slime_Attack.tka");
    m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);
    m_animationClips[enAnimationClip_JumpDead].Load("Assets/animData/enemy/slime/slime_Dead.tka");
    m_animationClips[enAnimationClip_JumpDead].SetLoopFlag(false);
    m_animationClips[enAnimationClip_AttackDead].Load("Assets/animData/enemy/slime/slime_Dead2.tka");
    m_animationClips[enAnimationClip_AttackDead].SetLoopFlag(false);


    m_enemyModel.Init("Assets/modelData/enemy/slime/slime.tkm", m_animationClips, enAnimationClip_Num);


     // ステートパターンのステートとIDの登録
    m_enemyStatePattern->RegisterState<EnemyIdleState>(this);
    m_enemyStatePattern->RegisterState<EnemyMoveState>(this);
    m_enemyStatePattern->RegisterState<EnemyAttackState>(this);
    m_enemyStatePattern->RegisterState<EnemyJumpDeadState>(this);
    m_enemyStatePattern->RegisterState<EnemyAttackDeadState>(this);

    m_enemyStatePattern->InitializeState<EnemyIdleState>();


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


    return true;
}

void Enemy::Update()
{
    if (m_player == nullptr)
    {
        m_player = FindGO<Player>("Player");
    }

    m_toPlayer = m_player->GetPosition() - m_position;
    m_disToPlayer = m_toPlayer.Length();

    m_colPos = m_position + COLPOS_Y;
    m_colJumpPos = m_position + COLJUMPPOS_Y;

    enemyCollisionObject->SetPosition(m_colPos);
    enemyJumpCollision->SetPosition(m_colJumpPos);
    m_enemyModel.SetPosition(m_position);

    m_enemyStatePattern->Update();
    m_enemyModel.Update();
}

void Enemy::HP()
{
    if (hp <= 0)
    {
        hp = 0;
        isDead = true;
    }
}


void Enemy::Rotation()
{
    m_rotation.SetRotationYFromDirectionXZ(toPlayerDir);
    m_transform.m_localRotation = m_rotation;
    m_enemyModel.SetRotation(m_rotation);
}


void Enemy::Render(RenderContext& rc)
{
    m_enemyModel.Draw(rc);
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
