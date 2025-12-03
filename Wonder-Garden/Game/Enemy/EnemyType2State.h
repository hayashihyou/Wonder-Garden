#pragma once
#include "Assets/Util/CRC32.h"

#define appState(name)                                                                                                 \
public:                                                                                                                \
    static constexpr uint32_t ID()                                                                                     \
    {                                                                                                                  \
        return Hash32(#name);                                                                                          \
    }

class EnemyType2;

class IEnemyType2State : public Noncopyable
{
public:
    IEnemyType2State(EnemyType2* owner) : m_enemyType2(owner){};
    virtual ~IEnemyType2State(){};
    virtual void Enter() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;
    virtual bool RequestState(uint32_t& request) = 0;

protected:
    EnemyType2* m_enemyType2 = nullptr;
};

class EnemyType2IdleState : public IEnemyType2State
{
    appState(EnemyType2IdleState);

public:
    EnemyType2IdleState(EnemyType2* owner) : IEnemyType2State(owner){};
    virtual ~EnemyType2IdleState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;
    bool RequestState(uint32_t& request) override;
};

class EnemyType2AttackState : public IEnemyType2State
{
    appState(EnemyType2AttackState);

public:
    EnemyType2AttackState(EnemyType2* owner) : IEnemyType2State(owner){};
    virtual ~EnemyType2AttackState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;
    bool RequestState(uint32_t& request) override;

private:
        void MakeAttackCollision();
};

class EnemyType2AttackDeadState : public IEnemyType2State
{
    appState(EnemyType2AttackDeadState);

public:
    EnemyType2AttackDeadState(EnemyType2* owner) : IEnemyType2State(owner){};
    virtual ~EnemyType2AttackDeadState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;
    bool RequestState(uint32_t& request) override;
};

class EnemyType2JumpDeadState : public IEnemyType2State
{
    appState(EnemyType2JumpDeadState);

public:
    EnemyType2JumpDeadState(EnemyType2* owner) : IEnemyType2State(owner){};
    virtual ~EnemyType2JumpDeadState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;
    bool RequestState(uint32_t& request) override;
};
