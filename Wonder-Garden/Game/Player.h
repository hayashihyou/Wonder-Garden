#pragma once
#include "CharacterBase.h"

class Player :  public CharacterBase
{
public:
	Player() {};

	Vector3 pos = { 0,0,0 };
private:
	~Player() {};
	bool Start();
	void Rotation();
	void Update();
	void Render(RenderContext& rc);
	void ManagerState();
	void PlayAnimation();
	void HP()override;
	void Attack()override;
	void Move()override;

private:
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
	ModelRender m_playerModel;
	Quaternion m_rot;

	Vector3 moveSpeed;

	int playerState = enPlayerState_Idle;
};

