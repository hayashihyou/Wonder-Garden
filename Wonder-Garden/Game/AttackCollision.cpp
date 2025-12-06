#include "stdafx.h"

#include "AttackCollision.h"
#include "Player/Player.h"

AttackCollision::~AttackCollision()
{
    DeleteGO(m_punchCollision);
}

void AttackCollision::Update()
{

}

void AttackCollision::CreateCollision(float size)
{
    m_punchCollision = NewGO<CollisionObject>(0);
    m_punchCollision->CreateSphere(m_transform.m_localPosition, m_transform.m_localRotation, size);
    m_punchCollision->SetIsEnableAutoDelete(false);
}

void AttackCollision::InitTransform(Vector3 position,Vector3 forward, Transform& parentTransform)
{
    parentTransform.SetParent(&m_transform);
    Vector3 toTargetPos = {0, 0, 0};
    toTargetPos.Set(position);
    parentTransform.m_localRotation.Apply(toTargetPos);
    m_transform.m_localPosition = toTargetPos + parentTransform.m_localPosition;
    m_transform.m_localPosition += forward * 0.2f;
    m_transform.UpdateTransform();
}
