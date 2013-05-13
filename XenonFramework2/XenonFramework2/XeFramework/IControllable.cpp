#include "IControllable.h"
#include "ControlManager.h"

RTTI_CLASS_DERIVATIONS(	IControllable,
						RTTI_DERIVATIONS_END
						);

IControllable::IControllable():
RTTI_CLASS_DEFINE( IControllable ),
m_controller( 0 ),
m_manager( 0 ),
m_myActor( 0 )
{
}

IControllable::~IControllable()
{
	if( m_controller )
		m_controller->m_actor = 0;
	DELETE_OBJECT( m_controller );
	unbind();
}

void IControllable::bind( ControlManager* m, IActor* a )
{
	unbind();
	m_manager = m;
	if( m_manager )
		m_manager->attach( this );
	m_myActor = a;
}

void IControllable::unbind()
{
	if( m_manager )
		m_manager->detach( this );
	m_manager = 0;
	m_myActor = 0;
}

IActor* IControllable::getActor()
{
	return( m_myActor );
}

void IControllable::setController( IController* newcontroller )
{
	if( m_controller )
		m_controller->m_actor = 0;
	DELETE_OBJECT( m_controller );
	m_controller = newcontroller;
	m_controller->m_actor = m_myActor;
}

IController* IControllable::getController()
{
	return( m_controller );
}
