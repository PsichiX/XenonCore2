#include "Canvas.h"
#include "Texture.h"
#include "Asset.h"
#include "CanvasManager.h"

RTTI_CLASS_DERIVATIONS(	Canvas,
						RTTI_DERIVATION( Asset ),
						RTTI_DERIVATIONS_END
						);

Canvas::Canvas( int w, int h, Type t ):
RTTI_CLASS_DEFINE( Canvas ),
m_type( t ),
m_clearOnActivate( false ),
m_depthTest( false )
{
	if( XeCore::Photon::XeFrameBufferCreate( &m_fbo, w, h, t == tData ? XeCore::XE_DATA : XeCore::XE_2D ) )
	{
		m_texture = *(XeCore::Photon::XeElmTexture*)XeCore::Photon::XeFrameBufferGet( m_fbo, XeCore::XE_FRAMEBUFFER_TEXTURE );
		m_textureDepth = *(XeCore::Photon::XeElmTexture*)XeCore::Photon::XeFrameBufferGet( m_fbo, XeCore::XE_FRAMEBUFFER_TEXTURE_DEPTH );
	}
}

Canvas::~Canvas()
{
	XeCore::Photon::XeFrameBufferDestroy( m_fbo );
	m_fbo.Unref();
	m_texture.Unref();
	m_textureDepth.Unref();

	Asset::release( this );
}

int Canvas::getWidth()
{
	if( m_fbo.IsEmpty() )
		return( -1 );
	return( *(int*)XeCore::Photon::XeFrameBufferGet( m_fbo, XeCore::XE_FRAMEBUFFER_WIDTH ) );
}

int Canvas::getHeight()
{
	if( m_fbo.IsEmpty() )
		return( -1 );
	return( *(int*)XeCore::Photon::XeFrameBufferGet( m_fbo, XeCore::XE_FRAMEBUFFER_HEIGHT ) );
}

Canvas::Type Canvas::getType()
{
	return( m_type );
}

bool Canvas::activate()
{
	if( XeCore::Photon::XeFrameBufferActivate( m_fbo ) )
	{
		if(m_depthTest)
			XeCore::XeSetState( XeCore::XE_RENDER_DEPTH_TEST, XeCore::XE_TRUE );
		if( m_clearOnActivate )
			XeCore::Photon::XeRenderScene( XE_FLAG_COLORBUFF | XE_FLAG_DEPTHBUFF );
		return( true );
	}
	return( false );
}

bool Canvas::unactivate()
{
	XeCore::XeSetState( XeCore::XE_RENDER_DEPTH_TEST, XeCore::XE_FALSE );
	return( XeCore::Photon::XeFrameBufferUnactivate( m_fbo ) );
}

bool Canvas::activateTexture()
{
	return( XeCore::Photon::XeFrameBufferActivateTexture( m_fbo ) );
}

bool Canvas::unactivateTexture()
{
	return( XeCore::Photon::XeFrameBufferUnactivateTexture( m_fbo ) );
}

bool Canvas::activateTextureDepth()
{
	return( XeCore::Photon::XeFrameBufferActivateTextureDepth( m_fbo ) );
}

bool Canvas::unactivateTextureDepth()
{
	return( XeCore::Photon::XeFrameBufferUnactivateTextureDepth( m_fbo ) );
}

const XeCore::Photon::XeElmTexture& Canvas::getTexture()
{
	return( m_texture );
}

const XeCore::Photon::XeElmTexture& Canvas::getTextureDepth()
{
	return( m_textureDepth );
}

const XeCore::Photon::XeElmFrameBuffer& Canvas::getFBO()
{
	return( m_fbo );
}

void Canvas::setClearOnActivate( bool mode )
{
	m_clearOnActivate = mode;
}

bool Canvas::getClearOnActivate()
{
	return( m_clearOnActivate );
}

void Canvas::setDepthMode( bool m )
{
	m_depthTest = m;
}

bool Canvas::getDepthMode()
{
	return( m_depthTest );
}

bool Canvas::filtering( int level )
{
	if( level == 0 )
	{
		activateTexture();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_NEAREST );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_NEAREST );
		unactivateTexture();
		return( true );
	}
	else
	if( level == 1 )
	{
		activateTexture();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		unactivateTexture();
		return( true );
	}
	else
	if( level == 2 )
	{
		activateTexture();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_NEAREST_MIPMAP_LINEAR );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		unactivateTexture();
		return( true );
	}
	else
	if( level == 3 )
	{
		activateTexture();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR_MIPMAP_NEAREST );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		unactivateTexture();
		return( true );
	}
	else
	if( level == 4 )
	{
		activateTexture();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR_MIPMAP_LINEAR );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		unactivateTexture();
		return( true );
	}
	else
		return( false );
}

void Canvas::repeating( bool mode )
{
	activateTexture();
	XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_WRAP_S, float( mode ? XeCore::XE_TEXTURE_PARAM_REPEAT : XeCore::XE_TEXTURE_PARAM_CLAMP ) );
	XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_WRAP_T, float( mode ? XeCore::XE_TEXTURE_PARAM_REPEAT : XeCore::XE_TEXTURE_PARAM_CLAMP ) );
	unactivateTexture();
}

bool Canvas::filteringDepth( int level )
{
	if( level == 0 )
	{
		activateTextureDepth();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_NEAREST );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_NEAREST );
		unactivateTextureDepth();
		return( true );
	}
	else
	if( level == 1 )
	{
		activateTextureDepth();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		unactivateTextureDepth();
		return( true );
	}
	else
	if( level == 2 )
	{
		activateTextureDepth();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_NEAREST_MIPMAP_LINEAR );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		unactivateTextureDepth();
		return( true );
	}
	else
	if( level == 3 )
	{
		activateTextureDepth();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR_MIPMAP_NEAREST );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		unactivateTextureDepth();
		return( true );
	}
	else
	if( level == 4 )
	{
		activateTextureDepth();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR_MIPMAP_LINEAR );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		unactivateTextureDepth();
		return( true );
	}
	else
		return( false );
}

void Canvas::repeatingDepth( bool mode )
{
	activateTextureDepth();
	XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_WRAP_S, float( mode ? XeCore::XE_TEXTURE_PARAM_REPEAT : XeCore::XE_TEXTURE_PARAM_CLAMP ) );
	XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_WRAP_T, float( mode ? XeCore::XE_TEXTURE_PARAM_REPEAT : XeCore::XE_TEXTURE_PARAM_CLAMP ) );
	unactivateTextureDepth();
}

Asset* Canvas::onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways )
{
	int w( 0 ), h( 0 );
	Canvas::Type type = Canvas::t2d;
	if( params.Exists( "width" ) )
		params[ "width" ].getValue().Convert( &w, 'i' );
	if( params.Exists( "height" ) )
		params[ "height" ].getValue().Convert( &h, 'i' );
	if( params.Exists( "type" ) && params[ "type" ].getValue() == "data" )
		type = Canvas::tData;
	Canvas* t = xnew Canvas( w, h, type );
	if( params.Exists( "depthMode" ) )
		t->setDepthMode( params[ "depthMode" ].getValue() == "true" );
	if( params.Exists( "clearOnActivate" ) )
		t->setClearOnActivate( params[ "clearOnActivate" ].getValue() == "true" );
	if( params.Exists( "textureColorFilteringLevel" ) )
	{
		int flevel( 0 );
		params[ "textureColorFilteringLevel" ].getValue().Convert( &flevel, 'i' );
		t->filtering( flevel );
	}
	if( params.Exists( "textureColorRepeating" ) )
		t->repeating( params[ "textureColorRepeating" ].getValue() == "true" );
	if( params.Exists( "textureDepthFilteringLevel" ) )
	{
		int flevel( 0 );
		params[ "textureDepthFilteringLevel" ].getValue().Convert( &flevel, 'i' );
		t->filteringDepth( flevel );
	}
	if( params.Exists( "textureDepthRepeating" ) )
		t->repeatingDepth( params[ "textureDepthRepeating" ].getValue() == "true" );
	if( Global::use().canvases->attach( NameID( name ), t ) )
	{
		ASSET_SET_PURE_POINTER( t );
		return( t );
	}
	else
	{
		DELETE_OBJECT( t );
		return( 0 );
	}
}

void Canvas::onUnload()
{
	Global::use().canvases->detach( NameID( getAssetName() ) );
}

Canvas::Canvas():
RTTI_CLASS_DEFINE( Canvas )
{
}