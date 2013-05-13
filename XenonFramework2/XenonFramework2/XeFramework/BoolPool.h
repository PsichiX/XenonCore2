#pragma once

#include "Base.h"

template< int Capacity >
class BoolPool
{
public:
						BoolPool();
						~BoolPool();
	FORCEINLINE void	set( int id, bool v );
	FORCEINLINE void	toggle( int id );
	FORCEINLINE bool	get( int id );

	FORCEINLINE void	operator() ( int id, bool v );
	FORCEINLINE bool	operator[] ( int id );

private:
	unsigned char		m_pool[ ( Capacity / 8 ) + 1 ];
};

#include "BoolPool.inl"