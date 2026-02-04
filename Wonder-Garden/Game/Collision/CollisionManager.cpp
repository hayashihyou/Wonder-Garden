#include "stdafx.h"

#include "AttackCollision.h"
#include "CollisionManager.h"
#include "EffectManager.h"
#include "Enemy/Boss.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyType2.h"
#include "Magic.h"
#include "Player/Player.h"

namespace
{
    const Vector3 ENEMY_EFFECT_SCALE = {10.0f, 10.0f, 10.0f};
    const Vector3 BOSS_EFFECT_SCALE = {20.0f, 20.0f, 20.0f};
}

CollisionManager* CollisionManager::m_instance = nullptr;

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
    if (player == nullptr)
    {
        player = NewGO<Player>(0, "Player");
    }
    Boss* boss = FindGO<Boss>("Boss");
    std::vector<Enemy*> enemys = FindGOs<Enemy>("Enemy");
    std::vector<EnemyType2*> enemysType2s = FindGOs<EnemyType2>("EnemyType2");

    // 当たり判定の処理をここでする

    // プレイヤーの攻撃がエネミーに当たったか
    {
        if (player->GetCollision() != nullptr)
        {

            for (Enemy* enemy : enemys)
            {
                if (enemy->GetColision() != nullptr)
                {
                    if (player->GetCollision()->m_punchCollision->IsHit(enemy->GetColision()))
                    {
                        // @tod for 数値をどこかに定数とかでおきたいね
                        // プレイヤーの攻撃力みたいなものを使いたい
                        enemy->DamagePunch(2);
                        Vector3 enemyEffectPos = enemy->GetPosition();
                        enemyEffectPos.y += 30.0f;
                        EffectManager::Get()->PlayEffect(enemyEffectPos, enemy->GetRotation(), ENEMY_EFFECT_SCALE, EnEffcetType::Enemy_Hit);
                    }
                }
            }
        }

        if (player->GetCollision() != nullptr)
        {

            for (EnemyType2* enemyType2 : enemysType2s)
            {
                if (enemyType2->GetCollision() != nullptr)
                {
                    if (player->GetCollision()->m_punchCollision->IsHit(enemyType2->GetCollision()))
                    {
                        enemyType2->DamagePunch(2);
                        Vector3 enemy2EffectPos = enemyType2->GetPosition();
                        enemy2EffectPos.y += 50.0f;
                        EffectManager::Get()->PlayEffect(enemy2EffectPos, enemyType2->GetRotation(), ENEMY_EFFECT_SCALE, EnEffcetType::Enemy_Hit);
                    }
                }
            }
        }
    }
    // プレイヤーがエネミーを踏んだ時
    {
        if (player->GetCollision() != nullptr)
        {

            for (Enemy* enemy : enemys)
            {
                if (enemy->GetHeadCollision()->IsHit(*player->GetCharCon()))
                {
                    Vector3 v = enemy->GetPosition() - player->GetPosition();
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

        if (player->GetCollision() != nullptr)
        {

            for (EnemyType2* enemyType2 : enemysType2s)
            {
                if (enemyType2->GetHeadCollision()->IsHit(*player->GetCharCon()))
                {
                    Vector3 v = enemyType2->GetPosition() - player->GetPosition();
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

    // プレイヤーの攻撃がボスに当たったか
    // TODO:ボスクラスの方でコリジョンがnullptrになっているため原因を探す

    {
        if (boss)
        {
            if (player->GetCollision() != nullptr)
            {
                if (boss->GetCollision() != nullptr)
                {
                    if (player->GetCollision()->m_punchCollision->IsHit(boss->GetCollision()))
                    {
                        boss->DamagePunch(2);
                        Vector3 bossEffectPos = boss->GetPosition();
                        bossEffectPos.y += 75.0f;
                        EffectManager::Get()->PlayEffect(bossEffectPos, boss->GetRotation(), BOSS_EFFECT_SCALE, EnEffcetType::Boss_Hit);
                    }
                }
            }

            if (player->GetCollision() != nullptr)
            {
                if (boss->GetHeadCollision()->IsHit(*player->GetCharCon()))
                {
                    Vector3 v = boss->GetPosition() - player->GetPosition();
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

    // エネミー、ボスの攻撃がプレイヤーに当たった時
    {
        if (player)
        {

            for (Enemy* enemy : enemys)
            {
                if (enemy->GetAttackCollision())
                {
                    if (enemy->GetAttackCollision()->m_punchCollision->IsHit(*player->GetCharCon()))
                    {
                        player->Damage(1);
                    }
                }
            }

            for (EnemyType2* enemyType2 : enemysType2s)
            {
                if (enemyType2->GetAttackCollision())
                {
                    if (enemyType2->GetAttackCollision()->m_magicCollision->IsHit(*player->GetCharCon()))
                    {
                        player->Damage(1);
                    }
                }
            }

            if (boss != nullptr)
            {
                if (boss->GetAttackCollision())
                {
                    if (boss->GetAttackCollision()->m_punchCollision->IsHit(*player->GetCharCon()))
                    {
                        player->Damage(2);
                    }
                }
            }
        }
    }
}
