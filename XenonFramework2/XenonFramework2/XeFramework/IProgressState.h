#pragma once

#include "IRtti.h"

#define PROGRESS_STATE_UPDATE(o)	if( o ){ ( o )->onProgress(); }

class Manager;

class IProgressState : public virtual  IRtti, public virtual MemoryManager::Manageable
{
	friend class Manager;

	RTTI_CLASS_DECLARE( IProgressState );

public:
								IProgressState();
	virtual						~IProgressState() = 0;
	virtual void				onEnter() = 0;
	virtual void				onExit() = 0;
	virtual bool				onProgress() = 0;
};
