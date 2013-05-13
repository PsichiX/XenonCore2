#include "IGame.h"
#include "Manager.h"
#include "IState.h"
#include <windows.h>
#include <math.h>

RTTI_CLASS_DERIVATIONS(	IGame,
						RTTI_DERIVATIONS_END
						);

IGame::IGame( char* name, int width, int height, Engine::WindowMode wm ):
RTTI_CLASS_DEFINE( IGame ),
m_manager( 0 ),
m_isRunning( false ),
m_renderInterval( 0.0f ),
m_renderIntervalAccel( 0.0f )
{
	m_manager = xnew Manager( name, width, height, wm );

	Global::use().game = this;
	Global::use().manager = m_manager;
}

IGame::~IGame()
{
	DELETE_OBJECT( m_manager );

	Global::use().game = 0;
	Global::use().manager = 0;
}

bool IGame::onProgress()
{
	if( !m_isRunning || !m_manager->getActiveState() )
		return( false );
	Engine::LoopResult lr = m_manager->m_engine->processLoop();
	if( lr == Engine::lrQuit )
		return( false );
	if( lr == Engine::lrLogic )
	{
		InputManager::use().refreshMousePos();
		if(	InputManager::use().getKey( InputManager::iePressed, InputManager::ibAny )		||
			InputManager::use().getKey( InputManager::ieReleased, InputManager::ibAny )		||
			InputManager::use().getKey( InputManager::ieHold, InputManager::ibAny )			||
			InputManager::use().getButton( InputManager::iePressed, InputManager::ibAny )	||
			InputManager::use().getButton( InputManager::ieReleased, InputManager::ibAny )	||
			InputManager::use().getButton( InputManager::ieHold, InputManager::ibAny )		||
			InputManager::use().mouseIsMoved()
			)
			m_manager->getActiveState()->onInput();
		m_manager->getActiveState()->onUpdate();
		if( m_renderInterval > 0.0f )
		{
			m_renderIntervalAccel += m_manager->m_engine->getDeltaTime();
			if( m_renderIntervalAccel >= m_renderInterval )
			{
				m_renderIntervalAccel = fmodf( m_renderIntervalAccel, m_renderInterval );
				m_manager->getActiveState()->onRender();
			}
		}
		else
			m_manager->getActiveState()->onRender();
		if( m_manager->m_popState )
		{
			m_manager->_popState( m_manager->m_progressState );
			m_manager->m_popState = false;
		}
		if( m_manager->m_pushState )
		{
			m_manager->_pushState( m_manager->m_pushState, m_manager->m_progressState );
			m_manager->m_pushState = 0;
		}
		m_manager->m_changeState = false;
		DELETE_OBJECT( m_manager->m_progressState );
		InputManager::use().clear( true );
		InputManager::use().clearAfter();
	}
	return( true );
}

void IGame::run( IState* s, IProgressState* p )
{
	m_isRunning = true;
	m_manager->_pushState( s, p );
	while( onProgress() ){}
	while( m_manager->_popState( 0 ) ){}
	m_isRunning = false;
	DELETE_OBJECT( p );
}

void IGame::terminate()
{
	m_isRunning = false;
}

Manager* IGame::getManager()
{
	return( m_manager );
}

void IGame::setRenderInterval( float i )
{
	m_renderInterval = i;
}

float IGame::getRenderInterval()
{
	return( m_renderInterval );
}
