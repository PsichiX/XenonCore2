#pragma once

#include "Singleton.h"
#include <iostream>

#define FORCEINLINE	__forceinline

class Logger : public Singleton< Logger >
{
public:
						Logger();
						~Logger();
	FORCEINLINE void	setup( const char* fname );
	FORCEINLINE void	log( const char* format, ... );
	FORCEINLINE void	lognl( const char* format, ... );

private:
	FILE*				m_fstdout;
	const char*			m_fname;
};

#include "Logger.inl"