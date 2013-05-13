#if defined( XMM_MEMORY_TRACING_MODE )
#define _CRTDBG_MAP_ALLOC
#endif
#define XMM_BLOCK_TYPE _NORMAL_BLOCK

#include "MemoryManager.h"
#include "Base.h"

MemoryManager::MemoryManager():
m_bytesize( 0 ),
m_itemsFirst( 0 ),
m_itemsLast( 0 ),
m_printableFirst( 0 ),
m_printableLast( 0 ),
m_printableCount( 0 ),
m_count( 0 )
{
}

MemoryManager::~MemoryManager()
{
	while( m_itemsLast )
	{
		void* p = m_itemsLast->data.pointer;
		remove( m_itemsLast );
#if defined( XMM_MEMORY_TRACING_MODE )
		MemoryManager::__deleteDebug( p );
#else
		MemoryManager::__delete( p );
#endif
	}
	while( m_printableFirst )
	{
		_removePrintable( m_printableFirst );
	}
}

void* MemoryManager::add( void* newobj, bool isarray, unsigned int bytesize, const char* tracefile, int traceline )
{
	if( !newobj || !bytesize )
		return( 0 );
	ListItem* e = _addItem();
	if( e )
	{
		e->data.pointer = newobj;
		e->data.isarray = isarray;
		e->data.bytesize = bytesize;
		m_bytesize += bytesize;
		e->data.tracefile = tracefile;
		e->data.traceline = traceline;
#if defined MEMORY_OBJECTS_LOG
		LOGNL( ">>> Add memory object: 0x%p; array: %s; bytes: %u; trace:\nFile: %s\nLine: %i", newobj, isarray ? "TRUE" : "FALSE", bytesize, tracefile, traceline );
#endif
	}
#if defined MEMORY_OBJECTS_LOG
	else
	{
		XPEDANTICWARNING( 0, "Cannot add memory object: 0x%p; array: %s; bytes: %u; trace:\nFile: %s\nLine: %i", newobj, isarray ? "TRUE" : "FALSE", bytesize, tracefile, traceline );
	}
#endif
	return( newobj );
}

MemoryManager::ListItem* MemoryManager::find( void* ptr )
{
	for( ListItem* l = m_itemsFirst; l; l = l->next )
		if( l->data.pointer == ptr )
			return( l );
	return( 0 );
}

void MemoryManager::remove( ListItem* item )
{
	if( item )
	{
		unsigned int bs = item->data.bytesize;
#if defined MEMORY_OBJECTS_LOG
		void* obj = item->data.pointer;
		bool isarray = item->data.isarray;
		unsigned int bytesize = item->data.bytesize;
		const char* tracefile = item->data.tracefile;
		int traceline = item->data.traceline;
#endif
		if( _removeItem( item ) )
		{
			m_bytesize -= bs;
#if defined MEMORY_OBJECTS_LOG
			LOGNL( ">>> Remove memory object: 0x%p; array: %s; bytes: %u; trace:\nFile: %s\nLine: %i", obj, isarray ? "TRUE" : "FALSE", bytesize, tracefile, traceline );
#endif
		}
#if defined MEMORY_OBJECTS_LOG
		else
		{
			XPEDANTICWARNING( 0, "Cannot remove memory object: 0x%p; array: %s; bytes: %u; trace:\nFile: %s\nLine: %i", obj, isarray ? "TRUE" : "FALSE", bytesize, tracefile, traceline );
		}
#endif
	}
}

bool MemoryManager::addPrintable( Printable* ptr )
{
	if( !ptr )
		return( false );
	ListPrintable* e = _addPrintable();
	if( e )
	{
		e->pointer = ptr;
		return( true );
	}
	return( false );
}

MemoryManager::ListPrintable* MemoryManager::findPrintable( Printable* ptr )
{
	for( ListPrintable* l = m_printableFirst; l; l = l->next )
		if( l->pointer == ptr )
			return( l );
	return( 0 );
}

void MemoryManager::removePrintable( Printable* ptr )
{
	if( ptr )
		_removePrintable( findPrintable( ptr ) );
}

unsigned int MemoryManager::getCount()
{
	return( m_count );
}

unsigned int MemoryManager::totalByteSize()
{
	return( m_bytesize );
}

MemoryManager::ListItem* MemoryManager::getFirst()
{
	return( m_itemsFirst );
}

bool MemoryManager::traceMemory( unsigned int listingDataBytes )
{
	LOGNL( "" );
	LOGNL( ">>>>>> Memory manager report:" );
	LOGNL( "Unreleased memory data pools: %u", m_count );
	LOGNL( "Unreleased memory data in bytes: %u", m_bytesize );
	LOGNL( "" );
#if defined( XMM_MEMORY_TRACING_MODE )
	for( ListItem* l = m_itemsFirst; l; l = l->next )
	{
		LOGNL( ">>>>>> Unreleased memory data pool allocated in file:" );
		LOGNL( "\"%s\"", l->data.tracefile );
		LOGNL( "at line: %i", l->data.traceline );
		LOGNL( "Size (in bytes): %u", l->data.bytesize );
		LOGNL( "Address: 0x%p", l->data.pointer );
		LOGNL( "Is array: %s", l->data.isarray ? "true" : "false" );
		if( listingDataBytes )
		{
			unsigned int bytes = listingDataBytes == -1 ? l->data.bytesize : min( listingDataBytes, l->data.bytesize );
			unsigned int lines = bytes / 8;
			unsigned int rest = bytes - ( lines * 8 );
			if( rest ) lines += 1;
			LOGNL( ">>>>>> Listing data bytes: %u", bytes );
			unsigned char* d = (unsigned char*)l->data.pointer;
			for( unsigned int i = 0; i < lines; i++, d += 8 )
			{
				if( i == lines - 1 )
				{
					if( rest == 0 ) LOGNL( "%14u: |%2c%2c%2c%2c%2c%2c%2c%2c| %02x %02x %02x %02x %02x %02x %02x %02x", i * 8, d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ], d[ 4 ], d[ 5 ], d[ 6 ], d[ 7 ], d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ], d[ 4 ], d[ 5 ], d[ 6 ], d[ 7 ] );
					else
					if( rest == 7 ) LOGNL( "%14u: |%2c%2c%2c%2c%2c%2c%2c  | %02x %02x %02x %02x %02x %02x %02x     ", i * 8, d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ], d[ 4 ], d[ 5 ], d[ 6 ], d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ], d[ 4 ], d[ 5 ], d[ 6 ] );
					else
					if( rest == 6 ) LOGNL( "%14u: |%2c%2c%2c%2c%2c%2c    | %02x %02x %02x %02x %02x %02x          ", i * 8, d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ], d[ 4 ], d[ 5 ], d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ], d[ 4 ], d[ 5 ] );
					else
					if( rest == 5 ) LOGNL( "%14u: |%2c%2c%2c%2c%2c      | %02x %02x %02x %02x %02x               ", i * 8, d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ], d[ 4 ], d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ], d[ 4 ] );
					else
					if( rest == 4 ) LOGNL( "%14u: |%2c%2c%2c%2c        | %02x %02x %02x %02x                    ", i * 8, d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ], d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ] );
					else
					if( rest == 3 ) LOGNL( "%14u: |%2c%2c%2c          | %02x %02x %02x                         ", i * 8, d[ 0 ], d[ 1 ], d[ 2 ], d[ 0 ], d[ 1 ], d[ 2 ] );
					else
					if( rest == 2 ) LOGNL( "%14u: |%2c%2c            | %02x %02x                              ", i * 8, d[ 0 ], d[ 1 ], d[ 0 ], d[ 1 ] );
					else
					if( rest == 1 ) LOGNL( "%14u: |%2c              | %02x                                   ", i * 8, d[ 0 ], d[ 0 ] );
				}
				else
					LOGNL( "%14u: |%2c%2c%2c%2c%2c%2c%2c%2c| %02x %02x %02x %02x %02x %02x %02x %02x", i * 8, d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ], d[ 4 ], d[ 5 ], d[ 6 ], d[ 7 ], d[ 0 ], d[ 1 ], d[ 2 ], d[ 3 ], d[ 4 ], d[ 5 ], d[ 6 ], d[ 7 ] );
			}
			LOGNL( ">>>>>> Listing data end" );
		}
		LOGNL( "" );
	}
#endif
	return( m_count ? true : false );
}

int MemoryManager::crtTraceMemory()
{
	return( _CrtDumpMemoryLeaks() );
}

bool MemoryManager::queryPrint( Query* query, unsigned int count )
{
	bool status( false );
#if defined( XMM_MEMORY_TRACING_MODE )
	LOGNL( ">>>>>> Memory manager query report:" );
	for( unsigned int i = 0; i < count; i++ )
	{
		if( query[ i ].type == qtIsArray )
			LOGNL( "* Is array: %s", query[ i ].value ? "True" : "False" );
		else
		if( query[ i ].type == qtByteSize )
			LOGNL( "* Byte size: %u", query[ i ].value );
		else
		if( query[ i ].type == qtFile )
			LOGNL( "* File: %s", query[ i ].value );
		else
		if( query[ i ].type == qtFile )
			LOGNL( "* Line: %i", query[ i ].value );
	}
	LOGNL( "" );
	for( ListItem* l = m_itemsFirst; l; l = l->next )
	{
		bool accept( true );
		for( unsigned int i = 0; i < count; i++ )
		{
			if( query[ i ].type == qtIsArray && ( l->data.isarray && query[ i ].value || !l->data.isarray && !query[ i ].value ) )
				accept = false;
			else
			if( query[ i ].type == qtByteSize && l->data.bytesize != (unsigned int)query[ i ].value )
				accept = false;
			else
			if( query[ i ].type == qtFile && l->data.tracefile != XeCore::XeString((char*)query[ i ].value) )
				accept = false;
			else
			if( query[ i ].type == qtLine && l->data.traceline != (int)query[ i ].value )
				accept = false;
		}
		if( accept )
		{
			LOGNL( ">>>>>> Queried memory data pool allocated in file:" );
			LOGNL( "\"%s\"", l->data.tracefile );
			LOGNL( "at line: %i", l->data.traceline );
			LOGNL( "Size (in bytes): %u", l->data.bytesize );
			LOGNL( "Address: %x", l->data.pointer );
			LOGNL( "Is array: %s", l->data.isarray ? "true" : "false" );
			LOGNL( "" );
			status = true;
		}
	}
#endif
	return( status );
}

bool MemoryManager::debugDataPrint( Printable* object, int level )
{
	if( object )
	{
		ListPrintable* l = findPrintable( object );
		if( l )
		{
			LOGNL( ">>>>>> Object '%s' data printing begin: 0x%p", l->pointer->getName(), l->pointer );
			Printable::Member* m = l->pointer->getMembers();
			XeCore::XeString t, fmt;
			for( int i = 0; i < min( level, 32 ); i++ )
				t << "|";
			fmt.Format( "%s%%%is: ", t.Get(), max( 0, 32 - level ) );
			for( unsigned int i = 0; i < l->pointer->getCount(); i++ )
			{
				LOG( fmt.Get(), m[ i ].name );
				if( m[ i ].formatType == Printable::Member::tCompact )
					debugDataPrint( (Printable*)m[ i ].pointer, level + 1 );
				else
				if( m[ i ].formatType == Printable::Member::tBool )
					LOGNL( "[Bool]\t%s", (*(bool*)m[ i ].pointer) ? "true" : "false" );
				else
				if( m[ i ].formatType == Printable::Member::tChar )
					LOGNL( "[Char]\t%c", (*(char*)m[ i ].pointer) );
				else
				if( m[ i ].formatType == Printable::Member::tByte )
					LOGNL( "[Byte]\t%u", (unsigned int)(*(unsigned char*)m[ i ].pointer) );
				else
				if( m[ i ].formatType == Printable::Member::tShort )
					LOGNL( "[Short]\t%i", (*(short int*)m[ i ].pointer) );
				else
				if( m[ i ].formatType == Printable::Member::tWord )
					LOGNL( "[Word]\t%u", (*(short unsigned int*)m[ i ].pointer) );
				else
				if( m[ i ].formatType == Printable::Member::tInt )
					LOGNL( "[Int]\t%i", (*(int*)m[ i ].pointer) );
				else
				if( m[ i ].formatType == Printable::Member::tDword )
					LOGNL( "[Dword]\t%u", (*(unsigned int*)m[ i ].pointer) );
				else
				if( m[ i ].formatType == Printable::Member::tHalf )
					LOGNL( "[Half]\t%f", (*(float*)m[ i ].pointer) );
				else
				if( m[ i ].formatType == Printable::Member::tReal )
					LOGNL( "[Real]\t%f", (*(double*)m[ i ].pointer) );
				else
				if( m[ i ].formatType == Printable::Member::tPointer )
					LOGNL( "[Pointer]\t0x%p", (*(void**)m[ i ].pointer) );
				else
				if( m[ i ].formatType == Printable::Member::tString )
					LOGNL( "[String]\t%s", (*(char**)m[ i ].pointer) );
				else
					XASSERT( 0, "Undefined data type" );
			}
			fmt.Clear();
			LOGNL( ">>>>>> Object '%s' data printing end: 0x%p", l->pointer->getName(), l->pointer );
		}
		return( true );
	}
	return( false );
}

bool MemoryManager::debugDataPrintAll()
{
	if( m_printableCount )
	{
		LOGNL( ">>>>>> Debug data printing for all objects begin:" );
		LOGNL( "" );
		for( ListPrintable* l = m_printableFirst; l; l = l->next )
		{
			debugDataPrint( l->pointer );
			LOGNL( "" );
		}
		LOGNL( ">>>>>> Debug data printing for all objects end!" );
		return( true );
	}
	else
	{
		LOGNL( ">>>>>> Debug data printing for all objects begin:" );
		return( false );
	}
}

void* MemoryManager::_new( unsigned int bs )
{
	return( malloc( bs ) );
}

void* MemoryManager::_newDebug( unsigned int bs, const char* f, int l )
{
	return( _malloc_dbg( bs, XMM_BLOCK_TYPE, f, l ) );
}

void MemoryManager::_delete( void* d )
{
	free( d );
}

void MemoryManager::_deleteDebug( void* d )
{
	_free_dbg( d, XMM_BLOCK_TYPE );
}

MemoryManager::ListItem* MemoryManager::_addItem()
{
	ListItem* i = (ListItem*)_new( sizeof( ListItem ) );
	i->next = 0;
	if( !i )
		return( 0 );
	if( !m_itemsFirst && !m_itemsLast )
	{
		m_itemsFirst = i;
		m_itemsLast = i;
		m_count++;
		return( i );
	}
	else
	{
		m_itemsLast->next = i;
		m_itemsLast = i;
		m_count++;
		return( i );
	}
	return( 0 );
}

bool MemoryManager::_removeItem( ListItem* i )
{
	ListItem* t = 0;
	for( ListItem* l = m_itemsFirst; l; l = l->next )
	{
		if( l == i )
		{
			if( m_itemsLast == l )
				m_itemsLast = t;
			if( m_itemsFirst == l )
				m_itemsFirst = l->next;
			if( t )
				t->next = l->next;
			MemoryManager::_delete( l );
			m_count--;
			return( true );
		}
		t = l;
	}
	return( false );
}

MemoryManager::ListPrintable* MemoryManager::_addPrintable()
{
	ListPrintable* i = (ListPrintable*)_new( sizeof( ListPrintable ) );
	i->next = 0;
	if( !i )
		return( 0 );
	if( !m_printableFirst && !m_printableLast )
	{
		m_printableFirst = i;
		m_printableLast = i;
		m_printableCount++;
		return( i );
	}
	else
	{
		m_printableLast->next = i;
		m_printableLast = i;
		m_printableCount++;
		return( i );
	}
	return( 0 );
}

bool MemoryManager::_removePrintable( ListPrintable* i )
{
	ListPrintable* t = 0;
	for( ListPrintable* l = m_printableFirst; l; l = l->next )
	{
		if( l == i )
		{
			if( m_printableLast == l )
				m_printableLast = t;
			if( m_printableFirst == l )
				m_printableFirst = l->next;
			if( t )
				t->next = l->next;
			MemoryManager::_delete( l );
			m_printableCount--;
			return( true );
		}
		t = l;
	}
	return( false );
}

MemoryManager::Printable::Printable( const char* name ):
m_members( 0 ),
m_count( 0 ),
m_name( name )
{
	MemoryManager::use().addPrintable( this );
}

MemoryManager::Printable::~Printable()
{
	MemoryManager::use().removePrintable( this );
	DELETE_ARRAY( m_members );
	m_count = 0;
	m_name = 0;
}

void MemoryManager::Printable::setup( Member* members )
{
	DELETE_ARRAY( m_members );
	m_count = 0;
	if( members )
	{
		unsigned int count = 0;
		while( members[ count ].formatType != Member::tCount )
			count++;
		m_members = new Member[ count ];
		m_count = count;
		for( unsigned int i = 0; i < m_count; i++ )
		{
			m_members[ i ].name = members[ i ].name;
			m_members[ i ].pointer = members[ i ].pointer;
			m_members[ i ].formatType = members[ i ].formatType;
		}
	}
}

unsigned int MemoryManager::Printable::getCount()
{
	return( m_count );
}

MemoryManager::Printable::Member* MemoryManager::Printable::getMembers()
{
	return( m_members );
}

const char* MemoryManager::Printable::getName()
{
	return( m_name );
}

#if defined( XMM_MEMORY_TRACING_MODE ) && !defined( MEMORY_TRACE_ALL )

void* MemoryManager::Manageable::operator new( unsigned int s )
{
	return( MemoryManager::use().add( _newDebug( s, 0, 0 ), false, s, "<undefined>", 0 ) );
}

void* MemoryManager::Manageable::operator new[]( unsigned int s )
{
	return( MemoryManager::use().add( _newDebug( s, 0, 0 ), false, s, "<undefined>", 0 ) );
}

void MemoryManager::Manageable::operator delete( void* p ) throw()
{
	MemoryManager::use().remove( MemoryManager::use().find( p ) );
	_delete( p );
}

void MemoryManager::Manageable::operator delete[]( void* p ) throw()
{
	MemoryManager::use().remove( MemoryManager::use().find( p ) );
	_deleteDebug( p );
}

void* MemoryManager::Manageable::operator new( unsigned int s, const char* f, int l )
{
	return( MemoryManager::use().add( _newDebug( s, f, l ), false, s, f, l ) );
}

void* MemoryManager::Manageable::operator new[]( unsigned int s, const char* f, int l )
{
	return( MemoryManager::use().add( _newDebug( s, f, l ), true, s, f, l ) );
}

void MemoryManager::Manageable::operator delete( void* p, const char*, int ) throw()
{
	MemoryManager::use().remove( MemoryManager::use().find( p ) );
	_deleteDebug( p );
}

void MemoryManager::Manageable::operator delete[]( void* p, const char*, int ) throw()
{
	MemoryManager::use().remove( MemoryManager::use().find( p ) );
	_deleteDebug( p );
}

#endif

#if defined( XMM_MEMORY_TRACING_MODE ) && defined( MEMORY_TRACE_ALL )

void* operator new( unsigned int s )
{
	return( MemoryManager::use().add( MemoryManager::_newDebug( s, 0, 0 ), false, s, "<undefined>", 0 ) );
}

void* operator new[]( unsigned int s )
{
	return( MemoryManager::use().add( MemoryManager::_newDebug( s, 0, 0 ), false, s, "<undefined>", 0 ) );
}

void operator delete( void* p ) throw()
{
	MemoryManager::use().remove( MemoryManager::use().find( p ) );
	MemoryManager::_deleteDebug( p );
}

void operator delete[]( void* p ) throw()
{
	MemoryManager::use().remove( MemoryManager::use().find( p ) );
	MemoryManager::_deleteDebug( p );
}

void* operator new( unsigned int s, const char* f, int l )
{
	return( MemoryManager::use().add( MemoryManager::_newDebug( s, f, l ), false, s, f, l ) );
}

void* operator new[]( unsigned int s, const char* f, int l )
{
	return( MemoryManager::use().add( MemoryManager::_newDebug( s, f, l ), true, s, f, l ) );
}

void operator delete( void* p, const char*, int ) throw()
{
	MemoryManager::use().remove( MemoryManager::use().find( p ) );
	MemoryManager::_deleteDebug( p );
}

void operator delete[]( void* p, const char*, int ) throw()
{
	MemoryManager::use().remove( MemoryManager::use().find( p ) );
	MemoryManager::_deleteDebug( p );
}

#endif