#include "IRenderable.h"
#include "IScene.h"

RTTI_CLASS_DERIVATIONS(	IRenderable,
						RTTI_DERIVATIONS_END
						);

IRenderable::IRenderable():
RTTI_CLASS_DEFINE( IRenderable ),
m_parent( 0 ),
m_renderable( true ),
m_position( 0.0f, 0.0f, 0.0f ),
m_rotation( 0.0f, 0.0f, 0.0f ),
m_scale( 1.0f, 1.0f, 1.0f ),
m_order( 0.0f ),
m_needUpdate( false ),
m_needUpdateCounter( 0 ),
m_needUpdateCounterMax( 1 )
{
}

IRenderable::~IRenderable()
{
	if( m_parent )
		m_parent->detach( this );
}

void IRenderable::setRenderable( bool mode )
{
	m_renderable = mode;
}

bool IRenderable::isRenderable()
{
	return( m_renderable );
}

IScene* IRenderable::getParent()
{
	return( m_parent );
}

XeCore::XeHalfVector& IRenderable::getPosition()
{
	return( m_position );
}

XeCore::XeAngleHalfVector& IRenderable::getRotation()
{
	return( m_rotation );
}

XeCore::XeHalfVector& IRenderable::getScale()
{
	return( m_scale );
}

float IRenderable::getOrder()
{
	return( m_order );
}

void IRenderable::setPosition( XeCore::XeHalfVector& v )
{
	m_needUpdate = true;
	m_position = v;
}

void IRenderable::setRotation( XeCore::XeAngleHalfVector& v )
{
	m_needUpdate = true;
	m_rotation = v;
}

void IRenderable::setScale( XeCore::XeHalfVector& v )
{
	m_needUpdate = true;
	m_scale = v;
}

void IRenderable::setOrder( float o )
{
	m_order = o;
}

void IRenderable::setNeedUpdate( bool m )
{
	m_needUpdate = m;
	m_needUpdateCounter = m ? m_needUpdateCounterMax : 0;
}

bool IRenderable::isNeedUpdate()
{
	return( m_needUpdate );
}

void IRenderable::increaseNeedUpdateCounter()
{
	m_needUpdateCounter++;
	m_needUpdate = true;
}

void IRenderable::decreaseNeedUpdateCounter()
{
	if( m_needUpdateCounter > 0 )
		m_needUpdateCounter--;
	if( m_needUpdateCounter <= 0 )
		m_needUpdate = false;
}

unsigned int IRenderable::getNeedUpdateCounterMax()
{
	return( m_needUpdateCounterMax );
}

void IRenderable::setNeedUpdateCounterMax( unsigned int v )
{
	m_needUpdateCounterMax = v;
}