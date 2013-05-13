#pragma once

#include "IRtti.h"
#include "INamedItemsManager.h"
#include "Material.h"

class MaterialManager : public virtual IRtti, public INamedItemsManager< NameID, Material >, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( MaterialManager );

public:
	MaterialManager();
	~MaterialManager();
};