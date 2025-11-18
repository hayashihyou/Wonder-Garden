#include "stdafx.h"
#include "EffectManager.h"

bool EffectManager::Start()
{
    EffectEngine::GetInstance()->ResistEffect(Hit, u"Assets/effect/Hit.efk");

    return true;
}
