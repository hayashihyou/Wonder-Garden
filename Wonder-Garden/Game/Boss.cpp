#include "stdafx.h"
#include "Boss.h"
#include "BossState.h"
#include "Player.h"
#include "AttackCollision.h"

namespace
{
	Vector3 COLPOS_Y = { 0,30,0 };
}

bool Boss::Start()
{
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/boss/SkeletonIdle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Attack].Load("Assets/animData/boss/SkeletonAttack.tka");
	m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Dead].Load("Assets/animData/boss/SkeletonDeath.tka");
	m_animationClips[enAnimationClip_Dead].SetLoopFlag(false);

	m_bossModel.Init("Assets/modelData/boss/Skeleton.tkm", m_animationClips, enAnimationClip_Num);

	m_pos = { 0,0,-200 };
	m_scale = { 8,8,8 };

	m_colPos = m_pos + COLPOS_Y;

	m_bossModel.SetPosition(m_pos);
	m_bossModel.SetRotation(m_rot);
	m_bossModel.SetScale(m_scale);
	m_bossModel.Update();

	m_bossCollision.CreateSphere(m_colPos, m_rot, 70.0);

	m_stateList[enBossState_Idle] = new BossIdleState;
	m_stateList[enBossState_Attack] = new BossAttackState;
	m_stateList[enBossState_Dead] = new BossDeadState;

	m_currentState = m_stateList[enBossState_Idle];

	return true;
}

void Boss::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("Player");
	}

	m_attackCollision = FindGO<AttackCollision>("AttackCollision");

	ManagerState();

	HitJump();

	HitPunch();

	AttackFlag();

	UpdateChangeState();
}

void Boss::HP()
{
	if (hp <= 0)
	{
		hp = 0;
		isDeadFlag = true;
	}
}

void Boss::Attack()
{
}

void Boss::AttackFlag()
{
	toPlayer = m_player->playerPos - m_pos;

	disToPlayer = toPlayer.Length();
	if (disToPlayer < 150)
	{
		isAttackFlag = true;
	}

	m_bossModel.Update();
}

void Boss::SetAttack(bool attack)
{
	isAttackFlag = attack;
}

void Boss::SetDead(bool dead)
{
	isDeadFlag = dead;
}

void Boss::HitJump()
{
	if (m_bossCollision.IsHit(m_player->m_characterController))
	{
		hp -= 2;
		HP();
	}
}

void Boss::HitPunch()
{
	if (m_attackCollision != nullptr)
	{
		if (m_attackCollision->m_punchCollision != nullptr)
		{
			if (m_bossCollision.IsHit(m_attackCollision->m_punchCollision))
			{
				hp -= 2;
				HP();
			}
		}
	}
}

void Boss::ManagerState()
{
	//優先順位
	enum {
		PRI_NONE,
		PRI_IDLE,
		PRI_ATTACK,
		PRI_DEAD,
	};

	//優先順位の高いものを入れる変数
	int bestPri = PRI_NONE;
	//優先するステート
	EnBossState bestState = enBossState_Idle;

	//状態を考慮するラムダ式
	auto considerState = [&](int pri, EnBossState state)
		{
			//優先順位が一番高いものを採用する
			if (bestPri < pri)
			{
				bestPri = pri;
				bestState = state;
			}
		};

	if (isDeadFlag == true)
	{
		isDeadFlag = false;
		considerState(PRI_DEAD, enBossState_Dead);
		m_currentState = m_stateList[enBossState_Dead];
		bestState = enBossState_Dead;
	}

	if (isAttackFlag == true)
	{
		considerState(PRI_ATTACK, enBossState_Attack);
		Attack();
	}

	m_currentState = m_stateList[bestState];

}

void Boss::UpdateChangeState()
{
	IBossState* nextState = nullptr;

	if (m_currentState == m_stateList[0])
	{
		nextState = m_stateList[enBossState_Idle];
	}

	if (m_currentState == m_stateList[1])
	{
		nextState = m_stateList[enBossState_Attack];
	}

	if (m_currentState == m_stateList[2])
	{
		nextState = m_stateList[enBossState_Dead];
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

void Boss::Render(RenderContext& rc)
{
	m_bossModel.Draw(rc);
}
