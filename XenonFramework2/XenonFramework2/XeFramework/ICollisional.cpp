#include "ICollisional.h"

RTTI_CLASS_DERIVATIONS(	ICollisional,
						RTTI_DERIVATIONS_END
						);

ICollisional::ICollisional():
RTTI_CLASS_DEFINE( ICollisional ),
m_manager( 0 ),
m_collMode( cmBox ),
m_collRange( 0.0f ),
m_myActor( 0 ),
m_collLastState( false ),
m_collCat( 0 ),
m_collMask( -1 )
{
}

ICollisional::~ICollisional()
{
	unbind();
}

void ICollisional::bind( CollisionManager* m, IActor* a )
{
	unbind();
	m_manager = m;
	if( m_manager )
		m_manager->attach( this );
	m_myActor = a;
}

void ICollisional::unbind()
{
	if( m_manager )
		m_manager->detach( this );
	m_manager = 0;
	m_myActor = 0;
}

IActor* ICollisional::getActor()
{
	return( m_myActor );
}

void ICollisional::addCollision( ICollisional* c )
{
	m_collisions.AddPointer( c );
}

ICollisional::Element ICollisional::firstElement()
{
	return( m_collisions.FirstPointer() );
}

void ICollisional::clear()
{
	m_collisions.Clear();
}

bool ICollisional::isCollide()
{
	return( m_collisions.Size() ? true : false );
}

bool ICollisional::collisionChange()
{
	return( m_collLastState != ( m_collisions.Size() ? true : false ) );
}

void ICollisional::setCollisionRange( float r )
{
	m_collRange = r;
}

float ICollisional::getCollisionRange()
{
	return( m_collRange );
}

void ICollisional::setCollisionPosition( const XeCore::XeHalfVector& p )
{
	m_collPosition = p;
}

XeCore::XeHalfVector& ICollisional::getCollisionPosition()
{
	return( m_collPosition );
}

void ICollisional::setCollisionBox( const XeCore::XeHalfVector& min, const XeCore::XeHalfVector& max )
{
	m_collBoxMin = min;
	m_collBoxMax = max;
}

XeCore::XeHalfVector& ICollisional::getCollisionBoxMin()
{
	return( m_collBoxMin );
}

XeCore::XeHalfVector& ICollisional::getCollisionBoxMax()
{
	return( m_collBoxMax );
}
