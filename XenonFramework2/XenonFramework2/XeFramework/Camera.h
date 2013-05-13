#pragma once

#include "IRtti.h"
#include "Engine.h"

class Camera : public virtual IRtti, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Camera );

public:
							Camera();
	XeCore::XeHalfMatrix*	getMatrix();
	bool					projectionOrtho( float x, float y, float w, float h, float a, float zn = -1.0f, float zf = 1.0f );
	bool					projectionPerspective( XeCore::XeAngleVector a, XeCore::XeHalfVector p, bool projection = false, float angle = 45.0f, float aspect = 1.0f, float znear = 1.0f, float zfar = 10000.0f );
	void					setScissorActive( bool mode );
	void					setScissorX( int v );
	void					setScissorY( int v );
	void					setScissorWidth( int v );
	void					setScissorHeight( int v );
	void					setScissorClearBG( bool m );
	bool					getScissorActive();
	int						getScissorX();
	int						getScissorY();
	int						getScissorWidth();
	int						getScissorHeight();
	bool					getScissorClearBG();
	void					activateScissor();
	void					unactivateScissor();

private:
	XeCore::XeHalfMatrix	m_projectionMatrix;
	bool					m_scissorActive;
	int						m_scissorX;
	int						m_scissorY;
	int						m_scissorWidth;
	int						m_scissorHeight;
	bool					m_scissorClearBG;
};