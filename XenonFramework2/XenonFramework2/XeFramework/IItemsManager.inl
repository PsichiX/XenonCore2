template< class T >
IItemsManager< T >::IItemsManager()
{
}

template< class T >
IItemsManager< T >::~IItemsManager()
{
	m_items.Clear();
}

template< class T >
bool IItemsManager< T >::attach( T* item )
{
	if( !item )
		return( false );
	m_items.AddPointer( item );
	return( true );
}

template< class T >
bool IItemsManager< T >::detach( T* item )
{
	if( !item )
		return( false );
	for( Element e = m_items.FirstPointer(); !e.IsEmpty(); e.Next() )
		if( e() == item )
		{
			m_items.ErasePointer( e );
			return( true );
		}
	return( false );
}

template< class T >
bool IItemsManager< T >::remove( T* item )
{
	if( detach( item ) )
	{
		DELETE_OBJECT( item );
		return( true );
	}
	return( false );
}

template< class T >
XeCore::XeElements< T* >& IItemsManager< T >::access()
{
	return( m_items );
}
