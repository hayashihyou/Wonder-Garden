#pragma once
#include "Assets/Util/CRC32.h"

#define appState(name)                                                                                                 \
public:                                                                                                                \
    static constexpr uint32_t ID()                                                                                     \
    {                                                                                                                  \
        return Hash32(#name);                                                                                          \
    }

class Enemy;

class IEnemyState : public Noncopyable
{
public:
    IEnemyState(Enemy* enemy) : m_enemy(enemy){};
    virtual ~IEnemyState(){};
    virtual void Enter() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;

    virtual bool RequestState(uint32_t& request) = 0;

protected:
    Enemy* m_enemy;
};

class EnemyIdleState : public IEnemyState
{
    appState(EnemyIdleState);

public:
    EnemyIdleState(Enemy* enemy) : IEnemyState(enemy){};
    virtual ~EnemyIdleState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;
};

class EnemyMoveState : public IEnemyState
{
    appState(EnemyMoveState);

public:
    EnemyMoveState(Enemy* enemy) : IEnemyState(enemy){};
    virtual ~EnemyMoveState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;
};

class EnemyAttackState : public IEnemyState
{
    appState(EnemyAttackState);

public:
    EnemyAttackState(Enemy* enemy) : IEnemyState(enemy){};
    virtual ~EnemyAttackState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;
};

class EnemyJumpDeadState : public IEnemyState
{
    appState(EnemyJumpDeadState);

public:
    EnemyJumpDeadState(Enemy* enemy) : IEnemyState(enemy){};
    virtual ~EnemyJumpDeadState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;
};

class EnemyAttackDeadState : public IEnemyState
{
    appState(EnemyAttackDeadState);

public:
    EnemyAttackDeadState(Enemy* enemy) : IEnemyState(enemy){};
    virtual ~EnemyAttackDeadState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;
};
