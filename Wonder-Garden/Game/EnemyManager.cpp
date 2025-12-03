#include "stdafx.h"

#include "Enemy/Enemy.h"
#include "EnemyManager.h"
#include "Enemy/EnemyType2.h"

EnemyManager* EnemyManager::m_instance = nullptr;

EnemyManager::EnemyManager() {}

EnemyManager::~EnemyManager()
{
    /*for (int i = 0; i < m_enemy.size(); i++)
    {
        DeleteGO(m_enemy.at(i));
    }*/

    for (int a = 0; a < m_enemyType2.size(); a++)
    {
        DeleteGO(m_enemyType2.at(a));
    }
}

void EnemyManager::Setup()
{
   /* for (int i = 0; i < m_enemy.size(); i++)
    {
        Enemy* enemy = NewGO<Enemy>(0, "Enemy");
        enemy->SetPosition(Vector3(200, 0, i * 50));
        m_enemy.at(i) = enemy;
    }*/

    for (int a = 0; a < m_enemy.size(); a++)
    {
        EnemyType2* enemyType2 = NewGO<EnemyType2>(0, "EnemyType2");
        enemyType2->SetPosition(Vector3(-200, 0, a * 50));
        m_enemyType2.at(a) = enemyType2;
    }
}

void EnemyManager::Update() {}
