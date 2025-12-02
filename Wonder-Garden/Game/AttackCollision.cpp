#include "stdafx.h"

#include "AttackCollision.h"
#include "Player/Player.h"

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

void AttackCollision::InitTransform(Vector3 position, Vector3 forward, Transform& parentTransform)
{
    parentTransform.SetParent(&m_transform);
    Vector3 toTargetPos = {0, 0, 0};
    toTargetPos.Set(position);
    m_transform.m_localRotation.Apply(forward);
    float rot = atan2(forward.x, forward.z);
    rot -= 3.141592 / 2;
    Quaternion q;
    q.SetRotationY(rot);
    q.Apply(toTargetPos);
    toTargetPos = m_transform.m_localPosition = toTargetPos + parentTransform.m_localPosition;
    m_transform.UpdateTransform();
}

void AttackCollision::TimeLimit()
{
    if (m_punchCollision != nullptr)
    {
        deleteTimer -= g_gameTime->GetFrameDeltaTime();
    }
}
