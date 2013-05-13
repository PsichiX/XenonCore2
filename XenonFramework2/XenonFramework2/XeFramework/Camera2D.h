#pragma once

#include "IRtti.h"
#include "Camera.h"

class Camera2D : public virtual IRtti, public Camera, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Camera2D );

public:
							Camera2D( float x = 0.0f, float y = 0.0f, float w = 1.0f, float h = 1.0f, float a = 0.0f );
	FORCEINLINE void		setX( float v ) { m_x = v; }
	FORCEINLINE float		getX() { return( m_x ); }
	FORCEINLINE void		setY( float v ) { m_y = v; }
	FORCEINLINE float		getY() { return( m_y ); }
	FORCEINLINE void		setWidth( float v ) { m_width = v; }
	FORCEINLINE float		getWidth() { return( m_width ); }
	FORCEINLINE void		setHeight( float v ) { m_height = v; }
	FORCEINLINE float		getHeight() { return( m_height ); }
	FORCEINLINE void		setAngle( float v ) { m_angle = v; }
	FORCEINLINE float		getAngle() { return( m_angle ); }
	FORCEINLINE void		apply() { projectionOrtho( m_x, m_y, m_width, m_height, m_angle ); }

private:
	float					m_x;
	float					m_y;
	float					m_width;
	float					m_height;
	float					m_angle;
};