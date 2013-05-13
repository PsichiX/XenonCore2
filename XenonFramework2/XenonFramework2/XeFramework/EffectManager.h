#pragma once

#include "IRtti.h"
#include "INamedItemsManager.h"
#include "Effect.h"

class EffectManager : public virtual IRtti, public INamedItemsManager< NameID, Effect >, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( EffectManager );

public:
	EffectManager();
	~EffectManager();
};