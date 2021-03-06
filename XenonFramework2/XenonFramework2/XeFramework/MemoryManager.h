#pragma once

#include "Singleton.h"

#if defined( _DEBUG ) && defined( MEMORY_TRACING )
#define XMM_MEMORY_TRACING_MODE
#define xnew								new( __FILE__, __LINE__ )
#define xdelete								delete
#define TRACE_MEMORY						MemoryManager::use().traceMemory()
#define TRACE_MEMORY_PAUSE					if( TRACE_MEMORY ) { system( "pause" ); }
#define TRACE_MEMORY_LISTING(b)				MemoryManager::use().traceMemory( b )
#define TRACE_MEMORY_LISTING_PAUSE(b)		if( TRACE_MEMORY_LISTING( b ) ) { system( "pause" ); }
#define CRT_TRACE_MEMORY					MemoryManager::crtTraceMemory()
#define CRT_TRACE_MEMORY_PAUSE				if( CRT_TRACE_MEMORY ) { system( "pause" ); }
#define CRT_TRACE_MEMORY_ON_EXIT			_CrtSetDbgFlag( _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ) | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF )
#define QUERY_PRINT_MEMORY(q,c)				MemoryManager::use().queryPrint( q, c )
#define QUERY_PRINT_MEMORY_PAUSE(q,c)		if( QUERY_PRINT_MEMORY( q, c ) ) { system( "pause" ); }
#else
#define xnew								new
#define xdelete								delete
#define TRACE_MEMORY
#define TRACE_MEMORY_PAUSE
#define TRACE_MEMORY_LISTING(b)
#define TRACE_MEMORY_LISTING_PAUSE(b)
#define CRT_TRACE_MEMORY
#define CRT_TRACE_MEMORY_PAUSE
#define CRT_TRACE_MEMORY_ON_EXIT
#define QUERY_PRINT_MEMORY(q,c)
#define QUERY_PRINT_MEMORY_PAUSE(q,c)
#endif
#define DEBUG_DATA_PRINT_ALL				MemoryManager::use().debugDataPrintAll()
#define DEBUG_DATA_PRINT_OBJECT(o)			MemoryManager::use().debugDataPrint( o )
#define DEBUG_DATA_PRINT_ALL_PAUSE			if( DEBUG_DATA_PRINT_ALL ){ system( "pause" ); }
#define DEBUG_DATA_PRINT_OBJECT_PAUSE(o)	if( DEBUG_DATA_PRINT_OBJECT( o ) ){ system( "pause" ); }

#define XMM_PRINTABLE(c)					MemoryManager::Printable( ""#c )
#define XMM_PRINTABLE_SETUP(...)			{ MemoryManager::Printable::Member m[] = { __VA_ARGS__ }; MemoryManager::Printable::setup( m ); }
#define XMM_PRINTABLE_MEMBER(o)				MemoryManager::Printable::Member( o, ""#o )
#define XMM_PRINTABLE_MEMBER_PTR(o)			MemoryManager::Printable::Member( (void**)&o, ""#o )
#define XMM_PRINTABLE_MEMBERS_END			MemoryManager::Printable::Member()

class MemoryManager : public Singleton< MemoryManager >
{
public:
	class Printable;

	struct Item
	{
		void*			pointer;
		bool			isarray;
		unsigned int	bytesize;
		const char*		tracefile;
		int				traceline;
	};

	struct ListItem
	{
		ListItem*		next;
		Item			data;
	};

	struct ListPrintable
	{
		ListPrintable*	next;
		Printable*		pointer;
	};

	enum QueryType
	{
		qtIsArray,
		qtByteSize,
		qtFile,
		qtLine,

		qtCount
	};

	struct Query
	{
		Query( QueryType t, bool v ) : type( t ), value( (void*)v ) {}
		Query( QueryType t, unsigned int v ) : type( t ), value( (void*)v ) {}
		Query( QueryType t, const char* v ) : type( t ), value( (void*)v ) {}
		Query( QueryType t, int v ) : type( t ), value( (void*)v ) {}
		QueryType		type;
		void*			value;
	};

					MemoryManager();
					~MemoryManager();
	void*			add( void* newobj, bool isarray, unsigned int bytesize, const char* tracefile, int traceline );
	ListItem*		find( void* ptr );
	void			remove( ListItem* item );
	bool			addPrintable( Printable* ptr );
	ListPrintable*	findPrintable( Printable* ptr );
	void			removePrintable( Printable* ptr );
	unsigned int	getCount();
	ListItem*		getFirst();
	unsigned int	totalByteSize();
	bool			traceMemory( unsigned int listingDataBytes = 0 );
	static int		crtTraceMemory();
	bool			queryPrint( Query* query, unsigned int count );
	bool			debugDataPrint( Printable* object, int level = 0 );
	bool			debugDataPrintAll();

	static void*	_new( unsigned int bs );
	static void*	_newDebug( unsigned int bs, const char* f, int l );
	static void		_delete( void* d );
	static void		_deleteDebug( void* d );
	template< class T >
	static T*		__new();
	template< class T >
	static void		__delete( T* p );
	template< class T >
	static T*		__newDebug( const char* f, int l );
	template< class T >
	static void		__deleteDebug( T* p );
	template< class T >
	static T*		__newArray( unsigned int c );
	template< class T >
	static void		__deleteArray( T* p, unsigned int c );
	template< class T >
	static T*		__newArrayDebug( unsigned int c, const char* f, int l );
	template< class T >
	static void		__deleteArrayDebug( T* p, unsigned int c );

private:
	ListItem*		_addItem();
	bool			_removeItem( ListItem* i );
	ListPrintable*	_addPrintable();
	bool			_removePrintable( ListPrintable* i );

	ListItem*		m_itemsFirst;
	ListItem*		m_itemsLast;
	ListPrintable*	m_printableFirst;
	ListPrintable*	m_printableLast;
	unsigned int	m_printableCount;
	unsigned int	m_count;
	unsigned int	m_bytesize;

public:
	class Manageable
	{
	public:
#if defined( XMM_MEMORY_TRACING_MODE ) && !defined( MEMORY_TRACE_ALL )
		void* operator new( unsigned int );
		void* operator new[]( unsigned int );
		void operator delete( void* ) throw();
		void operator delete[]( void* ) throw();
		void* operator new( unsigned int, const char*, int );
		void* operator new[]( unsigned int, const char*, int );
		void operator delete( void*, const char*, int ) throw();
		void operator delete[]( void*, const char*, int ) throw();
#endif
	};

	class Printable
	{
	public:
		struct Member
		{
		public:
			enum Type
			{
				tCompact,
				tBool,
				tChar,
				tByte,
				tShort,
				tWord,
				tInt,
				tDword,
				tHalf,
				tReal,
				tPointer,
				tString,

				tCount
			};

						Member() : pointer( 0 ), name( 0 ), formatType( tCount ) {}
						Member( Printable& p, const char* n ) : pointer( &p ), name( n ), formatType( tCompact ) {}
						Member( bool& p, const char* n ) : pointer( &p ), name( n ), formatType( tBool ) {}
						Member( char& p, const char* n ) : pointer( &p ), name( n ), formatType( tChar ) {}
						Member( unsigned char& p, const char* n ) : pointer( &p ), name( n ), formatType( tByte ) {}
						Member( short int& p, const char* n ) : pointer( &p ), name( n ), formatType( tShort ) {}
						Member( unsigned short int& p, const char* n ) : pointer( &p ), name( n ), formatType( tWord ) {}
						Member( int& p, const char* n ) : pointer( &p ), name( n ), formatType( tInt ) {}
						Member( unsigned int& p, const char* n ) : pointer( &p ), name( n ), formatType( tDword ) {}
						Member( float& p, const char* n ) : pointer( &p ), name( n ), formatType( tHalf ) {}
						Member( double& p, const char* n ) : pointer( &p ), name( n ), formatType( tReal ) {}
						Member( void** p, const char* n ) : pointer( p ), name( n ), formatType( tPointer ) {}
						Member( char*& p, const char* n ) : pointer( &p ), name( n ), formatType( tString ) {}
			void*		pointer;
			const char*	name;
			Type		formatType;
		};

						Printable( const char* name );
						~Printable();
		void			setup( Member* members );
		unsigned int	getCount();
		Member*			getMembers();
		const char*		getName();

	private:
		Member*			m_members;
		unsigned int	m_count;
		const char*		m_name;
	};
};

#if defined( XMM_MEMORY_TRACING_MODE ) && defined( MEMORY_TRACE_ALL )
void* operator new( unsigned int );
void* operator new[]( unsigned int );
void operator delete( void* ) throw();
void operator delete[]( void* ) throw();
void* operator new( unsigned int, const char*, int );
void* operator new[]( unsigned int, const char*, int );
void operator delete( void*, const char*, int ) throw();
void operator delete[]( void*, const char*, int ) throw();
#endif

template< class T >
T* MemoryManager::__new()
{
	T* p = (T*)MemoryManager::_new( sizeof( T ) );
	new( p ) T();
	return( p );
}

template< class T >
void MemoryManager::__delete( T* p )
{
	p->~T();
	MemoryManager::_delete( p );
}

template< class T >
T* MemoryManager::__newDebug( const char* f, int l )
{
	T* p = (T*)MemoryManager::_newDebug( sizeof( T ), f, l );
	new( p ) T();
	return( p );
}

template< class T >
void MemoryManager::__deleteDebug( T* p )
{
	p->~T();
	MemoryManager::_deleteDebug( p );
}

template< class T >
T* MemoryManager::__newArray( unsigned int c )
{
	T* p = (T*)MemoryManager::_new( sizeof( T ) * c );
	T* _p = p;
	for( unsigned int i = 0; i < c; i++, _p++ )
		new( _p ) T();
	return( p );
}

template< class T >
void MemoryManager::__deleteArray( T* p, unsigned int c )
{
	T* _p = p;
	for( unsigned int i = 0; i < c; i++, _p++ )
		_p->~T();
	MemoryManager::_delete( p );
}

template< class T >
T* MemoryManager::__newArrayDebug( unsigned int c, const char* f, int l )
{
	T* p = (T*)MemoryManager::_newDebug( sizeof( T ), f, l );
	T* _p = p;
	for( unsigned int i = 0; i < c; i++, _p++ )
		new( _p ) T();
	return( p );
}

template< class T >
void MemoryManager::__deleteArrayDebug( T* p, unsigned int c )
{
	T* _p = p;
	for( unsigned int i = 0; i < c; i++, _p++ )
		_p->~T();
	MemoryManager::_deleteDebug( p );
}