#pragma once

#include "Logger.h"
#include "MemoryManager.h"
#include "InputManager.h"
#include "RuntimeDebugger.h"
#include "Global.h"

#if defined( _DEBUG )
#define MAIN							int main( int argc, const char* argv[] )
#define EXIT_MAIN_CODE(c)				{ SINGLETONS_DESTROY; return( ( c ) ); }
#define EXIT_MAIN						EXIT_MAIN_CODE( 0 )
#define LOG_SETUP(f)					Logger::use().setup( f )
#else
#define MAIN							int WINAPI WinMain( HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil )
#define EXIT_MAIN_CODE(c)				{ SINGLETONS_DESTROY; return( ( c ) ); }
#define EXIT_MAIN						EXIT_MAIN_CODE( 0 )
#define LOG_SETUP(...)					
#endif
#define DELETE_OBJECT(o)				{ if( o ){ delete o; o = 0; } }
#define DELETE_ARRAY(a)					{ if( a ){ delete[] a; a = 0; } }
#if defined( _DEBUG )
#include <assert.h>
#define LOG(str,...)					Logger::use().log( str, __VA_ARGS__ )
#define LOGNL(str,...)					Logger::use().lognl( str, __VA_ARGS__ )
#define XBREAKPOINT						_CrtDbgBreak()
#define XASSERT(expr,str,...)			if(!(expr)){ LOGNL( ">>>>>> Assertion Report:" ); LOGNL( str, __VA_ARGS__ ); LOGNL( "" ); assert(false); }
#define XWARNING(str,...)				{ LOGNL( ">>>>>> Warning Report:" ); LOGNL( str, __VA_ARGS__ ); LOGNL( "" ); }
#if defined( PEDANTIC_MODE )
#define XPEDANTICWARNING				XASSERT
#else
#define XPEDANTICWARNING				XWARNING
#endif
#else
#define LOG(...)
#define LOGNL(...)
#define XBREAKPOINT
#define XASSERT(...)
#define XWARNING(...)
#define XPEDANTICWARNING
#endif
#define FORCEINLINE						__forceinline
#define KEY_PRESSED(c)					InputManager::use().getKey( InputManager::iePressed, c )
#define KEY_HOLD(c)						InputManager::use().getKey( InputManager::ieHold, c )
#define KEY_RELEASED(c)					InputManager::use().getKey( InputManager::ieReleased, c )
#define KEY_AFTER(c)					InputManager::use().getKey( InputManager::ieAfter, c )
#define BUTTON_PRESSED(b)				InputManager::use().getButton( InputManager::iePressed, b )
#define BUTTON_HOLD(b)					InputManager::use().getButton( InputManager::ieHold, b )
#define BUTTON_RELEASED(b)				InputManager::use().getButton( InputManager::ieReleased, b )
#define BUTTON_AFTER(b)					InputManager::use().getButton( InputManager::ieAfter, b )
#define WHEEL_STEPS						InputManager::use().getWheelDelta()
#define CLAMP(v,mn,mx)					min( mx, max( mn, v ) )
#define REPEAT(c)						for( unsigned int __c_o_u_n_t_e_r__ = 0; __c_o_u_n_t_e_r__ < c; __c_o_u_n_t_e_r__++ )
#define LERP(f,mn,mx)					( ( ( f ) * ( mx ) ) + ( ( 1.0f - ( f ) ) * ( mn ) ) )
#if defined( _DEBUG )
#define SINGLETONS_DESTROY				{ RuntimeDebugger::destroy(); InputManager::destroy(); Global::destroy(); Logger::destroy(); MemoryManager::destroy(); }
#else
#define SINGLETONS_DESTROY				{ InputManager::destroy(); Global::destroy(); Logger::destroy(); MemoryManager::destroy(); }
#endif
#define INPUT							InputManager::use()
#define GLOBAL							Global::use()
#define BIT(i)							( 1 << i )

typedef XeCore::XeString				NameID;