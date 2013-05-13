#pragma once

#include "IRtti.h"
#include "INamedItemsManager.h"
#include "IActor.h"

class ActorManager : public virtual IRtti, public INamedItemsManager< NameID, IActor >, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( ActorManager );

public:
						ActorManager();
						~ActorManager();
	void				removeAll();
	void				update();
	void				input();
	void				render();

	void				getInfoList( XeCore::XeString& out );
};