#include "stdafx.h"

#include "Cannon.h"
#include "GameCamera.h"
#include "Player/Player.h"

namespace
{
    const Vector3 CANNONMODEL_POS = {-2100.0f, 100.0f, 2780.0f};
    const Vector3 CANNON_POS = {-2000.0f, 170.0f, 2800.0f};
    const Quaternion CANNON_ROT = {60.0f, 90.0f, -10.0f, 1.0f};
} 

bool Cannon::Start()
{
    m_cannonModel.Init("Assets/stage/cannon.tkm");

    m_player = FindGO<Player>("Player");
    m_gameCamera = FindGO<GameCamera>("GameCamera");

    position = CANNON_POS;
    modelPos = CANNONMODEL_POS;
    rotation = CANNON_ROT;
    scale = {3, 3, 3};

    m_cannonModel.SetPosition(modelPos);
    m_cannonModel.SetScale(scale);
    m_cannonCollision.SetPosition(position);
    m_cannonCollision.SetRotation(rotation);

    m_cannonModel.Update();
    m_cannonCollision.Update();

    m_cannonCollision.CreateCapsule(position, rotation, 60.0f, 120.0f);
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

        rotation.Normalize();
        m_player->GetModel()->SetPosition(position);
        m_player->GetModel()->SetRotation(rotation);
        m_player->GetCharCon()->SetPosition(position);
        m_player->GetCharCon()->GetPosition();
        m_player->GetModel()->Update();
        m_gameCamera->Update();
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
        fireDirection.x = 20.0f;
        fireDirection.y = 15.0f;
        fireDirection.Normalize();

        // 大砲の威力
        fireDirection *= 65.0f; // ここの数値を定数にして調整して

        m_player->SetAddForce(fireDirection);
    }
}
