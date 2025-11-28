#include "stdafx.h"
#include "Enemy/Boss.h"
#include "Enemy/BossState.h"
#include "Player/Player.h"
#include "AttackCollision.h"

namespace
{
	Vector3 COLPOS_Y = { 0,30,0 };
}

Boss::~Boss()
{
    DeleteGO(m_bossCollision);
    DeleteGO(m_bossHeadCollision);
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

    m_bossCollision = NewGO<CollisionObject>(0);
	m_bossCollision->CreateSphere(m_colPos, m_rot, 70.0);
    m_bossCollision->SetIsEnableAutoDelete(false);

    m_bossHeadCollision = NewGO<CollisionObject>(0);
    m_bossHeadCollision->CreateSphere(m_colPos, m_rot, 70.0);
    m_bossHeadCollision->SetIsEnableAutoDelete(false);

    m_stateMap.emplace(BossIdleState::ID(), new BossIdleState(this));
    m_stateMap.emplace(BossAttackState::ID(), new BossAttackState(this));
    m_stateMap.emplace(BossDeadState::ID(), new BossDeadState(this));
    // 初期状態設定
    m_currentStateId = BossIdleState::ID();
    auto it = m_stateMap.find(m_currentStateId);
    if (it != m_stateMap.end())
    {
        it->second->Enter();
    }


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
    toPlayer = m_player->GetPosition() - m_pos;

	disToPlayer = toPlayer.Length();
	if (disToPlayer < 150)
	{
		isAttackFlag = true;
    }
    else
    {
        isAttackFlag = false;
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

void Boss::ManagerState()
{
	////優先順位
	//enum {
	//	PRI_NONE,
	//	PRI_IDLE,
	//	PRI_ATTACK,
	//	PRI_DEAD,
	//};

	////優先順位の高いものを入れる変数
	//int bestPri = PRI_NONE;
	////優先するステート
	//EnBossState bestState = enBossState_Idle;

	////状態を考慮するラムダ式
	//auto considerState = [&](int pri, EnBossState state)
	//	{
	//		//優先順位が一番高いものを採用する
	//		if (bestPri < pri)
	//		{
	//			bestPri = pri;
	//			bestState = state;
	//		}
	//	};

	//if (isDeadFlag == true)
	//{
	//	isDeadFlag = false;
	//	considerState(PRI_DEAD, enBossState_Dead);
	//	m_currentState = m_stateList[enBossState_Dead];
	//	bestState = enBossState_Dead;
	//}

	//if (isAttackFlag == true)
	//{
	//	considerState(PRI_ATTACK, enBossState_Attack);
	//	Attack();
	//}

	//m_currentState = m_stateList[bestState];

}

void Boss::UpdateChangeState()
{
    auto it = m_stateMap.find(m_currentStateId);
    if (it == m_stateMap.end())
    {
        // 処理できない
        return;
    }
    auto* currentState = it->second;

    uint32_t request;
    if (currentState->RequestState(request))
    {
        currentState->Exit();
        m_currentStateId = request;
        auto it = m_stateMap.find(m_currentStateId);
        if (it != m_stateMap.end())
        {
            currentState = it->second;
            currentState->Enter();
        }
    }
    currentState->Update();

	//IBossState* nextState = nullptr;

	//if (m_currentState == m_stateList[0])
	//{
	//	nextState = m_stateList[enBossState_Idle];
	//}

	//if (m_currentState == m_stateList[1])
	//{
	//	nextState = m_stateList[enBossState_Attack];
	//}

	//if (m_currentState == m_stateList[2])
	//{
	//	nextState = m_stateList[enBossState_Dead];
	//}

	////状態切り替わり処理
	//if (nextState != nullptr)
	//{
	//	m_currentState->Exit();
	//	m_currentState = nextState;
	//	m_currentState->Enter();
	//}

	//m_currentState->Update();
}

void Boss::Render(RenderContext& rc)
{
	m_bossModel.Draw(rc);
}

void Boss::DamagePunch(int damageAmount)
{
    Damage(damageAmount, enDeadReason_Punch);
}

void Boss::DamageReceiveHead(int damageAmount)
{
    Damage(damageAmount, enDeadReason_Jump);
}

void Boss::Damage(int damageAmount, int reason)
{
    hp -= damageAmount;
    HP();

    m_deadReason = (EnDeadReason) reason;
}
