#pragma once

#include "IRtti.h"
#include "../XeCore/Base/XeWstring.h"

#define UNIVAR_CONSTRUCTOR_DECL( type ) UniVar( XeCore::Xe##type v );
#define UNIVAR_CONSTRUCTOR_DECL_REF( type ) UniVar( XeCore::Xe##type& v );
#define UNIVAR_GET_DATA_DECL( type ) XeCore::Xe##type get##type();
#define UNIVAR_GET_DATA_DECL_REF( type ) XeCore::Xe##type& get##type();
#define UNIVAR_SET_DATA_DECL( type ) void set##type( XeCore::Xe##type v );
#define UNIVAR_SET_DATA_DECL_REF( type ) void set##type( XeCore::Xe##type& v );
#define UNIVAR_OPERATOR_SET( type ) \
	XeCore::Xe##type operator= ( XeCore::Xe##type v ) \
	{ \
		set##type( v ); \
		return( get##type() ); \
	}
#define UNIVAR_OPERATOR_SET_REF( type ) \
	XeCore::Xe##type& operator= ( XeCore::Xe##type& v ) \
	{ \
		set##type( v ); \
		return( get##type() ); \
	}

class UniVar : virtual public IRtti, virtual public MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( UniVar );

public:
	enum Type
	{
		tPointer,
		tChar,
		tByte,
		tShort,
		tWord,
		tInteger,
		tDword,
		tHalf,
		tReal,
		tString,
		tWstring,
		tAssoc,

		tNone
	};

					UniVar();
					UNIVAR_CONSTRUCTOR_DECL( Pointer );
					UNIVAR_CONSTRUCTOR_DECL( Char );
					UNIVAR_CONSTRUCTOR_DECL( Byte );
					UNIVAR_CONSTRUCTOR_DECL( Short );
					UNIVAR_CONSTRUCTOR_DECL( Word );
					UNIVAR_CONSTRUCTOR_DECL( Integer );
					UNIVAR_CONSTRUCTOR_DECL( Dword );
					UNIVAR_CONSTRUCTOR_DECL( Half );
					UNIVAR_CONSTRUCTOR_DECL( Real );
					UNIVAR_CONSTRUCTOR_DECL_REF( String );
					UNIVAR_CONSTRUCTOR_DECL_REF( Wstring );
					~UniVar();
	void			free();
	bool			isType( Type t );
					UNIVAR_SET_DATA_DECL( Pointer );
					UNIVAR_SET_DATA_DECL( Char );
					UNIVAR_SET_DATA_DECL( Byte );
					UNIVAR_SET_DATA_DECL( Short );
					UNIVAR_SET_DATA_DECL( Word );
					UNIVAR_SET_DATA_DECL( Integer );
					UNIVAR_SET_DATA_DECL( Dword );
					UNIVAR_SET_DATA_DECL( Half );
					UNIVAR_SET_DATA_DECL( Real );
					UNIVAR_SET_DATA_DECL_REF( String );
					UNIVAR_SET_DATA_DECL_REF( Wstring );
					UNIVAR_GET_DATA_DECL( Pointer );
					UNIVAR_GET_DATA_DECL( Char );
					UNIVAR_GET_DATA_DECL( Byte );
					UNIVAR_GET_DATA_DECL( Short );
					UNIVAR_GET_DATA_DECL( Word );
					UNIVAR_GET_DATA_DECL( Integer );
					UNIVAR_GET_DATA_DECL( Dword );
					UNIVAR_GET_DATA_DECL( Half );
					UNIVAR_GET_DATA_DECL( Real );
					UNIVAR_GET_DATA_DECL_REF( String );
					UNIVAR_GET_DATA_DECL_REF( Wstring );
					UNIVAR_OPERATOR_SET( Pointer );
					UNIVAR_OPERATOR_SET( Char );
					UNIVAR_OPERATOR_SET( Byte );
					UNIVAR_OPERATOR_SET( Short );
					UNIVAR_OPERATOR_SET( Word );
					UNIVAR_OPERATOR_SET( Integer );
					UNIVAR_OPERATOR_SET( Dword );
					UNIVAR_OPERATOR_SET( Half );
					UNIVAR_OPERATOR_SET( Real );
					UNIVAR_OPERATOR_SET_REF( String );
					UNIVAR_OPERATOR_SET_REF( Wstring );

private:
	void*			m_data;
	Type			m_type;
};