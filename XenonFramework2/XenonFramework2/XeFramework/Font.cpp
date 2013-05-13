#include "Font.h"
#include "FontManager.h"
#include "Asset.h"

RTTI_CLASS_DERIVATIONS(	Font,
						RTTI_DERIVATION( Asset ),
						RTTI_DERIVATIONS_END
						);

Font::Font():
RTTI_CLASS_DEFINE( Font ),
m_map( 0 )
{
}

Font::~Font()
{
	free();

	Asset::release( this );
}

bool Font::load( const char* fname )
{
	m_map = new XeCore::XeFontmap();
	if( m_map )
	{
		if( m_map->Compile( (char*)fname ) )
			return( true );
		else
			free();
	}
	return( false );
}

bool Font::loadFromMemory( void* data, unsigned int size )
{
	m_map = new XeCore::XeFontmap();
	if( m_map )
	{
		if( m_map->CompileFromMemory( data, size ) )
			return( true );
		else
			free();
	}
	return( false );
}

bool Font::isValid()
{
	return( m_map ? true : false );
}

void Font::free()
{
	DELETE_OBJECT( m_map );
}

bool Font::getCharacter( int id, XeCore::XeHalfVector& coordsB, XeCore::XeHalfVector& coordsE, XeCore::XeHalfVector& offset, XeCore::XeHalfVector& size, float& advance )
{
	if( !m_map || id <= 0 || id > 255 )
		return( false );
	size.X = m_map->Desc[ id ].Width;
	size.Y = m_map->Desc[ id ].Height;
	offset.X = m_map->Desc[ id ].Xoffset;
	offset.Y = m_map->Desc[ id ].Yoffset;
	advance = m_map->Desc[ id ].Advance;
	coordsB.X = m_map->Desc[ id ].Xbegin;
	coordsB.Y = m_map->Desc[ id ].Ybegin;
	coordsE.X = m_map->Desc[ id ].Xend;
	coordsE.Y = m_map->Desc[ id ].Yend;
	return( true );
}

float Font::getSize()
{
	return( m_map ? m_map->Size : 0.0f );
}

Asset* Font::onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways )
{
	Font* t = xnew Font();
	if( t->load( params[ "path" ].getValue() ) )
	{
		if( Global::use().fonts->attach( NameID( name ), t ) )
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

void Font::onUnload()
{
	Global::use().fonts->detach( NameID( getAssetName() ) );
}
