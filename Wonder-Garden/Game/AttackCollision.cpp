#include "stdafx.h"
#include "AttackCollision.h"
#include "Player.h"

void AttackCollision::Update()
{
	if (m_punchCollision == nullptr)
	{
		DeleteGO(this);
	}
}

void AttackCollision::CreateCollision(float size, bool deleteCheck, float deleteTime)
{
	m_punchCollision = NewGO<CollisionObject>(0);
	m_punchCollision->CreateSphere(m_transform.m_localPosition, m_transform.m_localRotation, size);
	m_punchCollision->SetIsEnableAutoDelete(deleteCheck);
	if (deleteTime > 0)
	{
		m_punchCollision->SetTimeLimit(deleteTime);
	}
}

void AttackCollision::InitTransform(const Vector3& position, Transform& transform)
{
	transform.SetParent(&m_transform);
	Vector3 toPlayerPos;
	toPlayerPos.Set(0, 30, 50);
	transform.m_localRotation.Apply(toPlayerPos);
	m_transform.m_localPosition = toPlayerPos + transform.m_localPosition;
	m_transform.UpdateTransform();
}
