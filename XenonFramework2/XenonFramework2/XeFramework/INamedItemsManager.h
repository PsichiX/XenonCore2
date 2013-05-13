#pragma once

#include "../XeCore/Base/XeElements.h"
#include "../XeCore/Base/XeSmart.h"

template< class N, class T >
class INamedItemsManager
{
public:
	struct Pair
	{
											Pair(){}
											Pair( N& k, T* v ) : key( k ), value( v ) {}
		N									key;
		T*									value;
	};

											INamedItemsManager();
											~INamedItemsManager();
	bool									attach( N& name, T* item );
	bool									detach( N& name );
	bool									remove( N& name );
	void									free();
	T*										find( N& name );
	bool									findName( T* ptr, N& name );
	XeCore::XeElements< typename Pair >&	access();
	virtual void							getInfoList( XeCore::XeString& out ) { out = "< info listing not implemented >"; }

	typedef XeCore::XeElementPointer< typename Pair > Element;

private:
	XeCore::XeElements< typename Pair >		m_items;
};

#include "INamedItemsManager.inl"