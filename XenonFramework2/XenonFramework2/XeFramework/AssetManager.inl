template< class T >
T* AssetManager::get( const char* name, bool keepAlways, SourceType type, SourceFormat format )
{
	for( XeCore::XeElementPointer< Asset* > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
		if( e()->m_name == const_cast<char*>(name) && IRtti::isType< T >( e() ) )
			return( static_cast< T* >(e()->getAssetPurePointer()) );
	if( type == stDefault )
		type = m_sourceType;
	if( format == sfDefault )
		format = m_sourceFormat;
	Asset* a( 0 );
	if( type == stFile )
	{
		XeCore::XeFile f;
		XeCore::XeString t;
		t.Format( "%s\\%s", m_sourcePath.Get(), name );
		if( m_sourceSubPath.current() )
			t << "\\" << m_sourceSubPath.current()->Get();
		if( f.Load( t ) )
		{
			f.Seek( 0 );
			if( format == sfXml )
			{
				XeCore::XeMarkup m;
				if( m.Parse( static_cast<char*>( f.Data()), f.Size() ) )
				{
					if( !m( "Asset", "Type" ).IsEmpty() )
					{
						Asset::Params params;
						parseGroup( params, m( "Asset" ), m );
						a = T::onLoad( this, XeCore::XeString( const_cast<char*>(name) ), params, keepAlways );
						if( a )
						{
							XASSERT( a->m_purePointer, "Asset must have pure pointer not NULL" );
							a->m_name = const_cast<char*>(name);
							a->m_manager = this;
							a->m_loaded = true;
							a->m_level = keepAlways ? 0 : Global::use().manager->getStatesCount();
							if( !( IRtti::isType< T >( a ) && a->m_purePointer && IItemsManager< Asset >::attach( a ) ) )
								DELETE_OBJECT( a );
						}
						params.Clear();
					}
					m.Free();
				}
				else
				{
					XASSERT( 0, "Cannot parse XML asset file" );
					return( 0 );
				}
				f.Free();
			}
			else
			if( format == sfBinary )
			{
				Asset::Params params;
				if( AssetManager::readBinary( f, params ) )
				{
					a = T::onLoad( this, XeCore::XeString( const_cast<char*>(name) ), params, keepAlways );
					if( a )
					{
						XASSERT( a->m_purePointer, "Asset must have pure pointer not NULL" );
						a->m_name = const_cast<char*>(name);
						a->m_manager = this;
						a->m_loaded = true;
						a->m_level = keepAlways ? 0 : Global::use().manager->getStatesCount();
						if( !( IRtti::isType< T >( a ) && a->m_purePointer && IItemsManager< Asset >::attach( a ) ) )
							DELETE_OBJECT( a );
					}
					params.Clear();
				}
				else
				{
					XASSERT( 0, "Cannot read binary asset file" );
					return( 0 );
				}
			}
			else
			{
				XASSERT( 0, "Unknown asset format id: %i", format );
				return( 0 );
			}
		}
	}
	if( a )
		return( static_cast< T* >(a->getAssetPurePointer()) );
	XASSERT( a, "Asset '%s' does not exists", name );
	return( 0 );
}