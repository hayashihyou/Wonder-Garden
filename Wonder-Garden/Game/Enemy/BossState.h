#pragma once
#include "Assets/Util/CRC32.h"

#define appState(name)                                                                                                 \
public:                                                                                                                \
    static constexpr uint32_t ID()                                                                                     \
    {                                                                                                                  \
        return Hash32(#name);                                                                                          \
    }

class Boss;
class KillCounter;

class IBossState : public Noncopyable
{
public:
    IBossState(Boss* owner) : m_boss(owner){};
    virtual ~IBossState(){};
    virtual void Enter() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;
    virtual bool RequestState(uint32_t& request) = 0;

protected:
    Boss* m_boss = nullptr;
    EffectEmitter* m_effect = nullptr;
};

class BossIdleState : public IBossState
{
    appState(BossIdleState);

public:
    BossIdleState(Boss* owner) : IBossState(owner){};
    virtual ~BossIdleState(){};
    void Enter();
    void Update();
    void Exit();
    bool RequestState(uint32_t& request);
};

class BossMoveState : public IBossState
{
    appState(BossMoveState);

private:
    bool isAttack = false;

public:
    BossMoveState(Boss* owner) : IBossState(owner){};
    virtual ~BossMoveState(){};
    void Enter();
    void Update();
    void Exit();
    bool RequestState(uint32_t& request);
};

class BossAttackState : public IBossState
{
    appState(BossAttackState);

private:
    enum EnAttackPattern
    {
        enNormalAttack,
        enDoubleHitAttack,
        enJumpAttack,
        enAttackNum,
    };

    EnAttackPattern m_attackPattern = enAttackNum;

    int m_attack;
    Vector3 m_attackPos;

public:
    BossAttackState(Boss* owner) : IBossState(owner){};
    virtual ~BossAttackState(){};
    void Enter();
    void Update();
    void Exit();
    bool RequestState(uint32_t& request);
    void MakeAttackCollision();
    void CreateEffect(Vector3 position, Quaternion rotation, int num);
};

class BossDeadState : public IBossState
{
    appState(BossDeadState);

public:
    BossDeadState(Boss* owner) : IBossState(owner){};
    virtual ~BossDeadState(){};
    void Enter();
    void Update();
    void Exit();
    bool RequestState(uint32_t& request);

private:
    KillCounter* m_killCounter = nullptr;
};

class BossDownState : public IBossState
{
    appState(BossDownState);

public:
    BossDownState(Boss* owner) : IBossState(owner){};
    virtual ~BossDownState(){};
    void Enter();
    void Update();
    void Exit();
    bool RequestState(uint32_t& request);
};
