#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

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
	m_enemyModel.SetPosition(m_pos);

	m_enemyModel.SetRotation(m_rot);


	m_enemyCollision.CreateFromModel(m_enemyModel.GetModel(), m_enemyModel.GetModel().GetWorldMatrix());

	m_enemyModel.Update();
	return true;
}

void Enemy::Update()
{

	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("Player");
	}

	Attack();

	Move();

	Rotation();

	//PlayAnimation();

}

void Enemy::HP()
{
	hp = 1;
	if (hp <= 0)
	{
		hp = 0;
		m_enemyState = enEnemyState_Die;
		m_enemyModel.PlayAnimation(enAnimationClip_AttackDie);
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

		m_enemyModel.SetPosition(m_pos);
		m_enemyModel.Update();
	}

	if (m_player->enPlayerState_Jump)
	{
		m_pos.y= 0;
	}
}

void Enemy::Rotation()
{
	m_rot.SetRotationY(Math::PI);
	m_enemyModel.SetRotation(m_rot);
	m_enemyModel.Update();
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
