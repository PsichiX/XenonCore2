#include "Logger.h"

Logger::Logger():
m_fstdout( 0 ),
m_fname( "XeFramework2.log" )
{
}

Logger::~Logger()
{
	fflush( m_fstdout );
	fclose( m_fstdout );
}