#include "stdafx.h"
#include "Enemy.h"
#include "EnemyState.h"
#include "Player.h"
#include "AttackCollision.h"

namespace
{
	const Vector3 COLPOS_Y = Vector3{ 0, 20, 0 };
	const Vector3 COLJUMPPOS_Y = Vector3{ 0,60,0 };
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
	m_pos = { 200,0,0 };
	m_colPos = m_pos + COLPOS_Y;

	m_colJumpPos = m_pos + COLJUMPPOS_Y;

	m_enemyModel.SetPosition(m_pos);
	m_enemyModel.SetRotation(m_rot);
	m_enemyModel.Update();

	enemyCollisionObject.CreateSphere(m_colPos, m_rot, 40.0f);
	enemyJumpCollision.CreateSphere(m_colJumpPos, m_rot, 25.0f);

	m_stateList[enEnemyState_Idle] = new EnemyIdleState;
	m_stateList[enEnemyState_Attack] = new EnemyAttackState;
	m_stateList[enEnemyState_JumpDead] = new EnemyJumpDeadState;
	m_stateList[enEnemyState_AttackDead] = new EnemyAttackDeadState;

	m_currentState = m_stateList[enEnemyState_Idle];

	return true;
}

void Enemy::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("Player");
	}

	m_attackCollision = FindGO<AttackCollision>("AttackCollision");

	ManagerState();

	JumpHit();

	PunchHit();

	Move();

	Rotation();

	UpdateChangeState();
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
	if (m_player->hp >= 1)
	{
		m_player->hp - 1;
	}
}

void Enemy::SetAttackFlag(bool attack)
{
	isAttack = attack;
}

void Enemy::Move()
{
	toPlayer = m_player->playerPos - m_pos;

	disToPlayer = toPlayer.Length();

	if (isStopMove == true)
	{
		toPlayer = currentToPlayer;
		if ((toPlayer - currentToPlayer).Length() < 0.001f || (toPlayer - currentToPlayer).Length() > 0.001f)
		{
			currentToPlayer = toPlayer;
		}
	}

	if (disToPlayer < 200)
	{
		toPlayerDir = toPlayer;
		toPlayerDir.Normalize();

		m_pos += toPlayerDir * 1.0f;

		m_colPos = m_pos + COLPOS_Y;
		m_colJumpPos = m_pos + COLJUMPPOS_Y;

		if (m_player->enPlayerState_Jump)
		{
			m_pos.y = 0;
		}

		enemyCollisionObject.SetPosition(m_colPos);
		enemyJumpCollision.SetPosition(m_colJumpPos);
		m_enemyModel.SetPosition(m_pos);
		m_enemyModel.Update();

	}

	if (disToPlayer < 100)
	{
		isAttack = true;
	}

}

void Enemy::JumpHit()
{
	if (enemyJumpCollision.IsHit(m_player->m_characterController))
	{
		hp -= 2;
		HP();
	}
}

void Enemy::PunchHit()
{
	if (m_attackCollision != nullptr)
	{
		if (m_attackCollision->m_punchCollision != nullptr)
		{
			if (enemyCollisionObject.IsHit(m_attackCollision->m_punchCollision))
			{
				hp -= 2;
				HP();
			}
		}
	}
}

void Enemy::Rotation()
{

}

void Enemy::ManagerState()
{
	//優先順位
	enum {
		PRI_NONE,
		PRI_IDLE,
		PRI_ATTACK,
		PRI_JUMPDEAD,
		PRI_ATTACKDEAD,
	};

	//優先順位の高いものを入れる変数
	int bestPri = PRI_NONE;
	//優先するステート
	EnEnemyState bestState = enEnemyState_Idle;

	//状態を考慮するラムダ式
	auto considerState = [&](int pri, EnEnemyState state)
		{
			//優先順位が一番高いものを採用する
			if (bestPri < pri)
			{
				bestPri = pri;
				bestState = state;
			}
		};

	if (isAttack == true)
	{
		considerState(PRI_ATTACK, enEnemyState_Attack);
		Attack();
		isStopMove = true;
	}

	if (isDead == true)
	{
		isDead = false;

		if (m_attackCollision != nullptr && m_attackCollision->m_punchCollision != nullptr)
		{
			considerState(PRI_ATTACKDEAD, enEnemyState_AttackDead);
			m_currentState = m_stateList[enEnemyState_AttackDead];
			isStopMove = true;
		}

		else
		{
			considerState(PRI_JUMPDEAD, enEnemyState_JumpDead);
			bestState = enEnemyState_JumpDead;
			isStopMove = true;
		}

		if (bestState != enEnemyState_AttackDead)
		{
			m_currentState = m_stateList[enEnemyState_JumpDead];
		}

	}

	if (!bestState == enEnemyState_AttackDead || !bestState == enEnemyState_JumpDead)
	{
		m_currentState = m_stateList[bestState];
	}

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

	//状態切り替わり処理
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
