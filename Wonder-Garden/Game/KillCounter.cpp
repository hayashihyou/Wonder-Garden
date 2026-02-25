#include "stdafx.h"
#include "KillCounter.h"

bool KillCounter::Start()
{
    return true;
}

void KillCounter::Update()
{
    
}

void KillCounter::TotalCount()
{
    m_totalCount = m_enemyCount + m_enemyType2Count + m_bossCount;
}

void KillCounter::EnemyCount()
{
    m_enemyCount++;
}

void KillCounter::EnemyType2Count()
{
    m_enemyType2Count++;
}

void KillCounter::BossCount()
{
    m_bossCount++;
}
