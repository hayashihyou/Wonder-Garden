#include "stdafx.h"

#include "CoinCount.h"

bool CoinCounter::Start()
{
    return true;
}

void CoinCounter::Count()
{
    m_countOnes++;
    m_totalCount++;

    if (m_countOnes > 9)
    {
        m_countTens++;
        m_countOnes = 0;
    }
}
