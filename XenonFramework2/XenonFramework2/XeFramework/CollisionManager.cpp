#include "CollisionManager.h"
#include "ICollisional.h"

RTTI_CLASS_DERIVATIONS(	CollisionManager,
						RTTI_DERIVATIONS_END
						);

CollisionManager::CollisionManager():
RTTI_CLASS_DEFINE( CollisionManager ),
m_active( true )
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::update()
{
	if( !m_active )
		return;
	for( XeCore::XeElementPointer< ICollisional* > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
		e()->m_collLastState = e()->m_collisions.Size() ? true : false;
	for( XeCore::XeElementPointer< ICollisional* > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
	{
		e()->clear();
		for( XeCore::XeElementPointer< ICollisional* > _e = access().FirstPointer(); !_e.IsEmpty(); _e.Next() )
		{
			if( e == _e )
				continue;
			if( canCollide( e(), _e() ) && e()->getCollisionMode() == ICollisional::cmRange )
			{
				if( ( e()->getCollisionPosition() - _e()->getCollisionPosition() ).Length() < e()->getCollisionRange() + _e()->getCollisionRange() )
				{
					e()->addCollision( _e() );
					_e()->addCollision( e() );
				}
			}
			else
			if( canCollide( e(), _e() ) && e()->getCollisionMode() == ICollisional::cmBox )
			{
				XeCore::XeHalfVector min = e()->getCollisionBoxMin() + e()->getCollisionPosition();
				XeCore::XeHalfVector max = e()->getCollisionBoxMax() + e()->getCollisionPosition();
				XeCore::XeHalfVector _min = _e()->getCollisionBoxMin() + _e()->getCollisionPosition();
				XeCore::XeHalfVector _max = _e()->getCollisionBoxMax() + _e()->getCollisionPosition();
				if( max.X >= _min.X && max.Y >= _min.Y && min.X < _max.X && min.Y < _max.Y )
				{
					e()->addCollision( _e() );
					_e()->addCollision( e() );
				}
			}
		}
	}
}

void CollisionManager::setActive( bool mode )
{
	m_active = mode;
}

bool CollisionManager::isActive()
{
	return( m_active );
}

ICollisional* CollisionManager::pickAABB( XeCore::XeHalfVector& posBeg, XeCore::XeHalfVector& posEnd, Area* area )
{
	for( XeCore::XeElementPointer< ICollisional* > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
	{
		if( e()->getCollisionMode() == ICollisional::cmRange )
		{
			if( ( e()->getCollisionPosition() - ( ( posBeg + posEnd ) * XeCore::XeHalfVector( 0.5f, 0.5f ) ) ).Length() < e()->getCollisionRange() )
			{
				return( e() );
			}
		}
		else
		if( e()->getCollisionMode() == ICollisional::cmBox )
		{
			XeCore::XeHalfVector min = e()->getCollisionBoxMin() + e()->getCollisionPosition();
			XeCore::XeHalfVector max = e()->getCollisionBoxMax() + e()->getCollisionPosition();
			XeCore::XeHalfVector _min = posBeg;
			XeCore::XeHalfVector _max = posEnd;
			if( max.X >= _min.X && max.Y >= _min.Y && min.X < _max.X && min.Y < _max.Y )
			{
				if( area )
				{
					memset( area, 0, sizeof( Area ) );
					area->begin.X = max( min.X, _min.X );
					area->begin.Y = max( min.Y, _min.Y );
					area->end.X = min( max.X, _max.X );
					area->end.Y = min( max.Y, _max.Y );
					area->a.top = _min.Y > min.Y;
					area->a.left = _min.X > min.X;
					area->a.bottom = _max.Y < max.Y;
					area->a.right = _max.X < max.X;
					area->b.top = min.Y < _min.Y;
					area->b.left = min.X < _min.X;
					area->b.bottom = max.Y > _max.Y;
					area->b.right = max.X > _max.X;
				}
				return( ( area->a.top || area->a.bottom || area->a.left || area->a.right ) ? e() : 0 );
			}
		}
	}
	return( 0 );
}

ICollisional* CollisionManager::pick( XeCore::XeHalfVector& pos )
{
	for( XeCore::XeElementPointer< ICollisional* > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
	{
		if( e()->getCollisionMode() == ICollisional::cmRange )
		{
			if( ( e()->getCollisionPosition() - pos ).Length() < e()->getCollisionRange() )
			{
				return( e() );
			}
		}
		else
		if( e()->getCollisionMode() == ICollisional::cmBox )
		{
			XeCore::XeHalfVector min = e()->getCollisionBoxMin() + e()->getCollisionPosition();
			XeCore::XeHalfVector max = e()->getCollisionBoxMax() + e()->getCollisionPosition();
			XeCore::XeHalfVector _min = pos;
			XeCore::XeHalfVector _max = pos;
			if( max.X >= _min.X && max.Y >= _min.Y && min.X < _max.X && min.Y < _max.Y )
			{
				return( e() );
			}
		}
	}
	return( 0 );
}

bool CollisionManager::canCollide( ICollisional* a, ICollisional* b )
{
	return( ( a->getCollisionMask() & b->getCollisionCategory() ) && ( b->getCollisionMask() & a->getCollisionCategory() ) );
}
