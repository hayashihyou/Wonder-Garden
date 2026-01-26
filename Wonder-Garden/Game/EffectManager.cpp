#include "stdafx.h"
#include "EffectManager.h"

bool EffectManager::Start()
{
    EffectEngine::GetInstance()->ResistEffect(Hit, u"Assets/effect/Hit.efk");
    EffectEngine::GetInstance()->ResistEffect(Boss_Hit, u"Assets/effect/Boss_Hit.efk");

    return true;
}
