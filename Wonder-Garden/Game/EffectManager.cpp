#include "stdafx.h"

#include "EffectManager.h"

EffectManager* EffectManager::m_instance = nullptr;

EffectManager::EffectManager() {}

EffectManager::~EffectManager()
{
   
}

bool EffectManager::Start()
{
    EffectEngine::GetInstance()->ResistEffect(Enemy_Hit, u"Assets/effect/Enemy_Hit/Enemy_Hit.efk");
    EffectEngine::GetInstance()->ResistEffect(Boss_Hit, u"Assets/effect/Boss_Hit/Boss_Hit.efk");
    EffectEngine::GetInstance()->ResistEffect(Cannon_Fire, u"Assets/effect/Cannon_Fire/Cannon_Fire.efk");
    EffectEngine::GetInstance()->ResistEffect(Player_Attack, u"Assets/effect/Player_Attack/Player_Attack.efk");
    EffectEngine::GetInstance()->ResistEffect(Boss_Attack, u"Assets/effect/Boss_Attack/Boss_Attack.efk");
    EffectEngine::GetInstance()->ResistEffect(Game_Clear, u"Assets/effect/Game_Clear/Game_Clear.efk");

    return true;
}

EffectEmitter* EffectManager::PlayEffect(Vector3 position, Quaternion rotation, Vector3 scale, int num)
{
    EffectEmitter* effect = NewGO<EffectEmitter>(0);
    effect->Init(num);
    effect->SetPosition(position);
    effect->SetRotation(rotation);
    effect->SetScale(scale);
    effect->Play();

    return effect;
}
