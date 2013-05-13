#pragma once

#include "IRtti.h"
#include "IItemsManager.h"
#include "IControllable.h"

class ControlManager : public virtual IRtti, public IItemsManager< IControllable >, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( ControlManager );
	
public:
			ControlManager();
			~ControlManager();
	void	update();
	void	input();
	void	setActive( bool mode );
	bool	isActive();

private:
	bool	m_active;
};
