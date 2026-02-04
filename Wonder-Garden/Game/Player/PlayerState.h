#pragma once
#include "Assets/Util/CRC32.h"

#define appState(name)                                                                                                 \
public:                                                                                                                \
    static constexpr uint32_t ID()                                                                                     \
    {                                                                                                                  \
        return Hash32(#name);                                                                                          \
    }

class Player;
class GameCamera;

class IPlayerState : public IGameObject
{
protected:
    Player* m_player;
    GameCamera* m_gameCamera;
    EffectEmitter* m_effect;

public:
    IPlayerState(Player* player) : m_player(player){};
    virtual ~IPlayerState(){};
    virtual void Enter() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;

    virtual bool RequestState(uint32_t& request) = 0;

    IPlayerState() = default;
};

class StatePatternBase
{
    using StateMap = std::map<uint32_t, IPlayerState*>;

protected:
    StateMap m_stateMap;
    IPlayerState* m_currentState;

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
    inline IPlayerState* FindState(uint32_t id)
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
    template <typename T> inline void RegisterState(Player* p)
    {
        // TのID()をキーにして、T型のインスタンスを生成し、m_stateMapに登録する
        m_stateMap.emplace(T::ID(),new T(p));
    }

    template <typename T> inline void InitializeState()
    {
        // TのID()をキーにして、stateMap_からステートを探し、m_currentStateに設定する
        m_currentState = FindState(T::ID());
        m_currentState->Enter();
    }
};

class PlayerStatePattern : public StatePatternBase
{
public:
    PlayerStatePattern();
    virtual ~PlayerStatePattern();

    virtual void Update() override;
};

class PlayerIdleState : public IPlayerState
{
    appState(PlayerIdleState);

public:
    PlayerIdleState(Player* player) : IPlayerState(player){};
    virtual ~PlayerIdleState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;
};

class PlayerWalkState : public IPlayerState
{
    appState(PlayerWalkState);

public:
    PlayerWalkState(Player* player) : IPlayerState(player){};
    virtual ~PlayerWalkState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;
};

class PlayerRunState : public IPlayerState
{
    appState(PlayerRunState);

public:
    PlayerRunState(Player* player) : IPlayerState(player){};
    virtual ~PlayerRunState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;
};

class PlayerJumpState : public IPlayerState
{
    appState(PlayerJumpState);

private:
    float m_jump = 0.0f;

public:
    PlayerJumpState(Player* player) : IPlayerState(player){};
    virtual ~PlayerJumpState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;
};

class PlayerAttackState : public IPlayerState
{
    appState(PlayerAttackState);

public:
    PlayerAttackState(Player* player) : IPlayerState(player){};
    virtual ~PlayerAttackState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;

private:
    /// <summary>
    /// 攻撃判定の生成
    /// </summary>
    void MakeAttackCollision();


private:
    int m_effectID = 0;


};

class PlayerDamageState : public IPlayerState
{
    appState(PlayerDamageState);

public:
    PlayerDamageState(Player* owner) : IPlayerState(owner){};
    virtual ~PlayerDamageState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;
};

class PlayerDeadState : public IPlayerState
{
    appState(PlayerDeadState);

public:
    PlayerDeadState(Player* player) : IPlayerState(player){};
    virtual ~PlayerDeadState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;
};

class PlayerPipeState : public IPlayerState
{
    appState(PlayerPipeState);

public:
    PlayerPipeState(Player* player) : IPlayerState(player){};
    virtual ~PlayerPipeState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;
};

class PlayerCannonState : public IPlayerState
{
    appState(PlayerCannonState);

public:
    PlayerCannonState(Player* player) : IPlayerState(player){};
    virtual ~PlayerCannonState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;
};

class PlayerFireState : public IPlayerState
{
    appState(PlayerFireState);

public:
    PlayerFireState(Player* player) : IPlayerState(player){};
    virtual ~PlayerFireState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;
    void CreateEffect(Vector3 position, Quaternion rotation, int num);

    virtual bool RequestState(uint32_t& request) override;


private:
    int m_effectID = 0;

};

class PlayerBattleState : public IPlayerState
{
    appState(PlayerBattleState);
    public:
        PlayerBattleState(Player* player) : IPlayerState(player){};
        virtual ~PlayerBattleState(){};
        void Enter() override;
        void Update() override;
        void Exit() override;

        virtual bool RequestState(uint32_t& request) override;
};

class PlayerStarState : public IPlayerState
{
    appState(PlayerStarState);

public:
    PlayerStarState(Player* player) : IPlayerState(player){};
    virtual ~PlayerStarState(){};
    void Enter() override;
    void Update() override;
    void Exit() override;

    virtual bool RequestState(uint32_t& request) override;
};
