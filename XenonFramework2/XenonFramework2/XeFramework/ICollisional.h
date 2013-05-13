#pragma once

#include "IRtti.h"
#include "IActor.h"
#include "CollisionManager.h"

class ICollisional : public virtual IRtti, public MemoryManager::Manageable
{
	friend class CollisionManager;

	RTTI_CLASS_DECLARE( ICollisional );

public:
	enum CollisionMode
	{
		cmRange,
		cmBox,
		cmCount
	};

	typedef XeCore::XeElementPointer< ICollisional* > Element;

										ICollisional();
	virtual 							~ICollisional();
	void								bind( CollisionManager* m, IActor* a );
	void								unbind();
	IActor*								getActor();
	void								addCollision( ICollisional* c );
	Element								firstElement();
	void								clear();
	bool								isCollide();
	bool								collisionChange();
	FORCEINLINE void					setCollisionMode( CollisionMode cm ) { m_collMode = cm; }
	FORCEINLINE CollisionMode			getCollisionMode() { return( m_collMode ); }
	void								setCollisionRange( float r );
	float								getCollisionRange();
	void								setCollisionPosition( const XeCore::XeHalfVector& p );
	XeCore::XeHalfVector&				getCollisionPosition();
	void								setCollisionBox( const XeCore::XeHalfVector& min, const XeCore::XeHalfVector& max );
	XeCore::XeHalfVector&				getCollisionBoxMin();
	XeCore::XeHalfVector&				getCollisionBoxMax();
	FORCEINLINE void					setCollisionCategory( XeCore::XeDword cat ) { m_collCat = cat; }
	FORCEINLINE XeCore::XeDword			getCollisionCategory() { return( m_collCat ); }
	FORCEINLINE void					setCollisionMask( XeCore::XeDword mask ) { m_collMask = mask; }
	FORCEINLINE XeCore::XeDword			getCollisionMask() { return( m_collMask ); }

private:
	CollisionManager*					m_manager;
	CollisionMode						m_collMode;
	XeCore::XeElements< ICollisional* >	m_collisions;
	IActor*								m_myActor;
	float								m_collRange;
	XeCore::XeHalfVector				m_collPosition;
	bool								m_collLastState;
	XeCore::XeHalfVector				m_collBoxMin;
	XeCore::XeHalfVector				m_collBoxMax;
	XeCore::XeDword						m_collCat;
	XeCore::XeDword						m_collMask;
};
