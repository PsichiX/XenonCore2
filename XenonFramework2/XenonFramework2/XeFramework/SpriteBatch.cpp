#include "SpriteBatch.h"
#include "Asset.h"
#include "SceneManager.h"
#include "AssetManager.h"
#include "Camera2D.h"

RTTI_CLASS_DERIVATIONS(	SpriteBatch,
						RTTI_DERIVATION( Asset ),
						RTTI_DERIVATION( ShapePool ),
						RTTI_DERIVATIONS_END
						);

SpriteBatch::SpriteBatch( unsigned int capacity, bool doublebuff ):
ShapePool( capacity * 4, doublebuff ),
RTTI_CLASS_DEFINE( SpriteBatch )
{
}

SpriteBatch::~SpriteBatch()
{
	Asset::release( this );
}

void SpriteBatch::update()
{
	ShapePool::swapBuffers();
	ShapePool::update();
	ShapePool::optimize();
	ShapePool::rebuildRenderQueue();
}

Asset* SpriteBatch::onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways )
{
	unsigned int capacity = 0;
	bool doublebuff = false;
	if( params.Exists( "capacity" ) )
		params[ "capacity" ].getValue().Convert( &capacity, 'd' );
	if( params.Exists( "doubleBuffer" ) )
		doublebuff = params[ "doubleBuffer" ].getValue() == "true";
	if( capacity )
	{
		SpriteBatch* t = xnew SpriteBatch( capacity, doublebuff );
		if( params.Exists( "camera" ) && params[ "camera" ].getType() == ParamData::tParams )
		{
			Params& cam = params[ "camera" ].getParams();
			float x( 0.0f ), y( 0.0f ), w( 1.0f ), h( 1.0f ), a( 0.0f );
			if( cam.Exists( "x" ) )
				cam[ "x" ].getValue().Convert( &x, 'h' );
			if( cam.Exists( "y" ) )
				cam[ "y" ].getValue().Convert( &y, 'h' );
			if( cam.Exists( "width" ) )
				cam[ "width" ].getValue().Convert( &w, 'h' );
			if( cam.Exists( "height" ) )
				cam[ "height" ].getValue().Convert( &h, 'h' );
			if( cam.Exists( "angle" ) )
				cam[ "angle" ].getValue().Convert( &a, 'h' );
			t->setCamera( xnew Camera2D( x, y, w, h, a ) );
		}
		if( params.Exists( "canvasAsset" ) )
			t->setCanvas( manager->get< Canvas >( params[ "canvasAsset" ].getValue(), keepAlways ) );
		if( Global::use().scenes->attach( NameID( name ), t ) )
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
	else
		return( 0 );
}

void SpriteBatch::onUnload()
{
	Global::use().scenes->detach( NameID( getAssetName() ) );
}

RTTI_CLASS_DERIVATIONS(	SpriteBatch::Sprite,
						RTTI_DERIVATION( ShapePool::Shape ),
						RTTI_DERIVATIONS_END
						);

SpriteBatch::Sprite::Sprite():
RTTI_CLASS_DEFINE( SpriteBatch::Sprite ),
m_width( 0.0f ),
m_height( 0.0f ),
m_xoffset( 0.0f ),
m_yoffset( 0.0f )
{
	setRenderMode( XeCore::XE_QUADS );
	reserve( 4 );
	access( 0 )->vertex.color = XeCore::XeHalfVector( 1.0f, 1.0f, 1.0f );
	access( 1 )->vertex.color = XeCore::XeHalfVector( 1.0f, 1.0f, 1.0f );
	access( 2 )->vertex.color = XeCore::XeHalfVector( 1.0f, 1.0f, 1.0f );
	access( 3 )->vertex.color = XeCore::XeHalfVector( 1.0f, 1.0f, 1.0f );
	access( 0 )->vertex.coords = XeCore::XeHalfVector( 0.0f, 0.0f );
	access( 1 )->vertex.coords = XeCore::XeHalfVector( 1.0f, 0.0f );
	access( 2 )->vertex.coords = XeCore::XeHalfVector( 1.0f, 1.0f );
	access( 3 )->vertex.coords = XeCore::XeHalfVector( 0.0f, 1.0f );
}

SpriteBatch::Sprite::~Sprite()
{
}

void SpriteBatch::Sprite::setColor( XeCore::XeHalfVector& col )
{
	access( 0 )->vertex.color = col;
	access( 1 )->vertex.color = col;
	access( 2 )->vertex.color = col;
	access( 3 )->vertex.color = col;
	setNeedUpdate( true );
}

XeCore::XeHalfVector& SpriteBatch::Sprite::getColor()
{
	return( access( 0 )->vertex.color );
}

void SpriteBatch::Sprite::setWidth( float v )
{
	m_width = v;
	rebuild();
}

float SpriteBatch::Sprite::getWidth()
{
	return( m_width );
}

void SpriteBatch::Sprite::setHeight( float v )
{
	m_height = v;
	rebuild();
}

float SpriteBatch::Sprite::getHeight()
{
	return( m_height );
}

void SpriteBatch::Sprite::setXoffset( float v )
{
	m_xoffset = v;
	rebuild();
}

float SpriteBatch::Sprite::getXoffset()
{
	return( m_xoffset );
}

void SpriteBatch::Sprite::setYoffset( float v )
{
	m_yoffset = v;
	rebuild();
}

float SpriteBatch::Sprite::getYoffset()
{
	return( m_yoffset );
}

void SpriteBatch::Sprite::flip( FlipType ft )
{
	if( ft == ftVertical )
	{
		float ta = access( 2 )->vertex.coords.Y;
		float tb = access( 3 )->vertex.coords.Y;
		access( 2 )->vertex.coords.Y = access( 1 )->vertex.coords.Y;
		access( 3 )->vertex.coords.Y = access( 0 )->vertex.coords.Y;
		access( 0 )->vertex.coords.Y = tb;
		access( 1 )->vertex.coords.Y = ta;
		setNeedUpdate( true );
	}
	else
	if( ft == ftHorizontal )
	{
		float ta = access( 0 )->vertex.coords.X;
		float tb = access( 3 )->vertex.coords.X;
		access( 0 )->vertex.coords.X = access( 1 )->vertex.coords.X;
		access( 3 )->vertex.coords.X = access( 2 )->vertex.coords.X;
		access( 2 )->vertex.coords.X = tb;
		access( 1 )->vertex.coords.X = ta;
		setNeedUpdate( true );
	}
}

void SpriteBatch::Sprite::rebuild()
{
	access( 0 )->vertex.position = XeCore::XeHalfVector( -m_xoffset, -m_yoffset );
	access( 1 )->vertex.position = XeCore::XeHalfVector( -m_xoffset + m_width, -m_yoffset );
	access( 2 )->vertex.position = XeCore::XeHalfVector( -m_xoffset + m_width, -m_yoffset + m_height );
	access( 3 )->vertex.position = XeCore::XeHalfVector( -m_xoffset, -m_yoffset + m_height );
	setNeedUpdate( true );
}

RTTI_CLASS_DERIVATIONS(	SpriteBatch::CanvasSprite,
						RTTI_DERIVATION( SpriteBatch::Sprite ),
						RTTI_DERIVATIONS_END
						);

SpriteBatch::CanvasSprite::CanvasSprite( Canvas* canvas, Effect* effect ):
RTTI_CLASS_DEFINE( SpriteBatch::CanvasSprite ),
m_texture( 0 ),
m_textureDepth( 0 ),
m_material( 0 )
{
	XASSERT( canvas, "Canvas cannot be NULL" );

	m_texture = xnew Texture( canvas->getTexture() );
	m_textureDepth = xnew Texture( canvas->getTextureDepth() );
	m_material = xnew Material();
	m_material->setTexture( m_texture, 0 );
	m_material->setTexture( m_textureDepth, 1 );
	m_material->setEffect( effect );
	setWidth( static_cast<float>(canvas->getWidth()) );
	setHeight( static_cast<float>(canvas->getHeight()) );
	setMaterial( m_material );
	flip( ftVertical );
}

SpriteBatch::CanvasSprite::~CanvasSprite()
{
	DELETE_OBJECT( m_texture );
	DELETE_OBJECT( m_textureDepth );
	DELETE_OBJECT( m_material );
}