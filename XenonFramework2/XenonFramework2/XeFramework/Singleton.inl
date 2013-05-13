#include "MemoryManager.h"

template< class T >
T* Singleton< T >::instance = 0;

template< class T >
T& Singleton< T >::use()
{
	if( !Singleton< T >::instance )
#if defined( XMM_MEMORY_TRACING_MODE )
		Singleton< T >::instance = MemoryManager::__newDebug< T >( __FILE__, __LINE__ );
#else
		Singleton< T >::instance = MemoryManager::__new< T >();
#endif
	return( *Singleton< T >::instance );
}

template< class T >
void Singleton< T >::destroy()
{
	if( Singleton< T >::instance )
	{
#if defined( XMM_MEMORY_TRACING_MODE )
		MemoryManager::__deleteDebug< T >( Singleton< T >::instance );
#else
		MemoryManager::__delete< T >( Singleton< T >::instance );
#endif
		Singleton< T >::instance = 0;
	}
}