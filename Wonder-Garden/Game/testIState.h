//#pragma once
//#include "Assets/Util/CRC32.h"
//
//#define appState(name) \
//public:\
//    static constexpr uint32_t ID(){ return Hash32(#name);}
//
//class IState
//{
//public:
//    IState(){};
//    virtual ~IState(){};
//
//    virtual void Enter() = 0;
//    virtual void Update() = 0;
//    virtual void Exit() = 0;
//
//    virtual bool RequestState(uint32_t& request) = 0;
//};
//
//
//class StatePatternBase
//{
//    using StateMap = std::map<uint32_t,IState*>;
//
//protected:
//    StateMap m_stateMap;
//    IState* m_currentState;
//
//public:
//    StatePatternBase() : m_currentState(nullptr)
//    {
//        m_stateMap.clear();
//    }
//    virtual ~StatePatternBase()
//    {
//        for (auto it : m_stateMap)
//        {
//            delete it.second;
//            it.second = nullptr;
//        }
//        m_stateMap.clear();
//    }
//
//    virtual void Update() = 0;
//
//protected:
//    inline IState* FindState(uint32_t id)
//    {
//        const auto& it = m_stateMap.find(id);
//        if (it == m_stateMap.end())
//        {
//            return nullptr;
//        }
//        return it->second;
//    }
//
//public:
//    template <typename T>
//    inline void RegisterState()
//    {
//        stateMap.emplace(T::ID(), new T());
//    }
//
//    template<typename T>
//    inline void InitializeState()
//    {
//        m_currentState = FindState(T::ID());
//    }
//};
//
//class PlayerStatePattern : public StatePatternBase
//{
//public:
//    PlayerStatePattern();
//    virtual ~PlayerStatePattern();
//
//    virtual void Update() override;
//};
//
//
//class PlayerIdleState : public IState
//{
//    appState(PlayerIdleState);
//
//public:
//    PlayerIdleState() : IState() {}
//    virtual ~PlayerIdleState() {}
//
//    virtual void Enter() override;
//    virtual void Update() override;
//    virtual void Exit() override;
//
//    virtual bool RequestState(uint32_t& request) override;
//};
//
//
//
//class PlayerMoveState : public IState
//{
//    appState(PlayerMoveState);
//
//public:
//    PlayerMoveState() : IState() {}
//    virtual ~PlayerMoveState() {}
//
//    virtual void Enter() override;
//    virtual void Update() override;
//    virtual void Exit() override;
//
//    virtual bool RequestState(uint32_t& request) override;
//};
