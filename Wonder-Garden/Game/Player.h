#pragma once
#include "CharacterBase.h"

class IState;
class Player : public CharacterBase
{
public:
	Player() {};
	void RegisterState();

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

public:
	ModelRender m_playerModel;

	Vector3 pos = { 0,0,0 };
	Vector3 moveSpeed;
	int hp = 10;
	void SetAttack(bool attackFlag);

private:
	~Player() {};
	bool Start();
	void Rotation();
	void Update();
	void Render(RenderContext& rc);
	void ManagerState();
	void UpdateChangeState();

	void HP()override;
	void Attack()override;
	void Move()override;

private:

	/// <summary>
	/// プレイヤーの状態
	/// </summary>
	enum AnimationState
	{
		enPlayerState_Idle,
		enPlayerState_Walk,
		enPlayerState_Run,
		enPlayerState_Jump,
		enPlayerState_Attack,
		enPlayerState_Num,
	};

	AnimationClip m_animationClips[enAnimationClip_Num];
	CharacterController m_characterController;
	CharacterBase* m_characterBase;
	Quaternion m_rot;

	int playerState = enPlayerState_Idle;
	int m_atk = 1;

private:
	IState* m_currentState = nullptr;
	IState* m_stateList[enPlayerState_Num];
	bool m_attackFlag = false;	
	bool m_isStopMove = false;
};