#include "stdafx.h"
#include "PlayerState.h"
#include "Player.h"

void PlayerIdleState::Enter()
{
	m_player = FindGO<Player>("Player");
	m_player->m_playerModel.PlayAnimation(m_player->enAnimationClip_Idle);
}

void PlayerIdleState::Update()
{

}

void PlayerIdleState::Exit()
{

}

void PlayerWalkState::Enter()
{
	m_player = FindGO<Player>("Player");
	m_player->m_playerModel.PlayAnimation(m_player->enAnimationClip_Walk);
}

void PlayerWalkState::Update()
{

}

void PlayerWalkState::Exit()
{

}

void PlayerRunState::Enter()
{
	m_player = FindGO<Player>("Player");
	m_player->m_playerModel.PlayAnimation(m_player->enAnimationClip_Run);
}

void PlayerRunState::Update()
{

}

void PlayerRunState::Exit()
{

}

void PlayerJumpState::Enter()
{
	m_player = FindGO<Player>("Player");
	m_player->m_playerModel.PlayAnimation(m_player->enAnimationClip_Jump);
}

void PlayerJumpState::Update()
{

}

void PlayerJumpState::Exit()
{
}

void PlayerAttackState::Enter()
{
	m_player = FindGO<Player>("Player");
	m_player->m_playerModel.PlayAnimation(m_player->enAnimationClip_Attack);
	m_player->SetAttack(true);
}

void PlayerAttackState::Update()
{
	if (!m_player->m_playerModel.IsPlayingAnimation())
	{
		m_player->SetAttack(false);
	}
}

void PlayerAttackState::Exit()
{
	
}
