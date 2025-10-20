#pragma once

class EnemyType2;

class IEnemyType2State : public IGameObject
{
public:
	IEnemyType2State() {};
	virtual ~IEnemyType2State() {};
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;

    void SetOwner(EnemyType2* owner) { m_enemyType2 = owner; };

protected:
	EnemyType2* m_enemyType2 = nullptr;
};

class EnemyType2IdleState : public IEnemyType2State
{
public:
	EnemyType2IdleState() {};
	virtual ~EnemyType2IdleState() {};
	void Enter();
	void Update();
	void Exit();
};

class EnemyType2AttackState : public IEnemyType2State
{
public:
	EnemyType2AttackState() {};
	virtual ~EnemyType2AttackState() {};
	void Enter();
	void Update();
	void Exit();
};

class EnemyType2AttackDeadState : public IEnemyType2State
{
public:
	EnemyType2AttackDeadState() {};
	virtual ~EnemyType2AttackDeadState() {};
	void Enter();
	void Update();
	void Exit();
};

class EnemyType2JumpDeadState : public IEnemyType2State
{
public:
	EnemyType2JumpDeadState() {};
	virtual ~EnemyType2JumpDeadState() {};
	void Enter();
	void Update();
	void Exit();
};

