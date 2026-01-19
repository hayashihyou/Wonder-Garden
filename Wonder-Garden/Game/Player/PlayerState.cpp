#include "stdafx.h"

#include "AttackCollision.h"
#include "Player.h"
#include "PlayerState.h"
#include "SoundManager.h"
#include "GameCamera.h"


namespace
{
    /// <summary>
    /// 移動方向を取得
    /// </summary>
    /// <param name="direction"></param>
    /// <returns></returns>
    Vector3 GetStickL(const Vector3& direction)
    {
        Vector3 forward = g_camera3D->GetForward();
        Vector3 right = g_camera3D->GetRight();

        forward.y = 0.0f;
        right.y = 0.0f;

        right *= direction.x;
        forward *= direction.z;

        Vector3 retDirection = right + forward;
        retDirection.Normalize();
        return retDirection;
    }

    const float GRAVITY = 0.98f;
    const float ATK_COL_SIZE = 20.0f;
    const Vector3 ATK_POSITION = {0.0f, 30.0f, 50.0f};
} // namespace

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
    m_gameCamera = FindGO<GameCamera>("GameCamera");
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Idle);
}

void PlayerIdleState::Update()
{
    // 待機状態でも重力の影響を受ける
    Vector3 move = Vector3(0.0f, -GRAVITY, 0.0f);
    const Vector3 nextPosition = m_player->GetCharCon()->Execute(move, 1.0f);
    m_player->SetPosition(nextPosition);
}

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

    if (m_player->IsCannon() == true)
    {
        request = PlayerCannonState::ID();
        return true;
    }

    if (m_gameCamera->GetBossCamera() == true)
    {
        request = PlayerBattleState::ID();
        return true;
    }

    if( m_gameCamera->GetStarCamera() == true)
    {
        request = PlayerStarState::ID();
        return true;
    }

    return false;
}

void PlayerWalkState::Enter()
{
    m_gameCamera = FindGO<GameCamera>("GameCamera");
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Walk);
}

void PlayerWalkState::Update()
{
    const Vector3& moveDirection = GetStickL(m_player->GetMoveDir());
    Vector3 move = moveDirection * m_player->GetMoveSpeed();
    move.y -= GRAVITY;

    const Vector3 nextPosition = m_player->GetCharCon()->Execute(move, 1.0f);
    if (fabs(moveDirection.x) >= 0.001f || fabs(moveDirection.z) >= 0.001f)
    {
        Vector3 moveDirectionTemp = move;
        moveDirectionTemp.Normalize();
        m_player->UpdateRotationY(moveDirectionTemp);
    }

    m_player->SetPosition(nextPosition);
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

    if (m_player->IsCannon() == true)
    {
        request = PlayerCannonState::ID();
        return true;
    }

    if (m_gameCamera->GetBossCamera() == true)
    {
        request = PlayerBattleState::ID();
        return true;
    }

    if (m_gameCamera->GetStarCamera() == true)
    {
        request = PlayerStarState::ID();
        return true;
    }

    return false;
}

void PlayerRunState::Enter()
{
    m_gameCamera = FindGO<GameCamera>("GameCamera");
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Run);
}

void PlayerRunState::Update()
{
    const Vector3& moveDirection = GetStickL(m_player->GetMoveDir());
    Vector3 move = moveDirection * m_player->GetMoveSpeed() * 1.5f;

    const Vector3 nextPosition = m_player->GetCharCon()->Execute(move, 1.0f);
    if (fabs(moveDirection.x) >= 0.001f || fabs(moveDirection.z) >= 0.001f)
    {
        Vector3 moveDirectionTemp = move;
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

    if (m_player->IsCannon() == true)
    {
        request = PlayerCannonState::ID();
        return true;
    }

    if (m_gameCamera->GetBossCamera() == true)
    {
        request = PlayerBattleState::ID();
        return true;
    }

    if (m_gameCamera->GetStarCamera() == true)
    {
        request = PlayerStarState::ID();
        return true;
    }

    return false;
}

void PlayerJumpState::Enter()
{
    m_gameCamera = FindGO<GameCamera>("GameCamera");
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Jump);
    m_jump = m_player->GetJumpPower();

    // ジャンプ音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::PlayerJumpSE);
}

void PlayerJumpState::Update()
{
    const Vector3& moveDirection = GetStickL(m_player->GetMoveDir());
    Vector3 move = moveDirection * m_player->GetMoveSpeed();

    // 上方向の移動を計算
    m_jump -= GRAVITY;
    move.y = m_jump;

    Vector3 nextPosition = m_player->GetCharCon()->Execute(move, 1.0f);

    if (fabs(moveDirection.x) >= 0.001f || fabs(moveDirection.z) >= 0.001f)
    {
        Vector3 moveDirectionTemp = move;
        moveDirectionTemp.Normalize();
        m_player->UpdateRotationY(moveDirectionTemp);
    }

    m_player->SetPosition(nextPosition);
}

void PlayerJumpState::Exit() {}

bool PlayerJumpState::RequestState(uint32_t& request)
{
    if (m_player->GetCharCon()->IsOnGround())
    {
        request = PlayerIdleState::ID();
        return true;
    }

    if (m_player->GetCharCon()->IsOnGround())
    {
        if (m_player->IsDamage())
        {
            request = PlayerDamageState::ID();
            return true;
        }
    }

    if (m_player->GetCharCon()->IsOnGround())
    {
        if (m_player->IsDead())
        {
            request = PlayerDeadState::ID();
            return true;
        }
    }

    if (m_player->IsCannon() == true)
    {
        request = PlayerCannonState::ID();
        return true;
    }

    if (m_gameCamera->GetBossCamera() == true)
    {
        request = PlayerBattleState::ID();
        return true;
    }

    if (m_gameCamera->GetStarCamera() == true)
    {
        request = PlayerStarState::ID();
        return true;
    }

    return false;
}

void PlayerAttackState::Enter()
{
    m_gameCamera = FindGO<GameCamera>("GameCamera");
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Attack);

    // パンチ音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::PlayerPunchSE);
}

void PlayerAttackState::Update()
{
    if (m_player->IsAttack())
    {
        if (m_player->GetCollision() != nullptr)
        {
            return;
        }

        MakeAttackCollision();
    }

    else 
    {
        m_player->DeleteAttackCollision();
    }
}

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

    if (m_gameCamera->GetBossCamera() == true || m_gameCamera->GetStarCamera() == true)
    {
        request = PlayerBattleState::ID();
        return true;
    }

    return false;
}

void PlayerAttackState::MakeAttackCollision()
{
    // 攻撃用の当たり判定を作成
    m_player->SetCollision(NewGO<AttackCollision>(0, "AttackCollision"));
    m_player->GetCollision()->InitTransform(ATK_POSITION, GetStickL(m_player->GetForward()), *m_player->GetTransform());
    m_player->GetCollision()->CreateCollision(ATK_COL_SIZE);
    m_player->GetCollision()->Update();
}

void PlayerDamageState::Enter()
{
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Damage);
    m_player->SetDamage(false);

    // ダメージ音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::PlayerDamageSE);
}

void PlayerDamageState::Update()
{
    if (!m_player->GetModel()->IsPlayingAnimation())
    {
        m_player->DeleteAttackCollision();
    }
}

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
        m_player->DeleteAttackCollision();
        m_player->SetGameOverFlag(true);
    }
}

void PlayerDeadState::Exit() {}

bool PlayerDeadState::RequestState(uint32_t& request)
{
    return false;
}

void PlayerCannonState::Enter()
{
    m_gameCamera = FindGO<GameCamera>("GameCamera");
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Idle);
}

void PlayerCannonState::Update() {}

void PlayerCannonState::Exit() {}

bool PlayerCannonState::RequestState(uint32_t& request)
{
    if (m_player->IsFire() == true)
    {
        m_player->SetCannonFlag(false);
        request = PlayerFireState::ID();
        return true;
    }

    return false;
}

void PlayerFireState::Enter()
{
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Fire);

    // 発射音再生
    SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::CanonFireSE);
}

void PlayerFireState::Update()
{

    Quaternion rotation = m_player->GetRotation();


    // 外部からの力を適用
    if (m_player->GetForce().Length() > 0.0f)
    {

        m_player->SetAddForce(m_player->GetForce() - Vector3(0.0f, GRAVITY, 0.0f));

        Vector3 move = m_player->GetForce();

        Vector3 nextpostion = m_player->GetCharCon()->Execute(move, 1.0f);

        m_player->SetPosition(nextpostion);

        if (m_player->GetForce().Length() <= 1.0f)
        {
            m_player->GetForce() = Vector3::Zero;
        }
    }

    if (m_player->GetCharCon()->IsOnGround() == true)
    {
        m_player->SetFireFlag(false);
    }

   /* rotation.AddRotationDegX(5.0f);
    m_player->SetRotation(rotation);*/
}

void PlayerFireState::Exit()
{
    m_player->SetAddForce({0.0f, 0.0f, 0.0f});
}

bool PlayerFireState::RequestState(uint32_t& request)
{
    if (m_player->GetCharCon()->IsOnGround() == true)
    {
        m_player->SetRotation(Quaternion::Identity);
        m_player->SetCannonFlag(false);
        request = PlayerIdleState::ID();
        return true;
    }
    return false;
}

void PlayerBattleState::Enter()
{
    m_gameCamera = FindGO<GameCamera>("GameCamera"); 
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Idle);
}

void PlayerBattleState::Update() {}

void PlayerBattleState::Exit() {}

bool PlayerBattleState::RequestState(uint32_t& request)
{
    if (m_gameCamera->GetBossCamera() == false)
    {
        request = PlayerIdleState::ID();
        return true;
    }

    return false;
}

void PlayerStarState::Enter()
{
    m_gameCamera = FindGO<GameCamera>("GameCamera");
    m_player->GetModel()->PlayAnimation(m_player->enAnimationClip_Idle);
}

void PlayerStarState::Update() {}

void PlayerStarState::Exit() {}

bool PlayerStarState::RequestState(uint32_t& request)
{
    if (m_gameCamera->GetStarCamera() == false)
    {
        request = PlayerIdleState::ID();
        return true;
    }

    return false;
}
