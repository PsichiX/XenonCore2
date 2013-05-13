#pragma once

#include "Base.h"
#include "IRtti.h"
#include "../XeCore/XenonCore2Loader.h"

class Engine : public virtual IRtti, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Engine );

public:
	typedef XeCore::XeHandle(*ThreadFunction)( XeCore::XePointer, XeCore::XeDword );

	enum LoopResult
	{
		lrNone,
		lrQuit,
		lrLogic,
		lrMsg,

		lrCount
	};

	enum WindowMode
	{
		wmWindowed,
		wmWorkArea,
		wmScreenArea,
		wmFullScreen,

		wmCount
	};

	struct WindowRect
	{
		WindowRect()							: x( 0 ), y( 0 ), width( 0 ), height( 0 ) {}
		int										x;
		int										y;
		int										width;
		int										height;
	};
												Engine();
												~Engine();
	bool										initiation( const char* name, int width, int height, WindowMode wm = wmWindowed );
	bool										closure();
	void										flush();
	void										finish();
	void										render();
	bool										vsync( bool mode );
	static FORCEINLINE void						bgColor( XeCore::XeHalfVector& col ) { XeCore::XeSetState( XeCore::XE_SCENE_COLOR, (double)col.X, (double)col.Y, (double)col.Z, (double)col.W ); }
	LoopResult									processLoop();
	template< class T >
	XeCore::XeHandle							runThread( ThreadFunction tf, T* input );
	bool										terminateThread( XeCore::XeHandle t, XeCore::XeDword c );
	void										resetTimer();
	float										getDeltaTime();
	int											getFps();
	int											getFramesCounted();
	float										getCurrentTime();
	const XeCore::Photon::XeElmRenderTarget&	getRenderTarget();
	HWND										getWindow();
	bool										getWindowRect( WindowRect& wr );
	int											getTextureUnitsCount();

	static LRESULT CALLBACK				windowProcedure( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

private:
	struct ThreadDesc
	{
										ThreadDesc( ThreadFunction f, XeCore::XePointer p, XeCore::XeDword s ) : func( f ), ptr( p ), size( s ) {}
		ThreadFunction					func;
		XeCore::XePointer				ptr;
		XeCore::XeDword					size;
	};

	static DWORD WINAPI					processThread( void* desc );

	HWND								m_hwnd;
	MSG									m_messages;
	WindowMode							m_windowmode;
	XeCore::Photon::XeElmRenderTarget	m_renderer;
	LONGLONG							m_time;
	LONGLONG							m_newTime;
	LONGLONG							m_deltaTime;
	int									m_frames;
	int									m_fps;
	LONGLONG							m_fpsTime;
	int									m_texUnitsMax;

public:
	/*class Semaphore
	{
	public:
										Semaphore( NameID& name );
										~Semaphore();
		void							open();
		void							close();

	private:
		volatile NameID					m_name;
		volatile unsigned int			m_waits;
	};*/
};

template< class T >
XeCore::XeHandle Engine::runThread( ThreadFunction tf, T* input )
{
	DWORD tid( -1 );
	Engine::ThreadDesc td( tf, input, sizeof( T ) );
	HANDLE t = CreateThread( 0, 0, processThread, &td, 0, &tid );
	return( (XeCore::XeHandle)t );
}
