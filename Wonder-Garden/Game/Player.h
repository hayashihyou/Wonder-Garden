#pragma once
#include "CharacterBase.h"


class IPlayerState;
class Enemy;
class AttackCollision;
class Player : public CharacterBase
{
public:
	Player() {};
	void SetAttack(bool attackFlag);

public:
	/// <summary>
	/// アニメーションの種類
	/// </summary>
	enum EnAnimationClip
	{
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_Attack,
		enAnimationClip_Num,
	};

	enum EnPlayerState
	{
		enPlayerState_Idle,
		enPlayerState_Walk,
		enPlayerState_Run,
		enPlayerState_Jump,
		enPlayerState_Attack,
		enPlayerState_Num,
	};

public:
	ModelRender m_playerModel;
	CharacterController m_characterController;

public:
	Vector3 moveSpeed;
	Vector3 playerPos;
	int hp = 10;
	bool m_deleteFlag = false;

private:
	~Player() {};
	bool Start();
	void Rotation();
	void Update();
	void Render(RenderContext& rc);
	void MakeAttackCollision();
	void ManagerState();
	void UpdateChangeState();

	void HP()override;
	void Attack()override;
	void Move()override;

private:

	AnimationClip m_animationClips[enAnimationClip_Num];
	CharacterBase* m_characterBase;
	IPlayerState* m_currentState = nullptr;
	IPlayerState* m_stateList[enPlayerState_Num];
	Enemy* m_enemy;
	Vector3 collisionRot;

private:
	int playerState = enPlayerState_Idle;
	int m_atk = 1;

	bool m_attackFlag = false;	
	bool m_isStopMove = false;
};
