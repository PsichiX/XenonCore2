#pragma once

#include "IRtti.h"
#include "INamedItemsManager.h"
#include "IScene.h"

class SceneManager : public virtual IRtti, public INamedItemsManager< NameID, IScene >, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( SceneManager );

public:
						SceneManager();
						~SceneManager();
	void				update();
	void				render();
	void				getInfoList( XeCore::XeString& out );

private:
	static int			sort( INamedItemsManager< NameID, IScene >::Pair* a, INamedItemsManager< NameID, IScene >::Pair* b );
};