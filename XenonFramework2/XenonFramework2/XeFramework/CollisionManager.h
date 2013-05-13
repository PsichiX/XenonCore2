#pragma once

#include "IRtti.h"
#include "IItemsManager.h"

class ICollisional;

class CollisionManager : public virtual IRtti, public IItemsManager< ICollisional >, public MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( CollisionManager );

public:
	struct CollSides
	{
		bool					top;
		bool					left;
		bool					bottom;
		bool					right;
	};

	struct Area
	{
		XeCore::XeHalfVector	begin;
		XeCore::XeHalfVector	end;
		CollSides				a;
		CollSides				b;
	};

					CollisionManager();
					~CollisionManager();
	void			update();
	void			setActive( bool mode );
	bool			isActive();
	ICollisional*	pickAABB( XeCore::XeHalfVector& posBeg, XeCore::XeHalfVector& posEnd, Area* area = 0 );
	ICollisional*	pick( XeCore::XeHalfVector& pos );
	bool			canCollide( ICollisional* a, ICollisional* b );

private:
	bool			m_active;
};
