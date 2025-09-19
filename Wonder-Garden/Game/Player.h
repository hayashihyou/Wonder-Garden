#pragma once
#include "CharacterBase.h"


class IState;
class Enemy;
class AttackCollision;
class Player : public CharacterBase
{
public:
	Player() {};

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

	enum AnimationState
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
	AttackCollision* punchCollision;

	/*Vector3 pos = { 0,0,0 };*/
	Vector3 moveSpeed;
	Vector3 playerPos;
	int hp = 10;
	void SetAttack(bool attackFlag);
	bool m_deleteFlag = false;

private:
	~Player() {};
	bool Start();
	void Rotation();
	void Update();
	void Render(RenderContext& rc);
	void MakeAttackCollision();
	void MakeJumpCollision();
	void ManagerState();
	void UpdateChangeState();

	void HP()override;
	void Attack()override;
	void Move()override;

private:

	AnimationClip m_animationClips[enAnimationClip_Num];
	CharacterController m_characterController;
	CharacterBase* m_characterBase;
	/*Quaternion m_rot;*/
	IState* m_currentState = nullptr;
	IState* m_stateList[enPlayerState_Num];
	Enemy* m_enemy;
	Vector3 collisionRot;
	//Vector3 toPlayerPos;

private:
	int playerState = enPlayerState_Idle;
	int m_atk = 1;
	bool m_attackFlag = false;	
	bool m_isStopMove = false;
};