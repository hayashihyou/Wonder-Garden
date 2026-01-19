#include "stdafx.h"

#include "Cannon.h"
#include "GameCamera.h"
#include "Player/Player.h"

namespace
{
    const Vector3 CANNONMODEL_POS = {-2100.0f, 100.0f, 2780.0f};
    const Vector3 CANNON_POS_COLLIDER_offset = {100.0f,100.0f,0.0f};
    const Vector3 CANNON_ROT_COLLIDER_offset = {-45.0f, 90.0f, 0.0f};
    const float CANNON_PLAYER_POS_Y = 225.0f;
} 

bool Cannon::Start()
{
    m_cannonModel.Init("Assets/stage/cannon.tkm");

    m_player = FindGO<Player>("Player");

    scale = {3, 3, 3};


    m_cannonModel.SetPosition(position);
    m_cannonModel.SetScale(scale);
    m_cannonModel.SetRotation(rotation);
    m_cannonModel.Update();

    m_collisionPositon = position + CANNON_POS_COLLIDER_offset;
    m_collisionRotation = Quaternion::Identity;

    m_collisionRotation.SetRotationDegZ(CANNON_ROT_COLLIDER_offset.x);

    m_cannonCollision.CreateCapsule(m_collisionPositon, m_collisionRotation, 60.0f, 120.0f);

    return true;
}

void Cannon::Update()
{
    CheckNearCannon();
}

void Cannon::Render(RenderContext& rc)
{
    m_cannonModel.Draw(rc);
}

void Cannon::CheckNearCannon()
{
    if (m_cannonCollision.IsHit(*m_player->GetCharCon()))
    {
        if (changeFlag == true)
        {
            return;
        }

        m_player->SetCannonFlag(true);

        Fire();

        Quaternion rot;
        rot.AddRotationDegY(CANNON_ROT_COLLIDER_offset.y * 2);
        rot.AddRotationDegX(CANNON_ROT_COLLIDER_offset.x * -2);

        Vector3 pos = m_collisionPositon;
        pos.y = CANNON_PLAYER_POS_Y;
         
        m_player->SetPosition(pos);
        m_player->SetRotation(rot);
        m_player->Update();

    }
}

void Cannon::Fire()
{

    if (g_pad[0]->IsTrigger(enButtonA))
    {
        changeFlag = true;

        m_player->SetFireFlag(true);

        // ここの方向は大砲の向き
        Vector3 fireDirection = Vector3::Front;
        fireDirection.x = 15.0f;
        fireDirection.y = 20.0f;
        fireDirection.z = 1.5f;
        fireDirection.Normalize();

        // 大砲の威力
        fireDirection *= 65.0f; // ここの数値を定数にして調整して

        m_player->SetAddForce(fireDirection);

        changeFlag = false;
    }
}
