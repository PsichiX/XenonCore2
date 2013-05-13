#pragma once

#include "IRtti.h"
#include "Engine.h"

class Manager;
class IState;
class IProgressState;

class IGame : public virtual IRtti, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( IGame );

public:
						IGame( char* name, int width = 0, int height = 0, Engine::WindowMode wm = Engine::wmWindowed );
	virtual				~IGame() = 0;
	bool				onProgress();
	void				run( IState* s, IProgressState* p = 0 );
	void				terminate();
	Manager*			getManager();
	void				setRenderInterval( float i );
	float				getRenderInterval();

private:
	Manager*			m_manager;
	bool				m_isRunning;
	float				m_renderInterval;
	float				m_renderIntervalAccel;
};
