#pragma once

class Enemy;

class IEnemyState : public IGameObject
{
public:
	IEnemyState() {};
	virtual ~IEnemyState() {};
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;

protected:
	Enemy* m_enemy = nullptr;
};

class EnemyIdleState : public IEnemyState
{
public:
	EnemyIdleState() {};
	virtual ~EnemyIdleState() {};
	void Enter();
	void Update();
	void Exit();
};

class EnemyAttackState : public IEnemyState
{
public:
	EnemyAttackState() {};
	virtual ~EnemyAttackState() {};
	void Enter();
	void Update();
	void Exit();
};

class EnemyJumpDeadState : public IEnemyState
{
public:
	EnemyJumpDeadState() {};
	virtual ~EnemyJumpDeadState() {};
	void Enter();
	void Update();
	void Exit();
};

class EnemyAttackDeadState : public IEnemyState
{
public:
	EnemyAttackDeadState() {};
	virtual ~EnemyAttackDeadState() {};
	void Enter();
	void Update();
	void Exit();
};

