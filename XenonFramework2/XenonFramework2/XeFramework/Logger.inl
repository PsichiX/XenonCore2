#include <stdarg.h>

void Logger::setup( const char* fname )
{
	m_fname = fname;
	fopen_s( &m_fstdout, m_fname, "w" );
}

void Logger::log( const char* format, ... )
{
	if( !m_fstdout )
		fopen_s( &m_fstdout, m_fname, "w" );
	va_list vl;
	va_start( vl, format );
	vprintf( format, vl );
	va_end( vl );
	if( m_fstdout )
	{
		va_start( vl, format );
		vfprintf( m_fstdout, format, vl );
		va_end( vl );
	}
}

void Logger::lognl( const char* format, ... )
{
	if( !m_fstdout )
		fopen_s( &m_fstdout, m_fname, "w" );
	va_list vl;
	va_start( vl, format );
	vprintf( format, vl );
	va_end( vl );
	printf( "\n" );
	if( m_fstdout )
	{
		va_start( vl, format );
		vfprintf( m_fstdout, format, vl );
		va_end( vl );
		fprintf( m_fstdout, "\n" );
	}
}