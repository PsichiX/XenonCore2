#include "PlayerBrain.h"
#include "Player.h"

RTTI_CLASS_DERIVATIONS(	PlayerBrain,
						RTTI_DERIVATION( IController ),
						RTTI_DERIVATIONS_END
						);

PlayerBrain::PlayerBrain():
RTTI_CLASS_DEFINE( PlayerBrain )
{
}

PlayerBrain::~PlayerBrain()
{
}

void PlayerBrain::update()
{
}

void PlayerBrain::input()
{
	if( IRtti::isType< Player >( getActor() ) )
	{
		if( KEY_HOLD( VK_UP ) )
			RTTI_TREAT_AS( getActor(), Player )->move( XeCore::XeHalfVector( 0.0f, -400.0f * GLOBAL.engine->getDeltaTime() ) );
		else
		if( KEY_HOLD( VK_DOWN ) )
			RTTI_TREAT_AS( getActor(), Player )->move( XeCore::XeHalfVector( 0.0f, 400.0f * GLOBAL.engine->getDeltaTime() ) );
		else
		if( KEY_HOLD( VK_LEFT ) )
			RTTI_TREAT_AS( getActor(), Player )->move( XeCore::XeHalfVector( -400.0f * GLOBAL.engine->getDeltaTime(), 0.0f ) );
		else
		if( KEY_HOLD( VK_RIGHT ) )
			RTTI_TREAT_AS( getActor(), Player )->move( XeCore::XeHalfVector( 400.0f * GLOBAL.engine->getDeltaTime(), 0.0f ) );
	}
}