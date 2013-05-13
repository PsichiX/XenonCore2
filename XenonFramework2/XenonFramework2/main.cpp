#include "XeFramework/XenonFramework2.h"
#include "XeFramework/Base.h"
#include "XeFramework/AssetManager.h"
#include "Application/Game.h"
#include "Application/Menu.h"
#include "Application/Loading.h"

MAIN
{
	CRT_TRACE_MEMORY_ON_EXIT;

	LOG_SETUP( "XeFramework2.log" );

	Game* game = xnew Game(	"XeFramework2",
							1024,
							576,
							Engine::wmWindowed
							);

	GLOBAL.assets->setSource( "./assets" );
	GLOBAL.assetsLoading->setSource( "./assets" );
	GLOBAL.manager->setDefaultProgressState( xnew Loading() );

	GLOBAL.engine->vsync( true );
	game->run( xnew Menu() );
	DELETE_OBJECT( game );

	TRACE_MEMORY_LISTING_PAUSE( 128 );

	EXIT_MAIN;
}
