#include "AssetManager.h"
#include "Stack.h"
#include "../XeCore/Base/XeFile.h"
#include "../XeCore/Base/XeMarkup.h"

RTTI_CLASS_DERIVATIONS(	AssetManager,
						RTTI_DERIVATIONS_END
						);

AssetManager::AssetManager():
RTTI_CLASS_DEFINE( AssetManager ),
m_sourcePath( "." ),
m_sourceType( stFile ),
m_sourceFormat( sfXml )
{
}

AssetManager::~AssetManager()
{
	releaseAll();
	while( m_sourceSubPath.count() )
	{
		XeCore::XeString* t = m_sourceSubPath.current();
		DELETE_OBJECT( t );
		m_sourceSubPath.pop();
	}
}

bool AssetManager::setSource( const char* path, SourceType type )
{
	if( !path || type < 0 || type >= stCount )
		return( false );
	m_sourcePath = const_cast<char*>(path);
	m_sourceType = type;
	return( true );
}

bool AssetManager::release( const char* name )
{
	return( false );
}

void AssetManager::releaseLevel( unsigned int level )
{
	bool doit = true;
	while( doit )
	{
		doit = false;
		for( XeCore::XeElementPointer< Asset* > e = access().FirstPointer(); !e.IsEmpty(); )
		{
			if( e()->m_level >= level )
			{
				IItemsManager< Asset >::remove( e() );
				doit = true;
				break;
			}
			else
				e.Next();
		}
	}
}

void AssetManager::releaseAll()
{
	XeCore::XeElementPointer< Asset* > e = IItemsManager< Asset >::access().FirstPointer();
	while( !e.IsEmpty() )
	{
		IItemsManager< Asset >::remove( e() );
		e = IItemsManager< Asset >::access().FirstPointer();
	}
}

void AssetManager::getInfoList( XeCore::XeString& out )
{
	for( XeCore::XeElementPointer< Asset* > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
	{
		XeCore::XeString n, a;
		n = e()->getAssetName();
		a.Format( "0x%p", e() );
		out << a << " <" << const_cast<char*>(e()->getName()) << ">: " << n << " -> Level: " << e()->getAssetLevel() << "\n";
	}
}

bool AssetManager::pushSubPath( const char* subpath )
{
	return( m_sourceSubPath.push( new XeCore::XeString( const_cast<char*>(subpath) ) ) );
}

bool AssetManager::popSubPath()
{
	XeCore::XeString* t = m_sourceSubPath.current();
	DELETE_OBJECT( t );
	return( m_sourceSubPath.pop() );
}

bool AssetManager::readBinary( XeCore::XeFile& file, Asset::Params& params )
{
	char header[ 3 ] = { 0, 0, 0 };
	file.Read( &header, sizeof( char ) * 3 );
	if( XeCore::XeString( "XAS" ) != header )
	{
		XASSERT( 0, "Wrong asset header" );
		return( false );
	}

	unsigned int version( 0 );
	file.Read( &version, sizeof( unsigned int ) );
	if( !version )
	{
		XASSERT( 0, "Wrong asset version" );
		return( false );
	}

	parseGroup( params, file );
	return( true );
}

bool AssetManager::writeBinary( XeCore::XeFile& file, Asset::Params& params )
{
	char header[ 3 ] = { 'X', 'A', 'S' };
	file.Write( &header, sizeof( char ) * 3 );

	unsigned int version( currentVersion );
	file.Write( &version, sizeof( unsigned int ) );

	makeGroup( params, file );
	return( true );
}

void AssetManager::parseGroup( Asset::Params& params, XeCore::XeMarkup::Etag& tag, XeCore::XeMarkup& m )
{
	for( XeCore::XeMarkup::Etag e = tag->FirstChild(); !e.IsEmpty(); e.Next() )
	{
		if( e()->Name == "Param" )
		{
			Asset::ParamData& p = params[ m( ".", "Name", XeCore::XeMarkup::CREATE, e.iPointer() )->Value ];
			p.setValue( m( ".", "Name", XeCore::XeMarkup::CREATE, e.iPointer() )->Value, m( ".", "Value", XeCore::XeMarkup::CREATE, e.iPointer() )->Value );
		}
		else
		if( e()->Name == "Group" )
		{
			Asset::ParamData& p = params[ m( ".", "Name", XeCore::XeMarkup::CREATE, e.iPointer() )->Value ];
			p.setParams( m( ".", "Name", XeCore::XeMarkup::CREATE, e.iPointer() )->Value, m( ".", "Type", XeCore::XeMarkup::CREATE, e.iPointer() )->Value );
			parseGroup( p.getParams(), e, m );
		}
	}
}

void AssetManager::parseGroup( Asset::Params& params, XeCore::XeFile& file )
{
	unsigned char t = 3;
	while( t != 0 )
	{
		file.Read( &t, sizeof( unsigned char ) );
		if( t == 1 )
		{
			XeCore::XeString name, value;
			file.ReadString( name, true );
			file.ReadString( value, true );
			Asset::ParamData& p = params[ name ];
			p.setValue( name, value );
		}
		else
		if( t == 2 )
		{
			XeCore::XeString name, type;
			file.ReadString( name, true );
			file.ReadString( type, true );
			Asset::ParamData& p = params[ name ];
			p.setParams( name, type );
			parseGroup( params, file );
		}
	}
}

void AssetManager::makeGroup( Asset::Params& params, XeCore::XeFile& file )
{
	unsigned char t = 0;
	for( Asset::ParamsElm e = params.FirstPointer(); !e.IsEmpty(); e.Next() )
	{
		if( e->Value.getType() == Asset::ParamData::tValue )
		{
			t = 1;
			file.Write( &t, sizeof( unsigned char ) );
			file.WriteString( e->Value.getName(), true );
			file.WriteString( e->Value.getValue(), true );
		}
		else
		if( e->Value.getType() == Asset::ParamData::tParams )
		{
			t = 2;
			file.Write( &t, sizeof( unsigned char ) );
			file.WriteString( e->Value.getName(), true );
			file.WriteString( e->Value.getGroupType(), true );
			makeGroup( e->Value.getParams(), file );
		}
	}
	t = 0;
	file.Write( &t, sizeof( unsigned char ) );
}
