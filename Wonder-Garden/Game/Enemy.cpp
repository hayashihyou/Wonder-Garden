#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "AttackCollision.h"

namespace
{
	const Vector3 COLPOS_Y = Vector3{ 0, 20, 0 };
	const Vector3 COLJUMPPOS_Y = Vector3{ 0,30,0 };
}

bool Enemy::Start()
{
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/enemy/slime/slime_Idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Attack].Load("Assets/animData/enemy/slime/slime_Attack.tka");
	m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);
	m_animationClips[enAnimationClip_JumpDie].Load("Assets/animData/enemy/slime/slime_Die.tka");
	m_animationClips[enAnimationClip_JumpDie].SetLoopFlag(false);
	m_animationClips[enAnimationClip_AttackDie].Load("Assets/animData/enemy/slime/slime_Die2.tka");
	m_animationClips[enAnimationClip_AttackDie].SetLoopFlag(false);

	m_enemyModel.Init("Assets/modelData/enemy/slime/slime.tkm", m_animationClips, enAnimationClip_Num);
	m_pos = { 200,0,0 };
	m_colPos = m_pos + COLPOS_Y;

	m_colJumpPos = m_pos + COLJUMPPOS_Y;

	m_enemyModel.SetPosition(m_pos);
	m_enemyModel.SetRotation(m_rot);
	m_enemyModel.Update();

	enemyCollisionObject.CreateSphere(m_colPos, m_rot, 40.0f);
	enemyJumpCollision.CreateSphere(m_colJumpPos, m_rot, 25.0f);
	return true;
}

void Enemy::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("Player");
	}


	m_attackCollision = FindGO<AttackCollision>("AttackCollision");


	Attack();

	Move();

	Rotation();

	JumpHit();

	PunchHit();

	//PlayAnimation();

}

void Enemy::HP()
{
	if (hp <= 0)
	{
		hp = 0;
		DeleteGO(this);
	}
}

void Enemy::Attack()
{
	atk = 1;
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		m_enemyState = enEnemyState_Attack;
		m_enemyModel.PlayAnimation(enAnimationClip_Attack);
	}

}

void Enemy::Move()
{
	toPlayer = m_player->playerPos - m_pos;

	disToPlayer = toPlayer.Length();

	if (disToPlayer < 200)
	{
		toPlayerDir = toPlayer;
		toPlayerDir.Normalize();

		m_pos += toPlayerDir * 1.0f;

		m_colPos = m_pos + COLPOS_Y;
		m_colJumpPos = m_pos + COLJUMPPOS_Y;
		enemyCollisionObject.SetPosition(m_colPos);
		enemyJumpCollision.SetPosition(m_colJumpPos);
		m_enemyModel.SetPosition(m_pos);
		m_enemyModel.Update();
	}

	if (m_player->enAnimationClip_Jump)
	{
		m_pos.y = 0;
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
		if (enemyCollisionObject.IsHit(m_attackCollision->m_punchCollision))
		{
			hp -= 2;
			HP();
		}
	}
}

void Enemy::Rotation()
{

}

void Enemy::ManagerState()
{

}

void Enemy::PlayAnimation()
{
	m_enemyModel.PlayAnimation(enAnimationClip_Idle);
	m_enemyModel.Update();
}

void Enemy::Render(RenderContext& rc)
{
	m_enemyModel.Draw(rc);
}
