#include "stdafx.h"
#include "player.h"

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

	m_playerModel.Init("Assets/modelData/player/player.tkm", m_animationClips, enAnimationClip_Num);

	//キャラクターコントローラーの初期化
	m_characterController.Init(25.0f, 75.0f, pos);

	m_playerModel.Update();

	return true;
}

void Player::Update()
{
	Attack();

	Move();

	Rotation();

	ManagerState();

	PlayAnimation();
}

void Player::HP()
{
	hp = 9;
}

void Player::Attack()
{
	atk = 2;

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		playerState = enAnimationClip_Attack;
	}
}

void Player::Move()
{
	//xzの移動速度を0にする
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//左スティックの入力量の取得
	Vector3 sthickL;
	sthickL.x = g_pad[0]->GetLStickXF();
	sthickL.z = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//y方向には移動させない
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量と120.0fを乗算
	right *= sthickL.x * 120.0f;
	forward *= sthickL.z * 120.0f;

	//移動速度に加算
	moveSpeed += right + forward;

	if (m_characterController.IsOnGround() == true)
	{
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			playerState = enAnimationClip_Jump;
			//ジャンプ
			moveSpeed.y = 350.0f;
		}
	}

	moveSpeed.y -= 10.0f;

	//キャラクターコントローラーを使って座標を移動させる
	pos = m_characterController.Execute(moveSpeed, 1.0f / 60.0f);

	//モデルの座標に反映させる
	m_playerModel.SetPosition(pos);

	m_playerModel.Update();
}

void Player::Rotation()
{
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		//キャラクターの向きを変える
		m_rot.SetRotationYFromDirectionXZ(moveSpeed);
		m_playerModel.SetRotation(m_rot);
	}
}

void Player::ManagerState()
{
	//地面についてないとき
	if (m_characterController.IsOnGround() == false)
	{
		playerState == enAnimationClip_Jump;
		return;
	}

	//移動しているとき
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		playerState = enAnimationClip_Walk;

		if (g_pad[0]->IsPress(enButtonX))
		{
			playerState = enAnimationClip_Run;
		}
	}

	else
	{
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			playerState = enAnimationClip_Attack;
		}

		playerState = enAnimationClip_Idle;
	}
}

void Player::PlayAnimation()
{
	switch (playerState)
	{
	case 0:
		m_playerModel.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1:
		m_playerModel.PlayAnimation(enAnimationClip_Walk);
		break;
	case 2:
		m_playerModel.PlayAnimation(enAnimationClip_Run);
		break;
	case 3:
		m_playerModel.PlayAnimation(enAnimationClip_Jump);
		break;
	case 4:
		m_playerModel.PlayAnimation(enAnimationClip_Attack);
		break;
	default:
		break;
	}
}


void Player::Render(RenderContext& rc)
{
	m_playerModel.Draw(rc);
}


