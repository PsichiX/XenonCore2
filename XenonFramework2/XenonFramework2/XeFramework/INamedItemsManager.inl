template< class N, class T >
INamedItemsManager< N, T >::INamedItemsManager()
{
}

template< class N, class T >
INamedItemsManager< N, T >::~INamedItemsManager()
{
	m_items.Clear();
}

template< class N, class T >
bool INamedItemsManager< N, T >::attach( N& name, T* item )
{
	if( !item )
		return( false );
	m_items.AddPointer( Pair( name, item ) );
	return( true );
}

template< class N, class T >
bool INamedItemsManager< N, T >::detach( N& name )
{
	for( Element e = m_items.FirstPointer(); !e.IsEmpty(); e.Next() )
		if( e().key == name )
		{
			m_items.ErasePointer( e );
			return( true );
		}
	return( false );
}

template< class N, class T >
bool INamedItemsManager< N, T >::remove( N& name )
{
	T* item = find( name );
	if( item && detach( name ) )
	{
		DELETE_OBJECT( item );
		return( true );
	}
	return( false );
}

template< class N, class T >
void INamedItemsManager< N, T >::free()
{
	m_items.Clear();
}

template< class N, class T >
T* INamedItemsManager< N, T >::find( N& name )
{
	for( Element e = m_items.FirstPointer(); !e.IsEmpty(); e.Next() )
		if( name == e().key )
			return( e().value );
	return( 0 );
}

template< class N, class T >
bool INamedItemsManager< N, T >::findName( T* ptr, N& name )
{
	for( Element e = m_items.FirstPointer(); !e.IsEmpty(); e.Next() )
		if( ptr == e().value )
		{
			name = e().key;
			return( true );
		}
	return( false );
}

template< class N, class T >
XeCore::XeElements< typename INamedItemsManager< N, T >::Pair >& INamedItemsManager< N, T >::access()
{
	return( m_items );
}
