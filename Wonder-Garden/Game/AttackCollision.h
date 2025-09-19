#pragma once
/**
 *TransformとIGameObjectを持った当たり判定のオブジェクト
 */

class AttackCollision : public IGameObject
{
public:
	CollisionObject m_collisionObject;
	Transform m_transform;
};

