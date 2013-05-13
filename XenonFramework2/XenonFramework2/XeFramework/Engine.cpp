#include "Engine.h"
#include "../XeCore/Base/XeTime.h"
#include <math.h>

RTTI_CLASS_DERIVATIONS(	Engine,
						RTTI_DERIVATIONS_END
						);

Engine::Engine():
RTTI_CLASS_DEFINE( Engine ),
m_hwnd( 0 ),
m_windowmode( wmWindowed ),
m_time( 0 ),
m_newTime( 0 ),
m_deltaTime( 0 ),
m_fps( 0 ),
m_frames( 0 ),
m_fpsTime( 0 ),
m_texUnitsMax( 1 )
{
	XeCore::XeInitiation();
}

Engine::~Engine()
{
	XeCore::XeClosure();
}

bool Engine::initiation( const char* name, int width, int height, WindowMode wm )
{
	int x = 0;
	int y = 0;
	int w = width;
	int h = height;
	if( wm == wmWindowed )
	{
		x = GetSystemMetrics( SM_CXSCREEN ) / 2 - w / 2;
		y = GetSystemMetrics( SM_CYSCREEN ) / 2 - h / 2;
	}
	else
	if( wm == wmScreenArea )
	{
		w = GetSystemMetrics( SM_CXSCREEN );
		h = GetSystemMetrics( SM_CYSCREEN );
	}
	else
	if( wm == wmWorkArea )
	{
		RECT workrect;
		SystemParametersInfo( SPI_GETWORKAREA, 0, &workrect, 0 );
		x = workrect.left;
		y = workrect.top;
		w = workrect.right - workrect.left;
		h = workrect.bottom - workrect.top;
	}
	WNDCLASSEX wincl;
	wincl.hInstance = GetModuleHandle( NULL );
	wincl.lpszClassName = name;
	wincl.lpfnWndProc = windowProcedure;
	wincl.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wincl.cbSize = sizeof( WNDCLASSEX );
	wincl.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wincl.hIconSm = LoadIcon( NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor( NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hbrBackground = NULL;
	if( !RegisterClassEx( &wincl ) ) return( false );
	m_hwnd = CreateWindowEx(	WS_EX_APPWINDOW, name, name,
								WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
								x, y, w, h,
								NULL, NULL, wincl.hInstance, NULL
								);
	ShowWindow( m_hwnd, SW_SHOW );
	DEVMODE dmScreenSettings;
	memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );
	dmScreenSettings.dmSize = sizeof( dmScreenSettings );
	if( wm == wmFullScreen )
	{
		dmScreenSettings.dmPelsWidth = w;
		dmScreenSettings.dmPelsHeight = h;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields |= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		if( ChangeDisplaySettings( &dmScreenSettings, 0 ) != DISP_CHANGE_SUCCESSFUL )
			wm = wmWindowed;
	}
	m_windowmode = wm;
	if( XeCore::Photon::XeRenderTargetCreate( &m_renderer, m_hwnd, XeCore::XE_DRAW_TO_WINDOW, 32, 16 ) )
	{
		if( XeCore::Photon::XeRenderTargetArea( m_renderer, 0, 0, w, h, 45, -1, 1, (double)w / (double)h ) )
		{
			if( XeCore::Photon::XeRenderTargetActivate( m_renderer ) )
			{
				XeCore::Photon::XeRenderVsync( XeCore::XE_FALSE );
				XeCore::XeSetState( XeCore::XE_SCENE_COLOR, 0.0, 0.0, 0.0, 0.0 );
				XeCore::Photon::XeExtensions();
				XeCore::Photon::XeShaderInit();
				XeCore::Photon::XeVertexBufferInit();
				XeCore::Photon::XeTextureMulti();
				XeCore::Photon::XeTextureUnit( 0 );
				m_texUnitsMax = *(int*)XeCore::XeGetState( XeCore::XE_TEXTURE_UNIT_COUNT );
				return( true );
			}
			else
			{
				XeCore::Photon::XeRenderTargetDestroy( m_renderer );
				m_renderer.Unref();
				DestroyWindow( m_hwnd );
				return( false );
			}
		}
		else
		{
			XeCore::Photon::XeRenderTargetDestroy( m_renderer );
			m_renderer.Unref();
			DestroyWindow( m_hwnd );
			return( false );
		}
	}
	else
	{
		DestroyWindow( m_hwnd );
		return( false );
	}
	return( false );
}

bool Engine::closure()
{
	XeCore::Photon::XeRenderTargetDestroy( m_renderer );
	m_renderer.Unref();
	if( m_windowmode == wmFullScreen )
		ChangeDisplaySettings( NULL, 0 );
	m_windowmode = wmWindowed;
	if( m_hwnd )
		DestroyWindow( m_hwnd );
	m_texUnitsMax = 1;
	return( true );
}

void Engine::flush()
{
	XeCore::Photon::XeRenderExecute( XeCore::XE_FLUSH );
}

void Engine::finish()
{
	XeCore::Photon::XeRenderExecute( XeCore::XE_FINISH );
}

void Engine::render()
{
	XeCore::Photon::XeRenderScene( XE_FLAG_SWAP | XE_FLAG_COLORBUFF | XE_FLAG_DEPTHBUFF );
}

bool Engine::vsync( bool mode )
{
	return( XeCore::Photon::XeRenderVsync( mode ? XeCore::XE_TRUE : XeCore::XE_FALSE ) );
}

Engine::LoopResult Engine::processLoop()
{
	//memset( &m_messages, 0, sizeof(MSG) );
	m_messages.message = WM_NULL;
	if( PeekMessage( &m_messages, m_hwnd, 0, 0, PM_REMOVE ) )
	{
		if( m_messages.message == WM_QUIT )
			return( lrQuit );
		else
		{
			TranslateMessage( &m_messages );
			DispatchMessage( &m_messages );
			return( lrMsg );
		}
	}
	else
	{
		m_newTime = XeCore::XeTime::GetMilisecs();
		m_deltaTime = m_newTime - m_time;
		m_time = m_newTime;
		m_frames++;
		m_fpsTime += m_deltaTime;
		if( m_fpsTime >= 1000 )
		{
			int ft = static_cast<int>(m_fpsTime) / 1000;
			if( ft )
				m_fps = m_frames / ft;
			else
				m_fps = 0;
			m_frames = 0;
			m_fpsTime = m_fpsTime % 1000;
		}
		return( lrLogic );
	}
	return( lrNone );
}

bool Engine::terminateThread( XeCore::XeHandle t, XeCore::XeDword c )
{
	return( TerminateThread( (HANDLE)t, c ) ? true : false );
}

void Engine::resetTimer()
{
	m_time = XeCore::XeTime::GetMilisecs();
	m_newTime = m_time;
	m_frames = 0;
	m_deltaTime = 0;
	m_fps = 0;
	m_fpsTime = 0;
}

float Engine::getDeltaTime()
{
	return( static_cast<float>(m_deltaTime) * 0.001f );
}

int Engine::getFps()
{
	return( m_fps );
}

int Engine::getFramesCounted()
{
	return( m_frames );
}

float Engine::getCurrentTime()
{
	return( static_cast<float>(m_time) * 0.001f );
}

const XeCore::Photon::XeElmRenderTarget& Engine::getRenderTarget()
{
	return( m_renderer );
}

HWND Engine::getWindow()
{
	return( m_hwnd );
}

bool Engine::getWindowRect( WindowRect& wr )
{
	RECT r;
	if( GetWindowRect( m_hwnd, &r ) )
	{
		wr.x = r.left;
		wr.y = r.top;
		wr.width = r.right - r.left;
		wr.height = r.bottom - r.top;
		return( true );
	}
	return( false );
}

int Engine::getTextureUnitsCount()
{
	return( m_texUnitsMax );
}

LRESULT CALLBACK Engine::windowProcedure(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
		case(WM_SYSCOMMAND):
		{
			switch(wParam)
			{
				case(SC_RESTORE):
				{
					ShowWindow(hWnd,SW_SHOWDEFAULT);
					return(0);
				}
				case(SC_SCREENSAVE):
				case(SC_MONITORPOWER):
				return(0);
			}
			return(0);
		}
		case(WM_CHAR):
		{
			InputManager::use().pushCharacter((char)wParam);
			return(0);
		}
		case(WM_DESTROY):
		{
			PostQuitMessage(0);
			return(0);
		}
		case(WM_KEYDOWN):
		{
			if(!InputManager::use().m_keysHold[wParam])
			{
				InputManager::use().m_keysPressed[wParam]=true;
				InputManager::use().m_keysPressed[0]=true;
			}
			InputManager::use().m_keysHold[wParam]=true;
			InputManager::use().m_keysHold[0]=true;
			return(0);
		}
		case(WM_KEYUP):
		{
			InputManager::use().m_keysReleased[wParam]=true;
			InputManager::use().m_keysReleased[0]=true;
			InputManager::use().m_keysHold[wParam]=false;
			InputManager::use().m_keysHold[0]=false;
			for(unsigned int i = 1; i < 256; i++)
				if(InputManager::use().m_keysHold[i])
				{
					InputManager::use().m_keysHold[0]=true;
					break;
				}
			return(0);
		}
		case(WM_LBUTTONDOWN):
		{
			if(!InputManager::use().m_buttonsHold[InputManager::ibLeft])
			{
				InputManager::use().m_buttonsPressed[InputManager::ibLeft]=true;
				InputManager::use().m_buttonsPressed[0]=true;
			}
			InputManager::use().m_buttonsHold[InputManager::ibLeft]=true;
			InputManager::use().m_buttonsHold[0]=true;
			return(0);
		}
		case(WM_RBUTTONDOWN):
		{
			if(!InputManager::use().m_buttonsHold[InputManager::ibRight])
			{
				InputManager::use().m_buttonsPressed[InputManager::ibRight]=true;
				InputManager::use().m_buttonsPressed[0]=true;
			}
			InputManager::use().m_buttonsHold[InputManager::ibRight]=true;
			InputManager::use().m_buttonsHold[0]=true;
			return(0);
		}
		case(WM_MBUTTONDOWN):
		{
			if(!InputManager::use().m_buttonsHold[InputManager::ibMiddle])
			{
				InputManager::use().m_buttonsPressed[InputManager::ibMiddle]=true;
				InputManager::use().m_buttonsPressed[0]=true;
			}
			InputManager::use().m_buttonsHold[InputManager::ibMiddle]=true;
			InputManager::use().m_buttonsHold[0]=true;
			return(0);
		}
		case(WM_LBUTTONUP):
		{
			InputManager::use().m_buttonsReleased[InputManager::ibLeft]=true;
			InputManager::use().m_buttonsReleased[0]=true;
			InputManager::use().m_buttonsHold[InputManager::ibLeft]=false;
			InputManager::use().m_buttonsHold[0]=false;
			for(unsigned int i = 1; i < InputManager::ibCount; i++)
				if(InputManager::use().m_buttonsHold[i])
				{
					InputManager::use().m_buttonsHold[0]=true;
					break;
				}
			return(0);
		}
		case(WM_RBUTTONUP):
		{
			InputManager::use().m_buttonsReleased[InputManager::ibRight]=true;
			InputManager::use().m_buttonsReleased[0]=true;
			InputManager::use().m_buttonsHold[InputManager::ibRight]=false;
			InputManager::use().m_buttonsHold[0]=false;
			for(unsigned int i = 1; i < InputManager::ibCount; i++)
				if(InputManager::use().m_buttonsHold[i])
				{
					InputManager::use().m_buttonsHold[0]=true;
					break;
				}
			return(0);
		}
		case(WM_MBUTTONUP):
		{
			InputManager::use().m_buttonsReleased[InputManager::ibMiddle]=true;
			InputManager::use().m_buttonsReleased[0]=true;
			InputManager::use().m_buttonsHold[InputManager::ibMiddle]=false;
			InputManager::use().m_buttonsHold[0]=false;
			for(unsigned int i = 1; i < InputManager::ibCount; i++)
				if(InputManager::use().m_buttonsHold[i])
				{
					InputManager::use().m_buttonsHold[0]=true;
					break;
				}
			return(0);
		}
		case(WM_MOUSEWHEEL):
		{
			InputManager::use().m_wheelDelta=GET_WHEEL_DELTA_WPARAM(wParam);
			return(0);
		}
	}
	return(DefWindowProc(hWnd,uMsg,wParam,lParam));
}

DWORD WINAPI Engine::processThread( void* desc )
{
	ThreadDesc* td = (ThreadDesc*)desc;
	XeCore::XeByte* data = new XeCore::XeByte[ td->size ];
	memcpy_s( data, td->size, td->ptr, td->size );
	DWORD status( 0 );
	if( td->func )
		status = td->func( data, td->size );
	DELETE_ARRAY( data );
	return( 0 );
}