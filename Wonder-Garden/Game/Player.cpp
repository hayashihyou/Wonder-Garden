#include "stdafx.h"
#include "Player.h"
#include "PlayerState.h"
#include "Enemy.h"
#include "AttackCollision.h"


namespace
{
    const Vector3 COLPOS_Y = {0.0f, 30.0f, 0.0f};
}
bool Player::Start()
{

    m_animationClips[enAnimationClip_Idle].Load("Assets/animData/player/playerIdle.tka");
    m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Walk].Load("Assets/animData/player/playerWalk.tka");
    m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Run].Load("Assets/animData/player/playerRun.tka");
    m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
    m_animationClips[enAnimationClip_Jump].Load("Assets/animData/player/playerJump.tka");
    m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
    m_animationClips[enAnimationClip_Attack].Load("Assets/animData/player/playerPunch.tka");
    m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);
    m_animationClips[enAnimationClip_Damage].Load("Assets/animData/player/playerDamage.tka");
    m_animationClips[enAnimationClip_Damage].SetLoopFlag(false);
    m_animationClips[enAnimationClip_Dead].Load("Assets/animData/player/playerDead.tka");
    m_animationClips[enAnimationClip_Dead].SetLoopFlag(false);

    m_playerModel.Init("Assets/modelData/player/player.tkm", m_animationClips, enAnimationClip_Num);

    m_stateList[enPlayerState_Idle] = new PlayerIdleState;
    m_stateList[enPlayerState_Walk] = new PlayerWalkState;
    m_stateList[enPlayerState_Run] = new PlayerRunState;
    m_stateList[enPlayerState_Jump] = new PlayerJumpState;
    m_stateList[enPlayerState_Attack] = new PlayerAttackState;
    m_stateList[enPlayerState_Damage ] = new PlayerDamageState;
    m_stateList[enPlayerState_Dead] = new PlayerDeadState;

    m_currentState = m_stateList[enPlayerState_Idle];

    // キャラクターコントローラーの初期化
    m_characterController.Init(10.0f, 40.0f, m_transform.m_localPosition);

    m_colPos = playerPos + COLPOS_Y;

    m_playerModel.Update();
    m_playerHitCollision.Update();

    m_playerHitCollision.CreateCapsule(m_colPos, m_colRot, 10.0f, 40.0f);

    return true;
}

void Player::Update()
{
    ManagerState();

    Move();

    Rotation();

    Attack();

    if (m_invincibleFlag == true)
    {
        m_invincibleTimer -= g_gameTime->GetFrameDeltaTime();
    }

    CheckInvincible();

    UpdateChangeState();
}

void Player::HP()
{
    if (hp > 0)
    {
        m_damageFlag = true;
    }

    if (hp <= 0)
    {
        hp = 0;
        m_deadFlag = true;
    }
}

void Player::Attack()
{
    m_atk = 2;

    if (g_pad[0]->IsTrigger(enButtonB))
    {
        /**TODO:現状複数回呼び出されるからアニメーションが終わるまでコリジョンの生成をなくし処理不可を軽くする */
        MakeAttackCollision();
    }
}

void Player::MakeAttackCollision()
{
    // 攻撃用の当たり判定を作成
    punchCollision = NewGO<AttackCollision>(0, "AttackCollision");
    punchCollision->InitTransform(playerPos, m_atkColPos, m_transform);
    punchCollision->CreateCollision();
    punchCollision->Update();
}

void Player::Move()
{
    // xzの移動速度を0にする
    moveSpeed.x = 0.0f;
    moveSpeed.z = 0.0f;

    // 左スティックの入力量の取得
    Vector3 sthickL;
    sthickL.x = g_pad[0]->GetLStickXF();
    sthickL.z = g_pad[0]->GetLStickYF();

    // カメラの前方向と右方向のベクトルを持ってくる
    Vector3 forward = g_camera3D->GetForward();
    Vector3 right = g_camera3D->GetRight();

    // y方向には移動させない
    forward.y = 0.0f;
    right.y = 0.0f;

    // 左スティックの入力量と120.0fを乗算
    right *= sthickL.x * 120.0f;
    forward *= sthickL.z * 120.0f;

    // 移動速度に加算
    moveSpeed += right + forward;

    if (m_characterController.IsOnGround() == true)
    {
        if (g_pad[0]->IsTrigger(enButtonA))
        {
            if (m_isStopMove == false)
            {
                // ジャンプ
                moveSpeed.y = 350.0f;
            }

            else
            {

            }
        }
    }

    moveSpeed.y -= 10.0f;

    // ストップムーブがtrueなら移動速度を0にする
    if (m_isStopMove)
    {
        moveSpeed.x = 0.0f;
        moveSpeed.z = 0.0f;
    }

    if (g_pad[0]->IsPress(enButtonX))
    {
        moveSpeed.x * 10.0f;
        moveSpeed.z * 10.0f;
    }

    // キャラクターコントローラーを使って座標を移動させる
    m_transform.m_localPosition = m_characterController.Execute(moveSpeed, 1.0f / 60.0f);
    playerPos = m_transform.m_localPosition;

    m_isStopMove = false;

    m_colPos = playerPos + COLPOS_Y;

    // モデルの座標に反映させる
    m_playerModel.SetPosition(m_transform.m_localPosition);
    m_playerHitCollision.SetPosition(m_colPos);

    m_playerModel.Update();
}



void Player::Rotation()
{
    if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
    {
        // キャラクターの向きを変える
        m_transform.m_localRotation.SetRotationYFromDirectionXZ(moveSpeed);
        m_rot = m_transform.m_localRotation;
        m_playerModel.SetRotation(m_rot);
        m_playerHitCollision.SetRotation(m_colRot);
    }
}

void Player::DamagePunch(int damageAmount)
{
    Damage(damageAmount);
}

void Player::Damage(int damageAmount)
{
    if (m_invincibleFlag == false)
    {
        hp -= damageAmount;
        HP();
        m_invincibleFlag = true;
        m_drawFlag = true;
    }
}

void Player::CheckInvincible()
{
    if (m_invincibleTimer <= 0.0f)
    {
        m_invincibleTimer = 3.0f;
        m_invincibleFlag = false;
        m_drawFlag = false;
    }
}

void Player::ManagerState()
{
    // 優先順位
    enum
    {
        PRI__NONE,
        PRI_IDLE,
        PRI_WALK,
        PRI_RUN,
        PRI_JUMP,
        PRI_ATTACK,
        PRI_DAMAGE,
        PRI_DEAD,
    };

    // 優先順位の高いものを入れる変数
    int bestPri = PRI__NONE;
    // 優先するステート
    EnPlayerState bestState = enPlayerState_Idle;

    bool isMove = fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f;

    // 状態を考慮するラムダ式
    auto considerState = [&](int pri, EnPlayerState state)
    {
        // 優先順位が一番高いものを採用する
        if (bestPri < pri)
        {
            bestPri = pri;
            bestState = state;
        }
    };

    // 地面についてないとき
    if (m_characterController.IsOnGround() == false)
    {
        considerState(PRI_JUMP, enPlayerState_Jump);
    }

    // 移動しているとき
    if (isMove)
    {
        // 歩いている状態にする
        considerState(PRI_WALK, enPlayerState_Walk);
    }

    // 走っている状態にする
    if (g_pad[0]->IsPress(enButtonX) && isMove)
    {
        considerState(PRI_RUN, enPlayerState_Run);
    }

    // 攻撃している状態にする
    if (g_pad[0]->IsTrigger(enButtonB) || m_attackFlag)
    {
        considerState(PRI_ATTACK, enPlayerState_Attack);
        m_isStopMove = true;
    }

    if (m_damageFlag == true || m_deadFlag == true)
    {
        m_damageFlag = false;
        m_deadFlag = false;

        if (hp > 0)
        {
            considerState(PRI_DAMAGE, enPlayerState_Damage);
            m_currentState = m_stateList[enPlayerState_Damage];
            bestState = enPlayerState_Damage;
            m_isStopMove = true;
        }

        if (hp <= 0)
        {
            considerState(PRI_DEAD, enPlayerState_Dead);
            m_currentState = m_stateList[enPlayerState_Dead];
            bestState = enPlayerState_Dead;
            m_isStopMove = true;
        }

    }

    // 優先順位が一番高いものを採用する
    m_currentState = m_stateList[bestState];
}

void Player::UpdateChangeState()
{

    IPlayerState* nextState = nullptr;

    if (m_currentState == m_stateList[0])
    {
        nextState = m_stateList[enPlayerState_Idle];
    }

    if (m_currentState == m_stateList[1])
    {
        nextState = m_stateList[enPlayerState_Walk];
    }

    if (m_currentState == m_stateList[2])
    {
        nextState = m_stateList[enPlayerState_Run];
    }

    if (m_currentState == m_stateList[3])
    {
        nextState = m_stateList[enPlayerState_Jump];
    }

    if (m_currentState == m_stateList[4])
    {
        nextState = m_stateList[enPlayerState_Attack];
    }

    if (m_currentState == m_stateList[5])
    {
        nextState = m_stateList[enPlayerState_Damage];
    }

    if (m_currentState == m_stateList[6])
    {
        nextState = m_stateList[enPlayerState_Dead];
    }

    // 状態切り替わり処理
    if (nextState != nullptr)
    {
        m_currentState->Exit();
        m_currentState = nextState;
        m_currentState->Enter();
    }

    m_currentState->Update();
};

void Player::Render(RenderContext& rc)
{
    if (m_invincibleFlag == false)
    {
        m_playerModel.Draw(rc);
    }

    else
    {

        if (m_drawFlag == true)
        {
            m_playerModel.Draw(rc);
            m_drawTimer++;

            if (m_drawTimer == 2)
            {
                m_drawFlag = false;
            }
        }

        else
        {
            m_drawFlag = true;
            m_drawTimer = 0;
        }
    }

}
