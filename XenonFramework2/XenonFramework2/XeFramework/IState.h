#pragma once

#include "IRtti.h"

class Manager;
class IProgressState;

class IState : public virtual  IRtti, public virtual MemoryManager::Manageable
{
	friend class Manager;

	RTTI_CLASS_DECLARE( IState );

public:
								IState();
	virtual						~IState() = 0;
	virtual void				onEnter( IProgressState* p ) = 0;
	virtual void				onExit() = 0;
	virtual void				onUpdate() = 0;
	virtual void				onRender() = 0;
	virtual void				onInput() = 0;
};
