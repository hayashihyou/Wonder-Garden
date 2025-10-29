#include "stdafx.h"

#include "AttackCollision.h"
#include "Player.h"

AttackCollision::~AttackCollision() {}

void AttackCollision::Update()
{

    TimeLimit();

    if (deleteTimer <= 0)
    {
        DeleteGO(m_punchCollision);
        DeleteGO(this);
    }
}

void AttackCollision::CreateCollision()
{
    m_punchCollision = NewGO<CollisionObject>(0);
    m_punchCollision->CreateSphere(m_transform.m_localPosition, m_transform.m_localRotation, 30.0f);
    m_punchCollision->SetIsEnableAutoDelete(false);
}

void AttackCollision::InitTransform(const Vector3& position, Vector3 setposition, Transform& transform)
{
    transform.SetParent(&m_transform);
    Vector3 toTargetPos;
    toTargetPos.Set(setposition);
    transform.m_localRotation.Apply(toTargetPos);
    m_transform.m_localPosition = toTargetPos + transform.m_localPosition;
    m_transform.UpdateTransform();
}

void AttackCollision::TimeLimit()
{
    if (m_punchCollision != nullptr)
    {
        deleteTimer -= g_gameTime->GetFrameDeltaTime();
    }
}
