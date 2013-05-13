#pragma once

#include "IRtti.h"
#include "Camera.h"

class Camera3D : public virtual IRtti, public Camera, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Camera3D );

public:
							Camera3D( float a = 0.0f, float b = 0.0f, float g = 0.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f, bool p = false, float ang = 45.0f, float asp = 1.0f, float zn = 1.0f, float zf = 10000.0f );
	FORCEINLINE void		setAlpha( float v ) { m_a = v; }
	FORCEINLINE float		getAlpha() { return( m_a ); }
	FORCEINLINE void		setBeta( float v ) { m_b = v; }
	FORCEINLINE float		getBeta() { return( m_b ); }
	FORCEINLINE void		setGamma( float v ) { m_g = v; }
	FORCEINLINE float		getGamma() { return( m_g ); }
	FORCEINLINE void		setX( float v ) { m_x = v; }
	FORCEINLINE float		getX() { return( m_x ); }
	FORCEINLINE void		setY( float v ) { m_y = v; }
	FORCEINLINE float		getY() { return( m_y ); }
	FORCEINLINE void		setZ( float v ) { m_z = v; }
	FORCEINLINE float		getZ() { return( m_z ); }
	FORCEINLINE void		setProjectionFromEyeToCameraPos( bool v ) { m_p = v; }
	FORCEINLINE bool		getProjectionFromEyeToCameraPos() { return( m_p ); }
	FORCEINLINE void		setAngle( float v ) { m_z = v; }
	FORCEINLINE float		getAngle() { return( m_z ); }
	FORCEINLINE void		setAspect( float v ) { m_asp = v; }
	FORCEINLINE float		getAspect() { return( m_asp ); }
	FORCEINLINE void		setZnear( float v ) { m_zn = v; }
	FORCEINLINE float		getZnear() { return( m_zn ); }
	FORCEINLINE void		setZfar( float v ) { m_zf = v; }
	FORCEINLINE float		getZfar() { return( m_zf ); }
	FORCEINLINE void		apply() { projectionPerspective( XeCore::XeAngleVector( m_a, m_b, m_g ), XeCore::XeHalfVector( m_x, m_y, m_z ), m_p, m_ang, m_asp, m_zn, m_zf ); }

private:
	float					m_a;
	float					m_b;
	float					m_g;
	float					m_x;
	float					m_y;
	float					m_z;
	bool					m_p;
	float					m_ang;
	float					m_asp;
	float					m_zn;
	float					m_zf;
};