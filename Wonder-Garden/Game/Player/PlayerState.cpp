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

void PlayerDamageState::Enter()
{
    m_player = FindGO<Player>("Player");
    m_player->m_playerModel.PlayAnimation(m_player->enAnimationClip_Damage);
    m_player->SetDamage(true);
}

void PlayerDamageState::Update()
{
    if (!m_player->m_playerModel.IsPlayingAnimation())
    {
        m_player->SetDamage(false);
    }
}

void PlayerDamageState::Exit()
{

}

void PlayerDeadState::Enter()
{
    m_player = FindGO<Player>("Player");
    m_player->m_playerModel.PlayAnimation(m_player->enAnimationClip_Dead);
    m_player->SetDead(true);
}

void PlayerDeadState::Update()
{
    if (!m_player->m_playerModel.IsPlayingAnimation())
    {
        m_player->SetDead(false);
        m_player->m_gameoverFlag = true;
    }
}

void PlayerDeadState::Exit()
{

}
