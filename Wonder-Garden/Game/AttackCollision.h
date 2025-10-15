#pragma once
/**
 *TransformとIGameObjectを持った当たり判定のオブジェクト
 */

class Player;
class AttackCollision : public IGameObject
{
public:
	AttackCollision() {};
	~AttackCollision();

	void Update();
	void CreateCollision();
	void InitTransform(const Vector3& position, Transform& transform);
	void TimeLimit();

public:
	CollisionObject* m_punchCollision = nullptr;


private:
	Transform m_transform;

private:
	float deleteTimer = 1.0f;
};

