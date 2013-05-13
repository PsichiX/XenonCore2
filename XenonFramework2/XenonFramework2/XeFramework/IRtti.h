#pragma once
#pragma warning( disable: 4355 )

#include "Base.h"

#define RTTI_CLASS_DECLARE(c)						public: static IRtti::Derivation ___RttiClassDerivationTable___[]; static const char* ___RttiClassName___; private:
#define RTTI_CLASS_DEFINE(c)						IRtti( c::___RttiClassDerivationTable___, c::___RttiClassName___, this )
#define RTTI_DERIVATION(c)							RTTI_AS_DERIVATION( c::___RttiClassDerivationTable___ )
#define RTTI_DERIVATION_TEMPLATE(c)					( (Derivation)c
#define RTTI_DERIVATION_TEMPLATE_REST				::___RttiClassDerivationTable___ )
#define RTTI_DERIVATIONS_END						0
#define RTTI_AS_DERIVATION_TABLE(v)					( (DerivationTable)v )
#define RTTI_AS_DERIVATION(v)						( (Derivation)v )
#define RTTI_CLASS_DERIVATIONS(c,...)				const char* c::___RttiClassName___( ""#c ); IRtti::Derivation c::___RttiClassDerivationTable___[] = { __VA_ARGS__ };
#define RTTI_CLASS_DERIVATIONS_TEMPLATE(c)			const char* c::___RttiClassName___( ""#c ); IRtti::Derivation c
#define RTTI_CLASS_DERIVATIONS_TEMPLATE_REST(...)	::___RttiClassDerivationTable___[] = { __VA_ARGS__ };
#define RTTI_CLASS_TYPE(c)							( (Derivation)c::___RttiClassDerivationTable___ )
#define RTTI_CLASS_TYPE_TEMPLATE(c)					( (Derivation)c
#define RTTI_CLASS_TYPE_TEMPLATE_REST				::___RttiClassDerivationTable___ )
#define RTTI_OBJECT_TYPE(o)							(o)->getType()
#define RTTI_TREAT_AS(o,c)							( (c*)(o) )

class IRtti
{
public:
	typedef unsigned int	Derivation;
	typedef Derivation*		DerivationTable;

							IRtti( DerivationTable derivTab, const char* name, void* basePointer );
							~IRtti();
	Derivation				getType();
	const char*				getName();
	void*					getBasePointer();
	template< class T >
	static bool				isType( IRtti* o );
	template< class T >
	static bool				isDerived( IRtti* o );
	template< class Tf, class Tt >
	static Tt*				derivationCast( Tf* o );

private:
	static bool				___RttiDerived___( Derivation type, IRtti::DerivationTable derivTab );

	DerivationTable			___RttiObjectDerivationTable___;
	const char*				___RttiObjectName___;
	void*					___RttiObjectBasePointer___;
};

template< class T >
bool IRtti::isType( IRtti* o )
{
	return( o ? ( o->___RttiObjectDerivationTable___ == T::___RttiClassDerivationTable___ ) : false );
}

template< class T >
bool IRtti::isDerived( IRtti* o )
{
	return( o ? ( ___RttiDerived___( RTTI_DERIVATION( T ), o->___RttiObjectDerivationTable___ ) ) : false );
}

template< class Tf,class Tt >
Tt* IRtti::derivationCast( Tf* o )
{
	return( isDerived< Tt >( o ) ? (Tt*)(void*)o : 0 );
}
