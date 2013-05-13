#if defined( _DEBUG )

#include "Base.h"
#include "RuntimeDebugger.h"
#include "Engine.h"
#include "IGame.h"
#include "AssetManager.h"
#include "SceneManager.h"
#include <Windows.h>

RuntimeDebugger::RuntimeDebugger():
m_active( false ),
m_lastResult( 0 ),
m_toExit( false ),
m_callback( 0 )
{
}

RuntimeDebugger::~RuntimeDebugger()
{
}

bool RuntimeDebugger::enter()
{
	if( m_active )
		return( false );
	m_active = true;
	m_toExit = false;
	HWND c = GetConsoleWindow();
	ShowWindow( c, SW_SHOW );
	SetForegroundWindow( c );
	SetFocus( c );
	SetActiveWindow( c );
	LOGNL( ">>>>>> Runtime Debugger:" );
	char ln[ 1024 ] = { 0 };
	XeCore::XeString cmd, *sv( 0 );
	unsigned int sc( 0 );
	while( !m_toExit )
	{
		LOG( ">: " );
		std::cin.getline( ln, 1024, '\n' );
		sc = 0;
		sv = XeCore::XeString::ExplodeBuff( ln, 1024, " \t\r\n", sc, "\"" );
		if( sv && sc )
			executeCommand( sv[ 0 ], sc > 1 ? sv + 1 : 0, sc ? sc - 1 : 0 );
		DELETE_ARRAY( sv );
	}
	c = Global::use().engine->getWindow();
	ShowWindow( c, SW_SHOW );
	SetForegroundWindow( c );
	SetFocus( c );
	SetActiveWindow( c );
	m_active = false;
	InputManager::use().clear();
	InputManager::use().charactersClear();
	Global::use().engine->resetTimer();
	return( true );
}

bool RuntimeDebugger::exit()
{
	if( !m_active )
		return( false );
	m_toExit = true;
	return( true );
}

void RuntimeDebugger::executeCommand( XeCore::XeString& cmd, XeCore::XeString* av, unsigned int ac )
{
	m_lastResult = _executeCommand( cmd, av, ac );
}

void RuntimeDebugger::setCallback( CmdCallback clb )
{
	m_callback = clb;
}

RuntimeDebugger::CmdCallback RuntimeDebugger::getCallback()
{
	return( m_callback );
}

unsigned int RuntimeDebugger::_executeCommand( XeCore::XeString& cmd, XeCore::XeString* av, unsigned int ac )
{
	if( cmd == "exit" )
	{
		exit();
		return( 1 );
	}
	else
	if( cmd == "terminate" )
	{
		exit();
		Global::use().game->terminate();
		return( 1 );
	}
	else
	if( cmd == "trace_memory" )
	{
		if( ac > 0 && av && av[ 0 ] == "info" )
		{
			LOGNL( "Memory pools: %u", MemoryManager::use().getCount() );
			LOGNL( "Allocated bytes: %u", MemoryManager::use().totalByteSize() );
		}
		else
		if( ac > 0 && av && av[ 0 ] == "listing" )
		{
			if( ac == 1 )
				MemoryManager::use().traceMemory( -1 );
			else
			{
				unsigned int b( 0 );
				av[ 1 ].Convert( &b, 'd' );
				MemoryManager::use().traceMemory( b );
			}
		}
		else
			MemoryManager::use().traceMemory();
		return( 1 );
	}
	else
	if( cmd == "manager" )
	{
		if( ac > 0 && av )
		{
			if( av[ 0 ] == "info-list" && ac > 1 )
			{
				if( av[ 1 ] == "assets" )
				{
					XeCore::XeString t;
					Global::use().manager->m_assets->getInfoList( t );
					LOGNL( t.Get() );
					return( 1 );
				}
				else
				if( av[ 1 ] == "assets-loading" )
				{
					XeCore::XeString t;
					Global::use().manager->m_assetsLoading->getInfoList( t );
					LOGNL( t.Get() );
					return( 1 );
				}
				else
				if( av[ 1 ] == "scenes" )
				{
					XeCore::XeString t;
					Global::use().manager->m_scenes->getInfoList( t );
					LOGNL( t.Get() );
					return( 1 );
				}
				else
				if( av[ 1 ] == "actors" )
				{
					XeCore::XeString t;
					Global::use().manager->m_actors->current()->getInfoList( t );
					LOGNL( t.Get() );
					return( 1 );
				}
				else
				if( av[ 1 ] == "materials" )
				{
					XeCore::XeString t;
					Global::use().manager->m_materials->getInfoList( t );
					LOGNL( t.Get() );
					return( 1 );
				}
				else
				if( av[ 1 ] == "effects" )
				{
					XeCore::XeString t;
					Global::use().manager->m_effects->getInfoList( t );
					LOGNL( t.Get() );
					return( 1 );
				}
				else
				if( av[ 1 ] == "fonts" )
				{
					XeCore::XeString t;
					Global::use().manager->m_fonts->getInfoList( t );
					LOGNL( t.Get() );
					return( 1 );
				}
				else
				if( av[ 1 ] == "textures" )
				{
					XeCore::XeString t;
					Global::use().manager->m_textures->getInfoList( t );
					LOGNL( t.Get() );
					return( 1 );
				}
				else
				if( av[ 1 ] == "canvases" )
				{
					XeCore::XeString t;
					Global::use().manager->m_canvases->getInfoList( t );
					LOGNL( t.Get() );
					return( 1 );
				}
				else
				if( av[ 1 ] == "audio" )
				{
					XeCore::XeString t;
					Global::use().manager->m_audio->getInfoList( t );
					LOGNL( t.Get() );
					return( 1 );
				}
				else
				{
					XWARNING( "Command not supported" );
				}
				return( 0 );
			}
			else
			{
				XWARNING( "Command not supported" );
			}
			return( 0 );
		}
		return( 0 );
	}
	else
	if( m_callback )
	{
		return( m_callback( cmd, av, ac ) );
	}
	else
	{
		XWARNING( "Command not supported" );
	}
	return( 0 );
}

#endif