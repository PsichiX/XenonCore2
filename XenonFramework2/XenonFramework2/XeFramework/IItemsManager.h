#pragma once

#include "../XeCore/Base/XeElements.h"
#include "../XeCore/Base/XeSmart.h"

template< class T >
class IItemsManager
{
public:
													IItemsManager();
													~IItemsManager();
	bool											attach( T* item );
	bool											detach( T* item );
	bool											remove( T* item );
	XeCore::XeElements< T* >&						access();
	virtual void									getInfoList( XeCore::XeString& out ) { out = "< info listing not implemented >"; }

	typedef XeCore::XeElementPointer< T* > Element;

private:
	XeCore::XeElements< T* >						m_items;
};

#include "IItemsManager.inl"