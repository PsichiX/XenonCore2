#include "ControlManager.h"
#include "IController.h"

RTTI_CLASS_DERIVATIONS(	ControlManager,
						RTTI_DERIVATIONS_END
						);

ControlManager::ControlManager():
RTTI_CLASS_DEFINE( ControlManager )
{
}

ControlManager::~ControlManager()
{
}

void ControlManager::update()
{
	if( !m_active )
		return;
	for( XeCore::XeElementPointer< IControllable* > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
		if( e()->getController() )
			e()->getController()->update();
}

void ControlManager::input()
{
	if( !m_active )
		return;
	for( XeCore::XeElementPointer< IControllable* > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
		if( e()->getController() )
			e()->getController()->input();
}

void ControlManager::setActive( bool mode )
{
	m_active = mode;
}

bool ControlManager::isActive()
{
	return( m_active );
}