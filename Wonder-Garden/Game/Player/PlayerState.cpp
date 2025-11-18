#include "stdafx.h"

#include "AttackCollision.h"
#include "Player.h"
#include "PlayerState.h"

PlayerStatePattern::PlayerStatePattern() : StatePatternBase() {}

PlayerStatePattern::~PlayerStatePattern() {}

void PlayerStatePattern::Update()
{
    K2_ASSERT(m_currentState != nullptr, "カレントステートねえぞこの野郎");
    if (m_currentState)
    {
        uint32_t request;
        if (m_currentState->RequestState(request))
        {
            m_currentState->Exit();
            m_currentState = FindState(request);
            m_currentState->Enter();
        }
        m_currentState->Update();
    }
}

void PlayerIdleState::Enter()
{
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Idle);
}

void PlayerIdleState::Update() {}

void PlayerIdleState::Exit() {}

bool PlayerIdleState::RequestState(uint32_t& request)
{
    if (m_player->GetMoveDir().LengthSq() > 0.01f)
    {
        request = PlayerWalkState::ID();
        return true;
    }

    if (m_player->IsJump())
    {
        request = PlayerJumpState::ID();
        return true;
    }

    if (m_player->IsAttack())
    {
        request = PlayerAttackState::ID();
        return true;
    }

    if (m_player->IsDamage())
    {
        request = PlayerDamageState::ID();
        return true;
    }

    if (m_player->IsDead())
    {
        request = PlayerDeadState::ID();
        return true;
    }

    return false;
}

void PlayerWalkState::Enter()
{
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Walk);
}

void PlayerWalkState::Update()
{
    Vector3 moveSpeed;

    moveSpeed.x = 0.0f;
    moveSpeed.z = 0.0f;

    Vector3 moveDirection;
    moveDirection.x = g_pad[0]->GetLStickXF();
    moveDirection.z = g_pad[0]->GetLStickYF();

    // カメラの前方向と右方向のベクトルを持ってくる
    Vector3 forward = g_camera3D->GetForward();
    Vector3 right = g_camera3D->GetRight();

    // y方向には移動させない
    forward.y = 0.0f;
    right.y = 0.0f;

    right *= moveDirection.x * 300.0f;
    forward *= moveDirection.z * 300.0f;

    moveSpeed += right + forward;

    Vector3 nextPosition = m_player->GetCharCon()->Execute(moveSpeed, 1.0f / 60.0f);

    if (fabs(moveDirection.x) >= 0.001f || fabs(moveDirection.z) >= 0.001f)
    {
        Vector3 moveDirectionTemp = moveSpeed;
        moveDirectionTemp.Normalize();
        m_player->UpdateRotationY(moveDirectionTemp);
    }
    m_player->SetPosition(nextPosition);
    m_player->SetMoveSpeed(moveSpeed);
}

void PlayerWalkState::Exit() {}

bool PlayerWalkState::RequestState(uint32_t& request)
{
    // 入力がなければ待機状態に戻す。
    if (m_player->GetMoveDir().LengthSq() <= 0.01f)
    {
        request = PlayerIdleState::ID();
        return true;
    }

    // ジャンプ入力があったらジャンプステートになる
    if (m_player->IsJump())
    {
        request = PlayerJumpState::ID();
        return true;
    }

    if (m_player->IsRun())
    {
        request = PlayerRunState::ID();
        return true;
    }

    if (m_player->IsAttack())
    {
        request = PlayerAttackState::ID();
        return true;
    }

    if (m_player->IsDamage())
    {
        request = PlayerDamageState::ID();
        return true;
    }

    if (m_player->IsDead())
    {
        request = PlayerDeadState::ID();
        return true;
    }

    return false;
}

void PlayerRunState::Enter()
{
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Run);
}

void PlayerRunState::Update()
{
    Vector3 moveSpeed;

    moveSpeed.x = 0.0f;
    moveSpeed.z = 0.0f;

    Vector3 moveDirection;
    moveDirection.x = g_pad[0]->GetLStickXF();
    moveDirection.z = g_pad[0]->GetLStickYF();

    // カメラの前方向と右方向のベクトルを持ってくる
    Vector3 forward = g_camera3D->GetForward();
    Vector3 right = g_camera3D->GetRight();

    // y方向には移動させない
    forward.y = 0.0f;
    right.y = 0.0f;

    right *= moveDirection.x * 500.0f;
    forward *= moveDirection.z * 500.0f;

    moveSpeed += right + forward;

    Vector3 nextPosition = m_player->GetCharCon()->Execute(moveSpeed, 1.0f / 60.0f);

    if (fabs(moveDirection.x) >= 0.001f || fabs(moveDirection.z) >= 0.001f)
    {
        Vector3 moveDirectionTemp = moveSpeed;
        moveDirectionTemp.Normalize();
        m_player->UpdateRotationY(moveDirectionTemp);
    }
    m_player->SetPosition(nextPosition);
}

void PlayerRunState::Exit() {}

bool PlayerRunState::RequestState(uint32_t& request)
{
    if (m_player->GetMoveDir().LengthSq() <= 0.01f)
    {
        request = PlayerIdleState::ID();
        return true;
    }

    if (!m_player->IsRun())
    {
        request = PlayerWalkState::ID();
        return true;
    }

    // ジャンプ入力があったらジャンプステートになる
    if (m_player->IsJump())
    {
        request = PlayerJumpState::ID();
        return true;
    }

    if (m_player->IsAttack())
    {
        request = PlayerAttackState::ID();
        return true;
    }

    if (m_player->IsDamage())
    {
        request = PlayerDamageState::ID();
        return true;
    }

    if (m_player->IsDead())
    {
        request = PlayerDeadState::ID();
        return true;
    }

    return false;
}

void PlayerJumpState::Enter()
{
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Jump);
}

// TODO:重力がうまくいってないから後で聞こう
void PlayerJumpState::Update()
{

    // 速度変えるため
    Vector3 accele = {0.0f, -500.0f, 0.0f};

    accele *= g_gameTime->GetFrameDeltaTime();

    Vector3 jump = m_player->GetJumpPower();
    jump += accele;

    m_player->SetJumpPower(jump);

    Vector3 jumpPos = m_player->GetCharCon()->Execute(jump, g_gameTime->GetFrameDeltaTime());

    if (m_player->GetCharCon()->IsOnGround() == true)
    {
        jump = Vector3::Zero;
        m_player->SetJumpPower(jump);
    }

    m_player->SetPosition(jumpPos);
}

void PlayerJumpState::Exit() {}

bool PlayerJumpState::RequestState(uint32_t& request)
{
    if (!m_player->GetModel()->IsPlayingAnimation())
    {
        request = PlayerIdleState::ID();
        return true;

        if (m_player->GetCharCon()->IsOnGround() == true)
        {
            Vector3 jump = Vector3::Zero;
            m_player->SetJumpPower(jump);
        }
    }

    if (m_player->IsAttack())
    {
        request = PlayerAttackState::ID();
        return true;
    }

    if (m_player->IsDamage())
    {
        request = PlayerDamageState::ID();
        return true;
    }

    if (m_player->IsDead())
    {
        request = PlayerDeadState::ID();
        return true;
    }

    return false;
}

void PlayerAttackState::Enter()
{
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Attack);
    m_player->SetAttack(true);
    MakeAttackCollision();
}

void PlayerAttackState::Update() {}

void PlayerAttackState::Exit() {}

bool PlayerAttackState::RequestState(uint32_t& request)
{
    if (!m_player->GetModel()->IsPlayingAnimation())
    {
        request = PlayerIdleState::ID();
        return true;
    }

    if (m_player->IsDamage())
    {
        request = PlayerDamageState::ID();
        return true;
    }

    if (m_player->IsDead())
    {
        request = PlayerDeadState::ID();
        return true;
    }

    return false;
}

void PlayerAttackState::MakeAttackCollision()
{
    // 攻撃用の当たり判定を作成
    m_player->SetCollision(NewGO<AttackCollision>(0, "AttackCollision"));
    m_player->GetCollision()->InitTransform(m_player->GetPosition(), m_player->GetMoveSpeed(),
                                            *m_player->GetTransform());
    m_player->GetCollision()->CreateCollision();
    m_player->GetCollision()->Update();
}

void PlayerDamageState::Enter()
{
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Damage);
    m_player->SetDamage(false);
}

void PlayerDamageState::Update() {}

void PlayerDamageState::Exit() {}

bool PlayerDamageState::RequestState(uint32_t& request)
{
    if (!m_player->GetModel()->IsPlayingAnimation())
    {
        request = PlayerIdleState::ID();
        return true;
    }

    return false;
}

void PlayerDeadState::Enter()
{
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Dead);
}

void PlayerDeadState::Update()
{
    if (!m_player->GetModel()->IsPlayingAnimation())
    {
        m_player->SetGameOverFlag(true);
    }
}

void PlayerDeadState::Exit() {}

bool PlayerDeadState::RequestState(uint32_t& request)
{
    return false;
}

void PlayerFireState::Enter() {}

void PlayerFireState::Update()
{
    //// 外部からの力を適用
    // if (m_player->GetForce().Length() > 0.0f)
    //{
    //     m_player->GetMoveSpeed() += m_player->GetForce();
    //     m_player->GetForce() *= 0.9f;

    //    // ストップじゃない
    //    m_player->SetStopMove(false);

    //    if (m_player->GetForce().Length() <= 1.0f)
    //    {
    //        m_player->GetForce() = Vector3::Zero;
    //    }
    //}

    // if (m_player->GetCharCon()->IsOnGround() == true)
    //{
    //     m_player->SetFireFlag(false);
    // }
}

void PlayerFireState::Exit()
{
    /* m_player->SetAddForce({0.0f,0.0f,0.0f});*/
}

bool PlayerFireState::RequestState(uint32_t& request)
{
    return false;
}
