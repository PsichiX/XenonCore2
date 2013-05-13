template< class T >
Stack< T >::Stack()
{
}

template< class T >
Stack< T >::~Stack()
{
	m_items.Clear();
}

template< class T >
bool Stack< T >::push( T* item )
{
	if( !item )
		return( false );
	m_items.AddPointer( item );
	return( true );
}

template< class T >
bool Stack< T >::pop()
{
	if( !m_items.Size() )
		return( false );
	m_items.ErasePointer( m_items.LastPointer() );
	return( true );
}

template< class T >
T* Stack< T >::current()
{
	if( !m_items.Size() )
		return( 0 );
	return( m_items.LastPointer()() );
}

template< class T >
unsigned int Stack< T >::count()
{
	return( m_items.Size() );
}
