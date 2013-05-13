#include "Texture.h"
#include "Asset.h"
#include "TextureManager.h"

#include "GdiPlus.h"
#pragma comment(lib,"GdiPlus.lib")

using namespace Gdiplus;

RTTI_CLASS_DERIVATIONS(	Texture,
						RTTI_DERIVATION( Asset ),
						RTTI_DERIVATIONS_END
						);

Texture::Texture():
RTTI_CLASS_DEFINE( Texture ),
m_type( tCount ),
m_attached( false )
{
	XeCore::Photon::XeTextureCreate( &m_texture );
}

Texture::Texture( const XeCore::Photon::XeElmTexture& texture ):
RTTI_CLASS_DEFINE( Texture ),
m_type( tCount ),
m_attached( true )
{
	m_texture = texture;
	m_type = XeCore::Photon::XeTextureType( m_texture ) == XeCore::XE_DATA ? tData : t2d;
}

Texture::~Texture()
{
	if( !m_attached )
		XeCore::Photon::XeTextureDestroy( m_texture );
	m_texture.Unref();

	Asset::release( this );
}

bool Texture::load( const char* fname )
{
	if( m_attached )
		return( false );
	if( XeCore::Photon::XeTextureLoad( m_texture, const_cast<char*>(fname), true ) )
	{
		m_type = t2d;
		return( true );
	}
	return( false );
}

bool Texture::loadImage( const char* fname )
{
	if( m_attached )
		return( false );
	XeCore::XeString str( const_cast<char*>(fname) );
	wchar_t name[ 1024 ] = { 0 };
	str.GetUnicode( name, 1024 );
	bool status = false;
	ULONG_PTR gptoken = 0;
	Gdiplus::GdiplusStartupInput gpsi;
	Gdiplus::GdiplusStartup( &gptoken, &gpsi, NULL );
	Bitmap* image = new Bitmap( name );
	BitmapData data;
	Rect rect( 0, 0, (int)image->GetWidth(), (int)image->GetHeight() );
	if( !image->LockBits( &rect, ImageLockModeWrite | ImageLockModeRead, PixelFormat32bppARGB, &data ) )
	{
		unsigned char* pos = (unsigned char*)data.Scan0;
		unsigned char col[ 4 ] = { 0 };
		for( unsigned int p = 0; p < image->GetWidth() * image->GetHeight(); p++ )
		{
			col[ 0 ] = pos[ 2 ];
			col[ 1 ] = pos[ 1 ];
			col[ 2 ] = pos[ 0 ];
			col[ 3 ] = pos[ 3 ];
			*(unsigned int*)pos = *(unsigned int*)col;
			pos += 4;
		}
		status = XeCore::Photon::XeTextureLoadRGBAFromMemory( m_texture, data.Scan0, (int)image->GetWidth(), (int)image->GetHeight() );
		image->UnlockBits( &data );
	}
	delete image;
	Gdiplus::GdiplusShutdown( gptoken );
	str.Clear();
	return( status );
}

bool Texture::loadAppIcon( const char* fname, int index, int width, int height )
{
	if( m_attached )
		return( false );
	HICON icon = 0;
	unsigned int st = 0;
	if( !fname )
	{
		fname = new char[1024];
		GetModuleFileName( 0, const_cast<char*>(fname), 1024 );
		if( !PrivateExtractIcons( fname, index, width, height, &icon, &st, 1, 0 ) )
		{
			delete[] fname;
			return( false );
		}
		delete[] fname;
		fname = 0;
	}
	else
	if( !PrivateExtractIcons( fname, index, width, height, &icon, &st, 1, 0 ) )
		return( false );
	if( st == (unsigned int)-1 )
		return( false );
	bool status = false;
	ULONG_PTR gptoken = 0;
	Gdiplus::GdiplusStartupInput gpsi;
	Gdiplus::GdiplusStartup( &gptoken, &gpsi, NULL );
	Bitmap* image = new Bitmap( icon );
	BitmapData data;
	Rect rect( 0, 0, (int)image->GetWidth(), (int)image->GetHeight() );
	if( !image->LockBits( &rect, ImageLockModeWrite | ImageLockModeRead, PixelFormat32bppARGB, &data ) )
	{
		unsigned char* pos = (unsigned char*)data.Scan0;
		unsigned char col[ 4 ] = { 0 };
		for( unsigned int p = 0; p < image->GetWidth() * image->GetHeight(); p++ )
		{
			col[ 0 ] = pos[ 2 ];
			col[ 1 ] = pos[ 1 ];
			col[ 2 ] = pos[ 0 ];
			col[ 3 ] = pos[ 3 ];
			*(unsigned int*)pos = *(unsigned int*)col;
			pos += 4;
		}
		status = XeCore::Photon::XeTextureLoadRGBAFromMemory( m_texture, data.Scan0, (int)image->GetWidth(), (int)image->GetHeight() );
		image->UnlockBits( &data );
	}
	delete image;
	Gdiplus::GdiplusShutdown( gptoken );
	DestroyIcon( icon );
	return( status );
}

bool Texture::empty( int w, int h )
{
	if( m_attached )
		return( false );
	if( w <= 0 || h <= 0 )
		return( false );
	if( XeCore::Photon::XeTextureLoadEmpty( m_texture, w, h, true ) )
	{
		m_type = t2d;
		return( true );
	}
	return( false );
}

bool Texture::data( int w, int h, void* data )
{
	if( m_attached )
		return( false );
	if( w <= 0 || h <= 0 )
		return( false );
	if( data )
	{
		if( XeCore::Photon::XeTextureLoadData( m_texture, data, w, h ) )
		{
			m_type = tData;
			return( true );
		}
	}
	else
	{
		if( XeCore::Photon::XeTextureLoadEmptyData( m_texture, w, h ) )
		{
			m_type = tData;
			return( true );
		}
	}
	return( false );
}

bool Texture::free()
{
	if( m_attached )
		return( false );
	if( m_texture.IsEmpty() )
		return( false );
	XeCore::Photon::XeTextureDestroy( m_texture );
	m_texture.Unref();
	XeCore::Photon::XeTextureCreate( &m_texture );
	m_type = tCount;
	return( true );
}

bool Texture::filtering( int level )
{
	if( level == 0 )
	{
		activate();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_NEAREST );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_NEAREST );
		unactivate();
		return( true );
	}
	else
	if( level == 1 )
	{
		activate();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		unactivate();
		return( true );
	}
	else
	if( level == 2 )
	{
		activate();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_NEAREST_MIPMAP_LINEAR );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		unactivate();
		return( true );
	}
	else
	if( level == 3 )
	{
		activate();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR_MIPMAP_NEAREST );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		unactivate();
		return( true );
	}
	else
	if( level == 4 )
	{
		activate();
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MIN_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR_MIPMAP_LINEAR );
		XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_MAG_FILTER, XeCore::XE_TEXTURE_PARAM_LINEAR );
		unactivate();
		return( true );
	}
	else
		return( false );
}

void Texture::repeating( bool mode )
{
	activate();
	XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_WRAP_S, float( mode ? XeCore::XE_TEXTURE_PARAM_REPEAT : XeCore::XE_TEXTURE_PARAM_CLAMP ) );
	XeCore::Photon::XeTextureParameter( XeCore::XE_TEXTURE_PARAM_WRAP_T, float( mode ? XeCore::XE_TEXTURE_PARAM_REPEAT : XeCore::XE_TEXTURE_PARAM_CLAMP ) );
	unactivate();
}

int Texture::getWidth()
{
	if( m_texture.IsEmpty() )
		return( -1 );
	return( *(int*)XeCore::Photon::XeTextureGet( m_texture, XeCore::XE_TEXTURE_WIDTH ) );
}

int Texture::getHeight()
{
	if( m_texture.IsEmpty() )
		return( -1 );
	return( *(int*)XeCore::Photon::XeTextureGet( m_texture, XeCore::XE_TEXTURE_HEIGHT ) );
}

int Texture::getRealWidth()
{
	if( m_texture.IsEmpty() )
		return( -1 );
	return( XeCore::Photon::XeTextureGetReal( m_texture, XeCore::XE_TEXTURE_WIDTH ) );
}

int Texture::getRealHeight()
{
	if( m_texture.IsEmpty() )
		return( -1 );
	return( XeCore::Photon::XeTextureGetReal( m_texture, XeCore::XE_TEXTURE_HEIGHT ) );
}

Texture::Type Texture::getType()
{
	return( m_type );
}

bool Texture::activate()
{
	return( XeCore::Photon::XeTextureActivate( m_texture ) );
}

const XeCore::Photon::XeElmTexture& Texture::getTexture()
{
	return( m_texture );
}

bool Texture::isAttached()
{
	return( m_attached );
}

void Texture::unactivate()
{
	return( XeCore::Photon::XeTextureUnactivate( m_texture ) );
}

Asset* Texture::onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways )
{
	Texture* t = xnew Texture();
	bool s = false;
	if( params[ "type" ].getValue() == "image" )
		s = t->loadImage( params[ "path" ].getValue() );
	else
	if( params[ "type" ].getValue() == "appIcon" )
	{
		int i( 0 ), w( 0 ), h( 0 );
		params[ "iconIndex" ].getValue().Convert( &i, 'i' );
		params[ "iconWidth" ].getValue().Convert( &w, 'i' );
		params[ "iconHeight" ].getValue().Convert( &h, 'i' );
		s = t->loadAppIcon( params[ "path" ].getValue(), i, w, h );
	}
	else
		s = t->load( params[ "path" ].getValue() );
	if( s )
	{
		if( params.Exists( "filteringLevel" ) )
		{
			int flevel( 0 );
			params[ "filteringLevel" ].getValue().Convert( &flevel, 'i' );
			t->filtering( flevel );
		}
		if( params.Exists( "repeating" ) )
			t->repeating( params[ "repeating" ].getValue() == "true" );
		if( Global::use().textures->attach( NameID( name ), t ) )
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
	{
		DELETE_OBJECT( t );
		return( 0 );
	}
}

void Texture::onUnload()
{
	Global::use().textures->detach( NameID( getAssetName() ) );
}