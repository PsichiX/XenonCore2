#include "Camera.h"

RTTI_CLASS_DERIVATIONS(	Camera,
						RTTI_DERIVATIONS_END
						);

Camera::Camera():
RTTI_CLASS_DEFINE( Camera ),
m_scissorActive( false ),
m_scissorX( 0 ),
m_scissorY( 0 ),
m_scissorWidth( 0 ),
m_scissorHeight( 0 ),
m_scissorClearBG( false )
{
}

XeCore::XeHalfMatrix* Camera::getMatrix()
{
	return( &m_projectionMatrix );
}

bool Camera::projectionOrtho( float x, float y, float w, float h, float a, float zn, float zf )
{
	return( XeCore::Photon::XeCameraOrthoCustomBuildHalf( &m_projectionMatrix, x, y, w, h, a, zn, zf ) );
}

bool Camera::projectionPerspective(  XeCore::XeAngleVector a, XeCore::XeHalfVector p, bool projection, float angle, float aspect, float znear, float zfar )
{
	return( XeCore::Photon::XeCameraPerspectiveCustomBuildHalf( &m_projectionMatrix, a, p, projection, angle, aspect, znear, zfar ) );
}

void Camera::setScissorActive( bool mode )
{
	m_scissorActive = mode;
}

void Camera::setScissorX( int v )
{
	m_scissorX = v;
}

void Camera::setScissorY( int v )
{
	m_scissorY = v;
}

void Camera::setScissorWidth( int v )
{
	m_scissorWidth = v;
}

void Camera::setScissorHeight( int v )
{
	m_scissorHeight = v;
}

void Camera::setScissorClearBG( bool m )
{
	m_scissorClearBG = m;
}

bool Camera::getScissorActive()
{
	return( m_scissorActive );
}

int Camera::getScissorX()
{
	return( m_scissorX );
}

int Camera::getScissorY()
{
	return( m_scissorY );
}

int Camera::getScissorWidth()
{
	return( m_scissorWidth );
}

int Camera::getScissorHeight()
{
	return( m_scissorHeight );
}

bool Camera::getScissorClearBG()
{
	return( m_scissorClearBG );
}

void Camera::activateScissor()
{
	if( !m_scissorActive )
		return;
	int* x = (int*)XeCore::Photon::XeRenderTargetGet( Global::use().engine->getRenderTarget(), XeCore::XE_RENDERTARGET_X );
	int* y = (int*)XeCore::Photon::XeRenderTargetGet( Global::use().engine->getRenderTarget(), XeCore::XE_RENDERTARGET_Y );
	int* w = (int*)XeCore::Photon::XeRenderTargetGet( Global::use().engine->getRenderTarget(), XeCore::XE_RENDERTARGET_WIDTH );
	int* h = (int*)XeCore::Photon::XeRenderTargetGet( Global::use().engine->getRenderTarget(), XeCore::XE_RENDERTARGET_HEIGHT );
	int _x = *x;
	int _y = *y;
	int _w = *w;
	int _h = *h;
	*x = m_scissorX;
	*y = _h - m_scissorY - m_scissorHeight;
	*w = m_scissorWidth;
	*h = m_scissorHeight;
	XeCore::Photon::XeRenderTargetActivate( Global::use().engine->getRenderTarget() );
	XeCore::XeSetState( XeCore::XE_RENDER_SCISSOR_MODE, XeCore::XE_TRUE );
	XeCore::XeSetState( XeCore::XE_RENDER_SCISSOR, *x, *y, *w, *h );
	*x = _x;
	*y = _y;
	*w = _w;
	*h = _h;
	if( m_scissorClearBG )
		XeCore::Photon::XeRenderScene( XE_FLAG_COLORBUFF );
}

void Camera::unactivateScissor()
{
	XeCore::XeSetState( XeCore::XE_RENDER_SCISSOR_MODE, XeCore::XE_FALSE );
}