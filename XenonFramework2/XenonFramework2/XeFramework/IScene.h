#pragma once

#include "IRtti.h"
#include "IItemsManager.h"
#include "IRenderable.h"
#include "Camera.h"
#include "Canvas.h"

class IScene : public virtual IRtti, public IItemsManager< IRenderable >, public IRenderable, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( IScene );

public:
							IScene();
	virtual					~IScene();
	virtual void			update() = 0;
	virtual	void			render() = 0;
	void					setCamera( Camera* newcamera );
	Camera*					getCamera();
	void					setCanvas( Canvas* canvas );
	Canvas*					getCanvas();
	virtual bool			attach( IRenderable* i );
	virtual bool			detach( IRenderable* i );

private:
	Camera*					m_camera;
	Canvas*					m_canvas;

protected:
	static void				setParent( IScene* parent, IRenderable* child );
};