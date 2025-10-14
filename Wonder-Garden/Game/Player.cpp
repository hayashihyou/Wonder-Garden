#include "stdafx.h"
#include "Player.h"
#include "PlayerState.h"
#include "Enemy.h"
#include "AttackCollision.h"


namespace
{
	const Vector3 TO_PLAYER_POS_VECTOR = { 0,30,50 };
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

	m_playerModel.Init("Assets/modelData/player/player.tkm", m_animationClips, enAnimationClip_Num);

	m_stateList[enPlayerState_Idle] = new PlayerIdleState;
	m_stateList[enPlayerState_Walk] = new PlayerWalkState;
	m_stateList[enPlayerState_Run] = new PlayerRunState;
	m_stateList[enPlayerState_Jump] = new PlayerJumpState;
	m_stateList[enPlayerState_Attack] = new PlayerAttackState;

	m_currentState = m_stateList[enPlayerState_Idle];

	//キャラクターコントローラーの初期化
	m_characterController.Init(25.0f, 75.0f, m_transform.m_localPosition);

	m_playerModel.Update();

	return true;
}

void Player::Update()
{
	ManagerState();

	Attack();

	Move();

	Rotation();

	UpdateChangeState();
}

void Player::HP()
{
	hp = 9;
}

void Player::Attack()
{
	m_atk = 2;

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		/**TODO:現状複数回呼び出されるからアニメーションが終わるまでコリジョンの生成をなくし処理不可を軽くする */
		MakeAttackCollision();
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
			//ジャンプ
			moveSpeed.y = 350.0f;
		}
	}

	moveSpeed.y -= 10.0f;

	//ストップムーブがtrueなら移動速度を0にする
	if (m_isStopMove) {
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
	}

	if (g_pad[0]->IsPress(enButtonX))
	{
		moveSpeed.x * 10.0f;
		moveSpeed.z * 10.0f;
	}

	//キャラクターコントローラーを使って座標を移動させる
	m_transform.m_localPosition = m_characterController.Execute(moveSpeed, 1.0f / 60.0f);
	playerPos = m_transform.m_localPosition;

	m_isStopMove = false;

	//モデルの座標に反映させる
	m_playerModel.SetPosition(m_transform.m_localPosition);

	m_playerModel.Update();

}

void Player::SetAttack(bool attackFlag)
{
	m_attackFlag = attackFlag;
}

void Player::Rotation()
{
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		//キャラクターの向きを変える
		m_transform.m_localRotation.SetRotationYFromDirectionXZ(moveSpeed);
		m_playerModel.SetRotation(m_transform.m_localRotation);
	}
}

void Player::MakeAttackCollision()
{
	//攻撃用の当たり判定を作成
	AttackCollision* punchCollision = NewGO<AttackCollision>(0, "AttackCollision");
	punchCollision->InitTransform(playerPos, m_transform);
	punchCollision->CreateCollision();
	punchCollision->Update();
}

void Player::ManagerState()
{
	//優先順位
	enum {
		PRI__NONE,
		PRI_IDLE,
		PRI_WALK,
		PRI_RUN,
		PRI_JUMP,
		PRI_ATTACK
	};

	//優先順位の高いものを入れる変数
	int bestPri = PRI__NONE;
	//優先するステート
	EnPlayerState bestState = enPlayerState_Idle;

	bool isMove = fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f;


	//状態を考慮するラムダ式
	auto considerState = [&](int pri, EnPlayerState state)
		{
			//優先順位が一番高いものを採用する
			if (bestPri < pri)
			{
				bestPri = pri;
				bestState = state;
			}
		};


	//地面についてないとき
	if (m_characterController.IsOnGround() == false)
	{
		considerState(PRI_JUMP, enPlayerState_Jump);
	}

	//移動しているとき
	if (isMove)
	{
		//歩いている状態にする
		considerState(PRI_WALK, enPlayerState_Walk);
	}

	//走っている状態にする
	if (g_pad[0]->IsPress(enButtonX) && isMove)
	{
		considerState(PRI_RUN, enPlayerState_Run);
	}


	//攻撃している状態にする
	if (g_pad[0]->IsTrigger(enButtonA) || m_attackFlag)
	{
		considerState(PRI_ATTACK, enPlayerState_Attack);
		m_isStopMove = true;
	}

	//優先順位が一番高いものを採用する
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

	//状態切り替わり処理
	if (nextState != nullptr)
	{
		m_currentState->Exit();
		m_currentState = nextState;
		m_currentState->Enter();
	}

	m_currentState->Update();

}


void Player::Render(RenderContext& rc)
{
	m_playerModel.Draw(rc);
}


