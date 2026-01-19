#include "stdafx.h"

#include "AttackCollision.h"
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Player/PlayerState.h"

namespace
{
    const Vector3 COLPOS_Y = {0.0f, 30.0f, 0.0f};
    const float INVINCIBLE_TIME = 2.0f;
    const float INVINCIBLE_FLASH_TIME = 0.05f;
    const float MOVESPEED = 3.0f;
    const float JUMPPOWER = 15.0f;
} // namespace

bool Player::Start()
{
    m_playerStatePattern = new PlayerStatePattern;

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
    m_animationClips[enAnimationClip_Fire].Load("Assets/animData/player/playerFly.tka");
    m_animationClips[enAnimationClip_Fire].SetLoopFlag(false);

    m_playerModel.Init("Assets/modelData/player/player.tkm", m_animationClips, enAnimationClip_Num);

    m_playerModel.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName)
    {
        OnAnimationEvent(clipName, eventName);
    });

    //m_position = {-1952.0f, 103.0f, 2418.0f};
    m_position = Vector3::Zero;
    m_moveDirection = Vector3::Zero;
    m_moveSpeed = MOVESPEED;
    m_jumpPower = JUMPPOWER;

    // ステートパターンのステートとIDの
    m_playerStatePattern->RegisterState<PlayerIdleState>(this);
    m_playerStatePattern->RegisterState<PlayerWalkState>(this);
    m_playerStatePattern->RegisterState<PlayerRunState>(this);
    m_playerStatePattern->RegisterState<PlayerJumpState>(this);
    m_playerStatePattern->RegisterState<PlayerAttackState>(this);
    m_playerStatePattern->RegisterState<PlayerDamageState>(this);
    m_playerStatePattern->RegisterState<PlayerDeadState>(this);
    m_playerStatePattern->RegisterState<PlayerCannonState>(this);
    m_playerStatePattern->RegisterState<PlayerFireState>(this);
    m_playerStatePattern->RegisterState<PlayerBattleState>(this);
    m_playerStatePattern->RegisterState<PlayerStarState>(this);

    // 最初はIdle(待機)状態から始まるので
    m_playerStatePattern->InitializeState<PlayerIdleState>();

    // キャラクターコントローラーの初期化
    m_characterController.Init(10.0f, 40.0f, m_position);
    m_playerModel.Update();
    return true;
}

void Player::Update()
{
    if (m_isInvincible)
    {
        m_invincibleTimer -= g_gameTime->GetFrameDeltaTime();
    }

    m_moveDirection.x = g_pad[0]->GetLStickXF();
    m_moveDirection.z = g_pad[0]->GetLStickYF();

    // 移動方向があるなら前方向を更新
    if ( m_moveDirection.LengthSq() > 0.0f )
    {
        m_forward = m_moveDirection;
    }

    m_isJump = g_pad[0]->IsTrigger(enButtonA);
    m_isRun = g_pad[0]->IsPress(enButtonX);

    m_transform.m_localPosition = m_position;
    m_transform.m_localRotation = m_rotation;
   
    Attack();
    CheckInvincible();
    m_playerStatePattern->Update();

    // モデルの座標に反映させる
    m_playerModel.SetPosition(m_position);
    m_playerModel.SetRotation(m_rotation);
    m_playerModel.Update();
}

void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
    if (wcscmp(eventName, L"attack_start") == 0)
    {
        m_isAttack = true;
    }
    else if (wcscmp(eventName, L"attack_end") == 0)
    {
        m_isAttack = false;
    }
}

void Player::HP()
{
    if (m_hp > 0)
    {
        m_isDamage = true;
    }

    if (m_hp <= 0)
    {
        m_hp = 0;
        m_isDead = true;
    }
}

void Player::Attack()
{
    m_isAttack = g_pad[0]->IsTrigger(enButtonB);
}

void Player::Move() {}

void Player::Rotation() {}

void Player::Damage(int damageAmount)
{
    if (m_isInvincible == false)
    {
        m_hp -= damageAmount;
        HP();
        m_isInvincible = true;
    }
}

void Player::DeleteAttackCollision()
{
    if (m_punchCollision != nullptr)
    {
        DeleteGO(m_punchCollision);
        m_punchCollision = nullptr;
    }
}

void Player::CheckInvincible()
{
    if (m_invincibleTimer <= 0.0f)
    {
        m_invincibleTimer = INVINCIBLE_TIME;
        m_isInvincible = false;
    }
}

void Player::Render(RenderContext& rc)
{
    // 通常時
    if (!m_isInvincible)
    {
        m_playerModel.Draw(rc);
    }
    // 被弾時の無敵の時
    else
    {
        // 指定秒数ごとに切り替え
        m_drawTimer += g_gameTime->GetFrameDeltaTime();
        if (m_drawTimer >= INVINCIBLE_FLASH_TIME)
        {
            m_drawTimer = 0.0f;
            m_isDraw = !m_isDraw;
        }

        // 描画のon/off
        if (m_isDraw)
        {
            m_playerModel.Draw(rc);
        }
    }
}


    // タイトル画面用のプレイヤークラス
    bool PlayerTitle::Start()
    {
        m_animationClips[enAnimationTitleClip_Title].Load("Assets/animData/player/playerTitle.tka");
        m_animationClips[enAnimationTitleClip_Title].SetLoopFlag(true);
        m_titleModel.Init("Assets/modelData/player/player.tkm", m_animationClips, enAnimationTitleClip_Num);
        m_titleModel.PlayAnimation(enAnimationTitleClip_Title);
        m_position = {0.0f, 0.0f, -50.0f};
        m_titleModel.SetPosition(m_position);
        m_titleModel.Update();

        
        return true;
    }

    void PlayerTitle::Update()
    {
        m_titleModel.SetPosition(m_position);
        m_titleModel.Update();
    }

    void PlayerTitle::Render(RenderContext& rc)
    {
        m_titleModel.Draw(rc);
    }


