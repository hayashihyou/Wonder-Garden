#include "stdafx.h"
#include "Magic.h"
#include "Enemy/EnemyType2.h"

void Magic::CreateCollision(float size)
{
    m_magicCollision = NewGO<CollisionObject>(0);
    m_magicCollision->CreateSphere(m_enemyType2->GetPosition(), m_enemyType2->GetRotation(), size);
    m_magicCollision->SetIsEnableAutoDelete(false);
}

void Magic::Update()
{
    TimeLimit();

    m_magicCollision->Update();
}

void Magic::TimeLimit()
{
    if (m_magicCollision != nullptr)
    {
        m_lifeTime -= GameTime().GetFrameDeltaTime();
        m_moveDirection = m_enemyType2->GetToPlayer();
        Vector3 pos = m_moveDirection + m_moveSpeed;
        m_magicCollision->SetPosition(pos);

        if (m_lifeTime <= 0.0f)
        {
            m_magicCollision->SetIsEnableAutoDelete(true);
            m_magicCollision = nullptr;
            DeleteGO(this);
        }
    }
}
