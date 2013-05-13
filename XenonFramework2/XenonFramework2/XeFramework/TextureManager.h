#pragma once

#include "IRtti.h"
#include "INamedItemsManager.h"
#include "Texture.h"

class TextureManager : public virtual IRtti, public INamedItemsManager< NameID, Texture >, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( TextureManager );

public:
	TextureManager();
	~TextureManager();
};