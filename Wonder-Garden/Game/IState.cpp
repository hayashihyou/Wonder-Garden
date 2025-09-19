#include "stdafx.h"
#include "IState.h"
#include "Player.h"

void IdleState::Enter()
{
	m_player = FindGO<Player>("Player");
	m_player->m_playerModel.PlayAnimation(m_player->enAnimationClip_Idle);
}

void IdleState::Update()
{

}

void IdleState::Exit()
{

}

void WalkState::Enter()
{
	m_player = FindGO<Player>("Player");
	m_player->m_playerModel.PlayAnimation(m_player->enAnimationClip_Walk);
}

void WalkState::Update()
{

}

void WalkState::Exit()
{

}

void RunState::Enter()
{
	m_player = FindGO<Player>("Player");
	m_player->m_playerModel.PlayAnimation(m_player->enAnimationClip_Run);
}

void RunState::Update()
{

}

void RunState::Exit()
{

}

void JumpState::Enter()
{
	m_player = FindGO<Player>("Player");
	m_player->m_playerModel.PlayAnimation(m_player->enAnimationClip_Jump);
}

void JumpState::Update()
{

}

void JumpState::Exit()
{
}

void AttackState::Enter()
{
	m_player = FindGO<Player>("Player");
	m_player->m_playerModel.PlayAnimation(m_player->enAnimationClip_Attack);
	m_player->SetAttack(true);
}

void AttackState::Update()
{
	if (!m_player->m_playerModel.IsPlayingAnimation())
	{
		m_player->SetAttack(false);
		m_player->m_deleteFlag = true;
	}
}

void AttackState::Exit()
{
	
}
