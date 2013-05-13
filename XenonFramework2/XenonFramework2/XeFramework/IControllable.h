#pragma once

#include "IRtti.h"
#include "IController.h"

class ControlManager;

class IControllable : public virtual IRtti, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( IControllable );

public:
						IControllable();
	virtual				~IControllable();
	void				bind( ControlManager* m, IActor* a );
	void				unbind();
	IActor*				getActor();
	void				setController( IController* newcontroller );
	IController*		getController();

private:
	ControlManager*		m_manager;
	IController*		m_controller;
	IActor*				m_myActor;
};
