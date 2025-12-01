#include "stdafx.h"
#include "Star.h"
#include "StarCounter.h"
#include "Player/Player.h"

bool Star::Start()
{
	m_star.Init("Assets/modelData/star.tkm");

	m_pos = { 2300,300,2730 };

	m_star.SetPosition(m_pos);
	m_star.Update();
	return true;
}

void Star::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("Player");
	}

	GetFlag();

	Rotation();
}

void Star::GetFlag()
{
    toPlayer = m_player->GetPosition() - m_pos;
	disToPlayer = toPlayer.Length();
	if (disToPlayer <= 120)
	{
		m_starCounter = FindGO<StarCounter>("StarCounter");
		m_starCounter->AddStarCount();
		DeleteGO(this);
	}

	m_star.Update();
}

void Star::Rotation()
{
	m_rot.AddRotationDegY(3.0f);
	m_star.SetRotation(m_rot);
}

void Star::Render(RenderContext& rc)
{
	m_star.Draw(rc);
}
