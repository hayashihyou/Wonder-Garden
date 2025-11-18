#include "stdafx.h"
//#include "testIState.h"
//
//PlayerStatePattern::PlayerStatePattern() : StatePatternBase()
//{
//
//}
//
//PlayerStatePattern::~PlayerStatePattern()
//{
//
//}
//
//void PlayerStatePattern::Update()
//{
//    K2_ASSERT(m_currentState != nullptr, "カレントステートねえぞこの野郎");
//    if (m_currentState)
//    {
//        uint32_t request;
//        if (m_currentState->RequestState(request))
//        {
//            m_currentState->Exit();
//            m_currentState = FindState(request);
//            m_currentState->Enter();
//        }
//        m_currentState->Update();
//    }
//}
//
//void PlayerIdleState::Enter()
//{
//    
//}
//
//
//void PlayerIdleState::Update()
//{
//
//}
//
//
//void PlayerIdleState::Exit()
//{
//
//}
//
//
//bool PlayerIdleState::RequestState(uint32_t& request)
//{
//    if (1)
//    {
//        request = PlayerMoveState::ID();
//        return;
//    }
//
//    return false;
//}
