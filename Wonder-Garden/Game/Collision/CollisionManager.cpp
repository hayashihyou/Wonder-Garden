#include "stdafx.h"
#include "CollisionManager.h"

#include "Player/Player.h"
#include "AttackCollision.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyType2.h"
#include "Enemy/Boss.h"


CollisionManager* CollisionManager::m_isntace = nullptr;


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}


void CollisionManager::Update()
{
    // NOTE: あえて関数に分割しない
    // 流れを一覧でみたいから

    Player* player = FindGO<Player>("Player");
    Boss* boss = FindGO<Boss>("Boss");
    std::vector<Enemy*> enemys = FindGOs<Enemy>("Enemy");
    std::vector<EnemyType2*> enemysType2s = FindGOs<EnemyType2>("EnemyType2");

    // 当たり判定の処理をここでする

    // プレイヤーの攻撃がエネミーに当たったか
    {
        if (player->punchCollision != nullptr)
        {

            for (Enemy* enemy : enemys)
            {
                if (player->punchCollision->m_punchCollision->IsHit(enemy->GetColision()))
                {
                    // @tod for 数値をどこかに定数とかでおきたいね
                    // プレイヤーの攻撃力みたいなものを使いたい
                    enemy->DamagePunch(2);
                }
            }
        }

        if (player->punchCollision != nullptr)
        {

            for (EnemyType2* enemyType2 : enemysType2s)
            {
                if (player->punchCollision->m_punchCollision->IsHit(enemyType2->GetCollision()))
                {
                    enemyType2->DamagePunch(2);
                }
            }
        }
    }
    // プレイヤーがエネミーを踏んだ時
    {
        if (player->punchCollision != nullptr)
        {

            for (Enemy* enemy : enemys)
            {
                if (enemy->GetHeadCollision()->IsHit(player->m_characterController))
                {
                    Vector3 v = enemy->GetPosition() - player->playerPos;
                    v.Normalize();
                    const float dot = v.Dot(Vector3::Down);
                    const float angle = acosf(dot);
                    if (fabs(angle) <= Math::DegToRad(45.0f))
                    {
                        // @tod for 数値をどこかに定数とかでおきたいね
                        // プレイヤーの攻撃力みたいなものを使いたい
                        enemy->DamageReceiveHead(2);
                    }
                }
            }
        }

        if (player->punchCollision != nullptr)
        {

            for (EnemyType2* enemyType2 : enemysType2s)
            {
                if (enemyType2->GetHeadCollision()->IsHit(player->m_characterController))
                {
                    Vector3 v = enemyType2->GetPosition() - player->playerPos;
                    v.Normalize();
                    const float dot = v.Dot(Vector3::Down);
                    const float angle = acosf(dot);
                    if (fabs(angle) <= Math::DegToRad(45.0f))
                    {
                        // @tod for 数値をどこかに定数とかでおきたいね
                        // プレイヤーの攻撃力みたいなものを使いたい
                        enemyType2->DamageReceiveHead(2);
                    }
                }
            }
        }
    }

    //プレイヤーの攻撃がボスに当たったか
    //TODO:ボスクラスの方でコリジョンがnullptrにンっているため原因を探す

    {
        if (boss)
        {
            if (player->punchCollision != nullptr)
            {
                if (player->punchCollision->m_punchCollision->IsHit(boss->GetCollision()))
                {
                    boss->DamagePunch(2);
                }
            }

            if (player->punchCollision != nullptr)
            {
                if (boss->GetHeadCollision()->IsHit(player->m_characterController))
                {
                    Vector3 v = boss->GetPosition() - player->playerPos;
                    v.Normalize();
                    const float dot = v.Dot(Vector3::Down);
                    const float angle = acosf(dot);
                    if (fabs(angle) <= Math::DegToRad(45.0f))
                    {
                        // @tod for 数値をどこかに定数とかでおきたいね
                        // プレイヤーの攻撃力みたいなものを使いたい
                        boss->DamageReceiveHead(2);
                    }
                }
            }
        }
    }


    //エネミー、ボスの攻撃がプレイヤーに当たった時
    {
        if (player)
        {
            for  (Enemy* enemy : enemys)
            {
                if (enemy->enemyAttack)
                {
                    if (enemy->enemyAttack->m_punchCollision->IsHit(player->m_characterController))
                    {
                        player->Damage(1);
                    }
                }
            }

            for (EnemyType2* enemyType2 : enemysType2s)
            {

            }
        }

        
    }
}
