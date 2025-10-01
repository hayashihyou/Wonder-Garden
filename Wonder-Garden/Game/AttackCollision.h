#pragma once
/**
 *TransformとIGameObjectを持った当たり判定のオブジェクト
 */

class Player;
class AttackCollision : public IGameObject
{
public:
	AttackCollision() {};
	~AttackCollision() {};

	void Update();
	void CreateCollision(float size, bool kesimasuka = true, float deleteTime = 0);
	void InitTransform(const Vector3& position, Transform& transform);

public:
	CollisionObject* m_punchCollision;


private:
	Transform m_transform;
};

