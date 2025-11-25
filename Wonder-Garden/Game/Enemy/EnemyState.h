#pragma once
#include "Assets/Util/CRC32.h"

#define appState(name)                                                                                                 \
public:                                                                                                                \
    static constexpr uint32_t ID()                                                                                     \
    {                                                                                                                  \
        return Hash32(#name);                                                                                          \
    }

class Enemy;
class Player;

class IEnemyState : public IGameObject
{
protected:
    Enemy* m_enemy;
    Player* m_player;

public:
    IEnemyState(Enemy* enemy) : m_enemy(enemy){};
    virtual ~IEnemyState(){};
    virtual void Enter() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;

    void SetOwner(Enemy* owner) { m_enemy = owner; }

    virtual bool RequestState(uint32_t& request) = 0;

    IEnemyState() = default;
};

class StatePatternBase
{
    using StateMap = std::map<uint32_t, IEnemyState*>;

protected:
    StateMap m_stateMap;
    IEnemyState* m_currentState;

public:
    StatePatternBase() : m_currentState(nullptr) { m_stateMap.clear(); }

    virtual ~StatePatternBase()
    {
        for (auto it : m_stateMap)
        {
            delete it.second;
            it.second = nullptr;
        }
        m_stateMap.clear();
    }

    virtual void Update() = 0;

protected:
    inline IEnemyState* FindState(uint32_t id)
    {
        const auto& it = m_stateMap.find(id);
        if (it == m_stateMap.end())
        {
            // ここに来ることはないはず
            return nullptr;
        }
        return it->second;
    }

public:
    template <typename T> inline void RegisterState(Enemy* e)
    {
        // TのID()をキーにして、T型のインスタンスを生成し、m_stateMapに登録する
        m_stateMap.emplace(T::ID(), new T(e));
    }

    template <typename T> inline void InitializeState()
    {
        // TのID()をキーにして、stateMap_からステートを探し、m_currentStateに設定する
        m_currentState = FindState(T::ID());
        m_currentState->Enter();
    }
};

class EnemyStatePattern : public StatePatternBase
{
public:
    EnemyStatePattern();
    virtual ~EnemyStatePattern();

    virtual void Update() override;
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
