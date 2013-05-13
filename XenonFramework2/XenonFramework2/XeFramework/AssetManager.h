#pragma once

#include "IRtti.h"
#include "IItemsManager.h"
#include "Asset.h"
#include "Manager.h"
#include "../XeCore/Base/XeMarkup.h"

class AssetManager : public virtual IRtti, public IItemsManager< Asset >, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( AssetManager );

	friend class Asset;

public:
	enum SourceType
	{
		stDefault,
		stFile,
		stCount
	};

	enum SourceFormat
	{
		sfDefault,
		sfXml,
		sfBinary,
		sfCount
	};

								AssetManager();
								~AssetManager();
	bool						setSource( const char* path, SourceType type = stFile );
	template< class T > T*		get( const char* name, bool keepAlways = false, SourceType type = stDefault, SourceFormat format = sfDefault );
	bool						release( const char* name );
	void						releaseLevel( unsigned int level );
	void						releaseAll();
	void						getInfoList( XeCore::XeString& out );
	bool						pushSubPath( const char* subpath );
	bool						popSubPath();

	static bool					readBinary( XeCore::XeFile& file, Asset::Params& params );
	static bool					writeBinary( XeCore::XeFile& file, Asset::Params& params );

	static const unsigned int	currentVersion = 1;

	static void					parseGroup( Asset::Params& params, XeCore::XeMarkup::Etag& tag, XeCore::XeMarkup& m );
	static void					parseGroup( Asset::Params& params, XeCore::XeFile& file );
	static void					makeGroup( Asset::Params& params, XeCore::XeFile& file );

private:
	SourceType					m_sourceType;
	SourceFormat				m_sourceFormat;
	XeCore::XeString			m_sourcePath;
	Stack< XeCore::XeString >	m_sourceSubPath;

protected:
	bool						attach( Asset* i ) { return( false ); };
	bool						detach( Asset* i ) { return( false ); };
	bool						remove( Asset* i ) { return( false ); };
};

#include "AssetManager.inl"