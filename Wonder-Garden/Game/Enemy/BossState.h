#pragma once

class Boss;

class IBossState : public IGameObject
{
public:
	IBossState() {};
	virtual ~IBossState() {};
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;

protected:
	Boss* m_boss = nullptr;
};

class BossIdleState : public IBossState
{
public:
	BossIdleState() {};
	virtual ~BossIdleState() {};
	void Enter();
	void Update();
	void Exit();
};

class BossAttackState : public IBossState
{
public:
	BossAttackState() {};
	virtual ~BossAttackState() {};
	void Enter();
	void Update();
	void Exit();
};

class BossDeadState : public IBossState
{
public:
	BossDeadState() {};
	virtual ~BossDeadState() {};
	void Enter();
	void Update();
	void Exit();
};

