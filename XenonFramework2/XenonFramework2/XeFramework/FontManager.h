#pragma once

#include "IRtti.h"
#include "INamedItemsManager.h"
#include "Font.h"

class FontManager : public virtual IRtti, public INamedItemsManager< NameID, Font >, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( FontManager );

public:
	FontManager();
	~FontManager();
};