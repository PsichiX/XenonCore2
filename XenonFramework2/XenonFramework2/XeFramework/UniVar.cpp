#include "UniVar.h"

#define UNIVAR_CONSTRUCTOR_DEF( type ) \
	UniVar::UniVar( XeCore::Xe##type v ) : RTTI_CLASS_DEFINE( UniVar ), m_data( 0 ), m_type( tNone ) \
	{ \
		set##type( v ); \
	}

#define UNIVAR_CONSTRUCTOR_DEF_REF( type ) \
	UniVar::UniVar( XeCore::Xe##type& v ) : RTTI_CLASS_DEFINE( UniVar ), m_data( 0 ), m_type( tNone ) \
	{ \
		set##type( v ); \
	}

#define UNIVAR_GET_DATA_DEF( type ) \
	XeCore::Xe##type UniVar::get##type() \
	{ \
		return( *(XeCore::Xe##type*)m_data ); \
	}

#define UNIVAR_GET_DATA_DEF_REF( type ) \
	XeCore::Xe##type& UniVar::get##type() \
	{ \
		return( *(XeCore::Xe##type*)m_data ); \
	}

#define UNIVAR_SET_DATA_DEF( type ) \
	void UniVar::set##type( XeCore::Xe##type v ) \
	{ \
		free(); \
		m_data = new XeCore::Xe##type( v ); \
		m_type = t##type; \
	}

#define UNIVAR_SET_DATA_DEF_REF( type ) \
	void UniVar::set##type( XeCore::Xe##type& v ) \
	{ \
		free(); \
		m_data = new XeCore::Xe##type( v ); \
		m_type = t##type; \
	}

#define UNIVAR_DELETE( type ) \
	if( m_type == t##type ) \
		delete (XeCore::Xe##type*)m_data;

RTTI_CLASS_DERIVATIONS(	UniVar,
						RTTI_DERIVATIONS_END
						);

UniVar::UniVar():
RTTI_CLASS_DEFINE( UniVar ),
m_data( 0 ),
m_type( tNone )
{
}

UNIVAR_CONSTRUCTOR_DEF( Pointer );
UNIVAR_CONSTRUCTOR_DEF( Char );
UNIVAR_CONSTRUCTOR_DEF( Byte );
UNIVAR_CONSTRUCTOR_DEF( Short );
UNIVAR_CONSTRUCTOR_DEF( Word );
UNIVAR_CONSTRUCTOR_DEF( Integer );
UNIVAR_CONSTRUCTOR_DEF( Dword );
UNIVAR_CONSTRUCTOR_DEF( Half );
UNIVAR_CONSTRUCTOR_DEF( Real );
UNIVAR_CONSTRUCTOR_DEF_REF( String );
UNIVAR_CONSTRUCTOR_DEF_REF( Wstring );

UniVar::~UniVar()
{
	free();
}

void UniVar::free()
{
	if( !m_data )
		return;
	UNIVAR_DELETE( Pointer ) else
	UNIVAR_DELETE( Char ) else
	UNIVAR_DELETE( Byte ) else
	UNIVAR_DELETE( Short ) else
	UNIVAR_DELETE( Word ) else
	UNIVAR_DELETE( Integer ) else
	UNIVAR_DELETE( Dword ) else
	UNIVAR_DELETE( Half ) else
	UNIVAR_DELETE( Real ) else
	UNIVAR_DELETE( String ) else
	UNIVAR_DELETE( Wstring ) else
	delete m_data;
}

bool UniVar::isType( Type t )
{
	return( m_type == t );
}

UNIVAR_SET_DATA_DEF( Pointer );
UNIVAR_SET_DATA_DEF( Char );
UNIVAR_SET_DATA_DEF( Byte );
UNIVAR_SET_DATA_DEF( Short );
UNIVAR_SET_DATA_DEF( Word );
UNIVAR_SET_DATA_DEF( Integer );
UNIVAR_SET_DATA_DEF( Dword );
UNIVAR_SET_DATA_DEF( Half );
UNIVAR_SET_DATA_DEF( Real );
UNIVAR_SET_DATA_DEF_REF( String );
UNIVAR_SET_DATA_DEF_REF( Wstring );
UNIVAR_GET_DATA_DEF( Pointer );
UNIVAR_GET_DATA_DEF( Char );
UNIVAR_GET_DATA_DEF( Byte );
UNIVAR_GET_DATA_DEF( Short );
UNIVAR_GET_DATA_DEF( Word );
UNIVAR_GET_DATA_DEF( Integer );
UNIVAR_GET_DATA_DEF( Dword );
UNIVAR_GET_DATA_DEF( Half );
UNIVAR_GET_DATA_DEF( Real );
UNIVAR_GET_DATA_DEF_REF( String );
UNIVAR_GET_DATA_DEF_REF( Wstring );