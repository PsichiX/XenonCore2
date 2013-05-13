#pragma once

#include "IRtti.h"
#include "IActor.h"

class IController : public virtual IRtti, public virtual MemoryManager::Manageable
{
	friend class IControllable;

	RTTI_CLASS_DECLARE( IController );

public:
					IController();
	virtual			~IController() = 0;
	virtual void	update() = 0;
	virtual void	input() = 0;
	IActor*			getActor();

private:
	IActor*			m_actor;
};
