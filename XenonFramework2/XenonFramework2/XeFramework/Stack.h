#pragma once

#include "../XeCore/Base/XeElements.h"

template< class T >
class Stack : public MemoryManager::Manageable
{
public:
								Stack();
								~Stack();
	bool						push( T* item );
	bool						pop();
	T*							current();
	unsigned int				count();

private:
	XeCore::XeElements< T* >	m_items;
};

#include "Stack.inl"