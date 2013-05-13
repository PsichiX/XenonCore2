#pragma once

#include "IRtti.h"
#include "../XeCore/Base/XeVectorTemplate.h"
#include "../XeCore/Base/XeAngleVectorTemplate.h"

class IScene;

class IRenderable : public virtual IRtti, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( IRenderable );

	friend class IScene;

public:

									IRenderable();
	virtual							~IRenderable();
	void							setRenderable( bool mode );
	bool							isRenderable();
	IScene*							getParent();
	XeCore::XeHalfVector&			getPosition();
	XeCore::XeAngleHalfVector&		getRotation();
	XeCore::XeHalfVector&			getScale();
	float							getOrder();
	void							setPosition( XeCore::XeHalfVector& v );
	void							setRotation( XeCore::XeAngleHalfVector& v );
	void							setScale( XeCore::XeHalfVector& v );
	void							setOrder( float o );
	void							setNeedUpdate( bool m );
	bool							isNeedUpdate();
	void							increaseNeedUpdateCounter();
	void							decreaseNeedUpdateCounter();
	unsigned int					getNeedUpdateCounterMax();
	void							setNeedUpdateCounterMax( unsigned int v );
		
private:
	IScene*							m_parent;
	bool							m_renderable;
	XeCore::XeHalfVector			m_position;
	XeCore::XeAngleHalfVector		m_rotation;
	XeCore::XeHalfVector			m_scale;
	float							m_order;
	bool							m_needUpdate;
	unsigned int					m_needUpdateCounter;
	unsigned int					m_needUpdateCounterMax;
};
