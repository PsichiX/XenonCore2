#include "IRtti.h"

IRtti::IRtti( DerivationTable derivTab, const char* name, void* basePointer ):
___RttiObjectDerivationTable___( derivTab ),
___RttiObjectName___( name ),
___RttiObjectBasePointer___( basePointer )
{
}

IRtti::~IRtti()
{
}

IRtti::Derivation IRtti::getType()
{
	return( RTTI_AS_DERIVATION( ___RttiObjectDerivationTable___ ) );
}

const char* IRtti::getName()
{
	return( ___RttiObjectName___ );
}

void* IRtti::getBasePointer()
{
	return( ___RttiObjectBasePointer___ );
}

bool IRtti::___RttiDerived___( IRtti::Derivation type, IRtti::DerivationTable derivTab )
{
	XASSERT( type, "Given Type cannot be NULL" );
	XASSERT( derivTab, "Given Derivation Table cannot be NULL" );
	DerivationTable curr = derivTab;
	if( curr == RTTI_AS_DERIVATION_TABLE( type ) )
		return( true );
	while( *curr != RTTI_DERIVATIONS_END )
	{
		XASSERT( *curr != RTTI_AS_DERIVATION( derivTab ), "Object cannot derivate by himself" );
		if( *curr == type )
			return( true );
		else
		if( ___RttiDerived___( type, RTTI_AS_DERIVATION_TABLE( *curr ) ) )
			return( true );
		curr++;
	}
	return( false );
}
