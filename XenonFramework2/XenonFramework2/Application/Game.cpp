#include "Game.h"
#include "../XeFramework/Base.h"
#include "../XeFramework/XenonFramework2.h"

RTTI_CLASS_DERIVATIONS(	Game,
						RTTI_DERIVATION( IGame ),
						RTTI_DERIVATIONS_END
						);

Game::Game( char* name, int width, int height, Engine::WindowMode wm ):
IGame( name, width, height, wm ),
RTTI_CLASS_DEFINE( IGame )
{
	LOGNL( "* Create instance: Game" );
	LOGNL( "  Name: '%s'", name );
	LOGNL( "  Resolution: %ix%i", width, height );
	LOGNL( "  Window mode: %s", ( wm == Engine::wmWindowed ? "Windowed" : ( wm == Engine::wmWorkArea ? "Work area" : ( wm == Engine::wmScreenArea ? "Screen area" : ( wm == Engine::wmFullScreen ? "Full screen" : "<undefined>" ) ) ) ) );
	LOGNL( "  OpenGL version: %s", (char*)XeCore::XeGetState( XeCore::XE_RENDER_VERSION ) );
	LOGNL( "  GPU renderer: %s", (char*)XeCore::XeGetState( XeCore::XE_RENDER_RENDERER ) );
	LOGNL( "  GPU vendor: %s", (char*)XeCore::XeGetState( XeCore::XE_RENDER_VENDOR ) );
}

Game::~Game()
{
	LOGNL( "* Destroy instance: Game" );
}
