#include "stdafx.h"
#include "EffectManager.h"

bool EffectManager::Start()
{
    EffectEngine::GetInstance()->ResistEffect(Enemy_Hit, u"Assets/effect/Enemy_Hit/Enemy_Hit.efk");
    EffectEngine::GetInstance()->ResistEffect(Boss_Hit, u"Assets/effect/Boss_Hit/Boss_Hit.efk");
    EffectEngine::GetInstance()->ResistEffect(Cannon_Fire, u"Assets/effect/Cannon_Fire/Cannon_Fire.efk");

    return true;
}
