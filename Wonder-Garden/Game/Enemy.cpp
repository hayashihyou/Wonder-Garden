#include "stdafx.h"
#include "Enemy.h"

bool Enemy::Start()
{
    m_enemyModel.Init("Assets/modelData/enemy/slime/slime.tkm");

	pos = { 200,0,0 };
	m_enemyModel.SetPosition(pos);

	m_enemyModel.Update();
    return true;
}

void Enemy::Update()
{
	Move();

	Rotation();

}

void Enemy::HP()
{
	hp = 5;
}

void Enemy::Attack()
{
	atk = 1;
}

void Enemy::Move()
{
}

void Enemy::Rotation()
{
	
}

void Enemy::Render(RenderContext& rc)
{
	m_enemyModel.Draw(rc);
}
