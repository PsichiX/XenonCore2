#pragma once

#if defined( _DEBUG )

#include "Singleton.h"

#define ENTER_RUNTIME_DEBUGGER					RuntimeDebugger::use().enter()
#define EXIT_RUNTIME_DEBUGGER					RuntimeDebugger::use().exit()

class RuntimeDebugger : public Singleton< RuntimeDebugger >
{
public:
	typedef unsigned int(*CmdCallback)( XeCore::XeString&, XeCore::XeString*, unsigned int );

							RuntimeDebugger();
							~RuntimeDebugger();
	bool					enter();
	bool					exit();
	void					executeCommand( XeCore::XeString& cmd, XeCore::XeString* av, unsigned int ac );
	void					setCallback( CmdCallback clb );
	CmdCallback				getCallback();

private:
	unsigned int			_executeCommand( XeCore::XeString& cmd, XeCore::XeString* av, unsigned int ac );
	bool					m_active;
	unsigned int			m_lastResult;
	bool					m_toExit;
	CmdCallback				m_callback;
};

#else

#define ENTER_RUNTIME_DEBUGGER
#define EXIT_RUNTIME_DEBUGGER

#endif
