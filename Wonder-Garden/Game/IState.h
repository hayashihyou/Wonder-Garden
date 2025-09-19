#pragma once

class Player;

class IState : public IGameObject
{
public:
	IState() {};
	virtual ~IState() {};
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;

public:
	Player* m_player = nullptr;
};

class IdleState : public IState
{
public:
	IdleState() {};
	virtual ~IdleState() {};
	void Enter()override;
	void Update()override;
	void Exit()override;
};

class WalkState : public IState
{
public:
	WalkState() {};
	virtual ~WalkState() {};
	void Enter()override;
	void Update()override;
	void Exit()override;
};

class RunState : public IState
{
public:
	RunState() {};
	virtual ~RunState() {};
	void Enter()override;
	void Update()override;
	void Exit()override;
};

class JumpState : public IState
{
public:
	JumpState() {};
	virtual ~JumpState() {};
	void Enter()override;
	void Update()override;
	void Exit()override;
};

class AttackState : public IState
{
public:
	AttackState() {};
	virtual ~AttackState() {};
	void Enter()override;
	void Update()override;
	void Exit()override;
public:
	Player* m_player;
};

