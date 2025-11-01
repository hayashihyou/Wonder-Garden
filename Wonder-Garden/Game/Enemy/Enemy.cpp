#include "stdafx.h"

#include "AttackCollision.h"
#include "Enemy.h"
#include "EnemyState.h"
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
    m_animationClips[enAnimationClip_Idle].Load("Assets/animData/enemy/slime/slime_Idle.tka");
    m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Attack].Load("Assets/animData/enemy/slime/slime_Attack.tka");
    m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);
    m_animationClips[enAnimationClip_JumpDead].Load("Assets/animData/enemy/slime/slime_Dead.tka");
    m_animationClips[enAnimationClip_JumpDead].SetLoopFlag(false);
    m_animationClips[enAnimationClip_AttackDead].Load("Assets/animData/enemy/slime/slime_Dead2.tka");
    m_animationClips[enAnimationClip_AttackDead].SetLoopFlag(false);

    m_enemyModel.Init("Assets/modelData/enemy/slime/slime.tkm", m_animationClips, enAnimationClip_Num);
    m_colPos = m_pos + COLPOS_Y;

    m_colJumpPos = m_pos + COLJUMPPOS_Y;

    m_enemyModel.SetPosition(m_pos);
    m_enemyModel.SetRotation(m_rot);
    m_enemyModel.Update();

    enemyCollisionObject = NewGO<CollisionObject>(0);
    enemyCollisionObject->CreateSphere(m_colPos, m_rot, 40.0f);
    enemyCollisionObject->SetIsEnableAutoDelete(false);
    enemyJumpCollision = NewGO<CollisionObject>(0);
    enemyJumpCollision->CreateSphere(m_colJumpPos, m_rot, 25.0f);
    enemyJumpCollision->SetIsEnableAutoDelete(false);

    m_stateList[enEnemyState_Idle] = new EnemyIdleState;
    m_stateList[enEnemyState_Idle]->SetOwner(this);
    m_stateList[enEnemyState_Attack] = new EnemyAttackState;
    m_stateList[enEnemyState_Attack]->SetOwner(this);
    m_stateList[enEnemyState_JumpDead] = new EnemyJumpDeadState;
    m_stateList[enEnemyState_JumpDead]->SetOwner(this);
    m_stateList[enEnemyState_AttackDead] = new EnemyAttackDeadState;
    m_stateList[enEnemyState_AttackDead]->SetOwner(this);

    m_currentState = m_stateList[enEnemyState_Idle];

    return true;
}

void Enemy::Update()
{
    if (m_player == nullptr)
    {
        m_player = FindGO<Player>("Player");
    }

    ManagerState();

    Move();

    Rotation();

    UpdateChangeState();

    m_attackCoolTimer -= g_gameTime->GetFrameDeltaTime();
    if (m_attackCoolTimer <= 0.0f)
        m_attackCoolTimer = 0.0f;

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

void Enemy::Attack()
{
    if (m_attackCoolTimer > 0.0f)
        return;

    MakeAttackCollision();

    m_attackCoolTimer = ATTACK_COOLTIME;
}

void Enemy::MakeAttackCollision()
{
    enemyAttack = NewGO<AttackCollision>(0, "AttackCollision");
    enemyAttack->InitTransform(m_pos, attackCol, m_transform);
    enemyAttack->CreateCollision();
    enemyAttack->Update();
}

void Enemy::SetAttackFlag(bool attack)
{
    isAttack = attack;
}

void Enemy::SetDeadFlag(bool dead)
{
    isDead = dead;
}

void Enemy::Move()
{
    if (isStopMove)return;
    toPlayer = m_player->playerPos - m_pos;

    disToPlayer = toPlayer.Length();

    if (disToPlayer < 200)
    {
        toPlayerDir = toPlayer;
        toPlayerDir.Normalize();

        m_pos += toPlayerDir * 1.0f;
        m_transform.m_localPosition = m_pos;

        if (m_player->enPlayerState_Jump)
        {
            m_pos.y = 0;
        }
    }

    if (disToPlayer < 100)
    {
        isAttack = true;
    }

    m_colPos = m_pos + COLPOS_Y;
    m_colJumpPos = m_pos + COLJUMPPOS_Y;

    enemyCollisionObject->SetPosition(m_colPos);
    enemyJumpCollision->SetPosition(m_colJumpPos);
    m_enemyModel.SetPosition(m_pos);
    
}

void Enemy::Rotation()
{
    m_rot.SetRotationYFromDirectionXZ(toPlayerDir);
    m_transform.m_localRotation = m_rot;
    m_enemyModel.SetRotation(m_rot);
}

void Enemy::ManagerState()
{
    // 優先順位
    enum
    {
        PRI_NONE,
        PRI_IDLE,
        PRI_ATTACK,
        PRI_JUMPDEAD,
        PRI_ATTACKDEAD,
    };

    // 優先順位の高いものを入れる変数
    int bestPri = PRI_NONE;
    // 優先するステート
    EnEnemyState bestState = enEnemyState_Idle;

    // 状態を考慮するラムダ式
    auto considerState = [&](int pri, EnEnemyState state)
    {
        // 優先順位が一番高いものを採用する
        if (bestPri < pri)
        {
            bestPri = pri;
            bestState = state;
        }
    };

    if (isDead == true)
    {
        isDead = false;

        if (m_deadReason == enDeadReason_Punch)
        {
            considerState(PRI_ATTACKDEAD, enEnemyState_AttackDead);
            m_currentState = m_stateList[enEnemyState_AttackDead];
            bestState = enEnemyState_AttackDead;
            isStopMove = true;
        }
        if (m_deadReason ==enDeadReason_Jump)
        {
            considerState(PRI_JUMPDEAD, enEnemyState_JumpDead);
            m_currentState = m_stateList[enEnemyState_JumpDead];
            bestState = enEnemyState_JumpDead;
            isStopMove = true;
        }
    }

    if (isAttack == true)
    {
        considerState(PRI_ATTACK, enEnemyState_Attack);
        Attack();
        isStopMove = true;
    }

    m_currentState = m_stateList[bestState];
}

void Enemy::UpdateChangeState()
{
    IEnemyState* nextState = nullptr;

    if (m_currentState == m_stateList[0])
    {
        nextState = m_stateList[enEnemyState_Idle];
    }

    if (m_currentState == m_stateList[1])
    {
        nextState = m_stateList[enEnemyState_Attack];
    }

    if (m_currentState == m_stateList[2])
    {
        nextState = m_stateList[enEnemyState_JumpDead];
    }

    if (m_currentState == m_stateList[3])
    {
        nextState = m_stateList[enEnemyState_AttackDead];
    }

    // 状態切り替わり処理
    if (nextState != nullptr)
    {
        m_currentState->Exit();
        m_currentState = nextState;
        m_currentState->Enter();
    }

    m_currentState->Update();
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
