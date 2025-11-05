#include "stdafx.h"
#include "Cannon.h"
#include "Player/Player.h"

namespace
{
    const Vector3 CANNON_POS = {-2030, 170, 2775};
    const Quaternion CANNON_ROT = {60, 90, -10, 1};
}

bool Cannon::Start()
{
    position = CANNON_POS;
    rotation = CANNON_ROT;
    m_cannonCollision.SetPosition(position);
    m_cannonCollision.SetRotation(rotation);
    m_cannonCollision.Update();

    m_cannonCollision.CreateCapsule(position, rotation, 60.0f, 120.0f);
    return true;
}

void Cannon::Update()
{

}

void Cannon::CheckNearCannon()
{

}
