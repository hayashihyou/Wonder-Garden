#include "stdafx.h"
#include "Score.h"
#include "CoinCount.h"
#include "KillCounter.h"

bool Score::Start()
{
    m_coinCounter = FindGO<CoinCounter>("CoinCounter");
    m_killCounter = FindGO<KillCounter>("KillCounter");


    return true;
}

void Score::CalcScore()
{
    int coinScore = m_coinCounter->GetTotalCount() * 100;
    int killScore = m_killCounter->GetTotalCount() * 100;

    m_totalScore = coinScore + killScore;
}
