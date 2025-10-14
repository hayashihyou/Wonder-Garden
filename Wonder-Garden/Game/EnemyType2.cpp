#include "stdafx.h"
#include "EnemyType2.h"
#include "Player.h"
#include "AttackCollision.h"

namespace
{
	const Vector3 POS_Y = { 0,35,0 };
	const Vector3 JUMPPOS = { 0,45,0 };
}

bool EnemyType2::Start()
{
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/enemy/stone/StoneMonstorIdle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Attack].Load("Assets/animData/enemy/stone/StoneMonstorAttack.tka");
	m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);
	m_animationClips[enAnimationClip_AttackDead].Load("Assets/animData/enemy/stone/StoneMonstorDamage.tka");
	m_animationClips[enAnimationClip_AttackDead].SetLoopFlag(false);
	m_animationClips[enAnimationClip_JumpDead].Load("Assets/animData/enemy/stone/StoneMonstorDeath.tka");
	m_animationClips[enAnimationClip_AttackDead].SetLoopFlag(false);

	m_enemyType2Model.Init("Assets/modelData/enemy/stone/StoneMonster.tkm");
	m_pos = { -200,0,0 };
	m_colPos = m_pos + POS_Y;

	m_colJumpPos = m_pos + JUMPPOS;

	m_enemyType2Model.SetPosition(m_pos);
	m_enemyType2Model.SetRotation(m_rot);
	m_enemyType2Model.Update();

	enemyType2Collision.CreateSphere(m_colPos, m_rot, 25.0f);
	enemyType2JumpCollision.CreateSphere(m_colJumpPos, m_rot, 20.0f);
	return true;
}

void EnemyType2::Update()
{
	PlayAnimation();
}

void EnemyType2::HP()
{
	if (hp <= 0)
	{
		hp = 0;
		isDeadFlag = true;
	}
}

void EnemyType2::Attack()
{
	toPlayer = m_player->playerPos - m_pos;

	disToPlayer = toPlayer.Length();
	if (disToPlayer < 200)
	{
		isAttackFlag = true;
	}

}

void EnemyType2::Move()
{

}

void EnemyType2::HitPunch()
{
	if (m_attackCollision != nullptr)
	{
		if (m_attackCollision->m_punchCollision != nullptr)
		{
			if (enemyType2Collision.IsHit(m_attackCollision->m_punchCollision))
			{
				hp -= 2;
				HP();
			}
		}
	}
}

void EnemyType2::HitJump()
{
	if (enemyType2JumpCollision.IsHit(m_player->m_characterController))
	{
		hp -= 2;
		HP();
	}
}

void EnemyType2::PlayAnimation()
{
	m_enemyType2Model.PlayAnimation(enAnimationClip_Idle);
	m_enemyType2Model.Update();
}

void EnemyType2::Render(RenderContext& rc)
{
	m_enemyType2Model.Draw(rc);
}
