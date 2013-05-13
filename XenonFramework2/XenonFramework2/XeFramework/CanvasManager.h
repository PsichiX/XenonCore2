#pragma once

#include "IRtti.h"
#include "INamedItemsManager.h"
#include "Canvas.h"

class CanvasManager : public virtual IRtti, public INamedItemsManager< NameID, Canvas >, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( CanvasManager );

public:
	CanvasManager();
	~CanvasManager();
};