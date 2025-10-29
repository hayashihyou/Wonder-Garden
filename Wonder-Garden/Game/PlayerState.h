#pragma once

class Player;

class IPlayerState : public IGameObject
{
public:
	IPlayerState() {};
	virtual ~IPlayerState() {};
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;

protected:
	Player* m_player = nullptr;
};

class PlayerIdleState : public IPlayerState
{
public:
	PlayerIdleState() {};
	virtual ~PlayerIdleState() {};
	void Enter()override;
	void Update()override;
	void Exit()override;
};

class PlayerWalkState : public IPlayerState
{
public:
	PlayerWalkState() {};
	virtual ~PlayerWalkState() {};
	void Enter()override;
	void Update()override;
	void Exit()override;
};

class PlayerRunState : public IPlayerState
{
public:
	PlayerRunState() {};
	virtual ~PlayerRunState() {};
	void Enter()override;
	void Update()override;
	void Exit()override;
};

class PlayerJumpState : public IPlayerState
{
public:
	PlayerJumpState() {};
	virtual ~PlayerJumpState() {};
	void Enter()override;
	void Update()override;
	void Exit()override;
};

class PlayerAttackState: public IPlayerState
{
public:
	PlayerAttackState() {};
	virtual ~PlayerAttackState() {};
	void Enter()override;
	void Update()override;
	void Exit()override;
};

class PlayerDamageState: public IPlayerState
{
public:
	PlayerDamageState() {};
	virtual ~PlayerDamageState() {};
	void Enter()override;
	void Update()override;
	void Exit()override;
};

class PlayerDeadState: public IPlayerState
{
public:
	PlayerDeadState() {};
	virtual ~PlayerDeadState() {};
	void Enter()override;
	void Update()override;
	void Exit()override;
};

