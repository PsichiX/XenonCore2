#pragma once

template< class T >
class Singleton
{
public:
	static T&	use();
	static void	destroy();

protected:
				Singleton() {}
				Singleton( const T& ) {}
				Singleton& operator= ( T const& ) {}

private:
	static T*	instance;
};

#include "Singleton.inl"
