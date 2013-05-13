#include "InputManager.h"
#include "Engine.h"

InputManager::InputManager():
m_pressOnce( false ),
m_wheelDelta( 0 ),
m_characters( 0 )
{
	for( int i = 0; i < 256; i++ )
	{
		m_keysPressed[ i ] = false;
		m_keysHold[ i ] = false;
		m_keysReleased[ i ] = false;
		m_keysAfter[ i ] = false;
	}
	for( int i = 0; i < ibCount; i++ )
	{
		m_buttonsPressed[ i ] = false;
		m_buttonsHold[ i ] = false;
		m_buttonsReleased[ i ] = false;
		m_buttonsAfter[ i ] = false;
	}
	m_mousePos.x = 0;
	m_mousePos.y = 0;
	m_lastMousePos.x = 0;
	m_lastMousePos.y = 0;
}

InputManager::~InputManager()
{
	charactersClear();
}

bool InputManager::getKey( InputEvent ie, int code )
{
	if( ie < 0 || ie > ieCount || code < 0 || code >= 256 )
		return( false );
	if( ie == iePressed )
		return( m_keysPressed[ code ] );
	else
	if( ie == ieHold )
		return( m_keysHold[ code ] );
	else
	if( ie == ieReleased )
		return( m_keysReleased[ code ] );
	else
	if( ie == ieAfter )
		return( m_keysAfter[ code ] );
	return( false );
}

bool InputManager::getButton( InputEvent ie, InputButton btn )
{
	if( ie < 0 || ie > ieCount || btn < 0 || btn >= ibCount )
		return( false );
	if( ie == iePressed )
		return( m_buttonsPressed[ btn ] );
	else
	if( ie == ieHold )
		return( m_buttonsHold[ btn ] );
	else
	if( ie == ieReleased )
		return( m_buttonsReleased[ btn ] );
	else
	if( ie == ieAfter )
		return( m_buttonsAfter[ btn ] );
	return( false );
}

void InputManager::refreshMousePos()
{
	m_lastMousePos = m_mousePos;
	GetCursorPos( &m_mousePos );
}

void InputManager::getMousePos( int& x, int& y, bool winrelative )
{
	x = m_mousePos.x;
	y = m_mousePos.y;
	if( winrelative )
	{
		Engine::WindowRect wr;
		Global::use().engine->getWindowRect( wr );
		x -= wr.x;
		y -= wr.y;
	}
}

XeCore::XeHalfVector& InputManager::getMouseVec( bool winrelative )
{
	m_mousePosVec = XeCore::XeHalfVector( static_cast<float>(m_mousePos.x), static_cast<float>(m_mousePos.y) );
	if( winrelative )
	{
		Engine::WindowRect wr;
		Global::use().engine->getWindowRect( wr );
		m_mousePosVec.X -= (float)wr.x;
		m_mousePosVec.Y -= (float)wr.y;
	}
	return( m_mousePosVec );
}

void InputManager::getLastMousePos( int& x, int& y, bool winrelative )
{
	x = m_lastMousePos.x;
	y = m_lastMousePos.y;
	if( winrelative )
	{
		Engine::WindowRect wr;
		Global::use().engine->getWindowRect( wr );
		x -= wr.x;
		y -= wr.y;
	}
}

XeCore::XeHalfVector& InputManager::getLastMouseVec( bool winrelative )
{
	m_lastMousePosVec = XeCore::XeHalfVector( static_cast<float>(m_lastMousePos.x), static_cast<float>(m_lastMousePos.y) );
	if( winrelative )
	{
		Engine::WindowRect wr;
		Global::use().engine->getWindowRect( wr );
		m_lastMousePosVec.X -= (float)wr.x;
		m_lastMousePosVec.Y -= (float)wr.y;
	}
	return( m_lastMousePosVec );
}

char InputManager::getLastCharacter( bool pop )
{
	char c( 0 );
	popCharacter( c, !pop );
	return( c );
}

bool InputManager::mouseIsMoved()
{
	return( m_mousePos.x != m_lastMousePos.x || m_mousePos.y != m_lastMousePos.y );
}

int InputManager::getWheelDelta()
{
	return( m_wheelDelta );
}

void InputManager::setKey( InputEvent ie, int code, bool mode )
{
	if( ie < 0 || ie > ieCount || code < 0 || code >= 256 )
		return;
	if( ie == iePressed )
		m_keysPressed[ code ] = mode;
	else
	if( ie == ieHold )
		m_keysHold[ code ] = mode;
	else
	if( ie == ieReleased )
		m_keysReleased[ code ] = mode;
	else
	if( ie == ieAfter )
		m_keysAfter[ code ] = mode;
}

void InputManager::setButton( InputEvent ie, InputButton btn, bool mode )
{
	if( ie < 0 || ie > ieCount || btn < 0 || btn >= ibCount )
		return;
	if( ie = iePressed )
		m_buttonsPressed[ btn ] = mode;
	else
	if( ie = ieHold )
		m_buttonsHold[ btn ] = mode;
	else
	if( ie = ieReleased )
		m_buttonsReleased[ btn ] = mode;
	else
	if( ie = ieAfter )
		m_buttonsAfter[ btn ] = mode;
}

void InputManager::setMousePos( int x, int y )
{
	m_mousePos.x = x;
	m_mousePos.y = y;
	SetCursorPos( x, y );
}

void InputManager::setMouseVec( XeCore::XeHalfVector& pos )
{
	m_mousePos.x = static_cast<int>(pos.X);
	m_mousePos.y = static_cast<int>(pos.Y);
}

void InputManager::clearAfter()
{
	for( int i = 0; i < 256; i++ )
		if( m_keysAfter[ i ] )
		{
			m_keysPressed[ i ] = false;
			m_keysHold[ i ] = false;
			m_keysReleased[ i ] = false;
		}
	for( int i = 0; i < ibCount; i++ )
		if( m_buttonsAfter[ i ] )
		{
			m_buttonsPressed[ i ] = false;
			m_buttonsHold[ i ] = false;
			m_buttonsReleased[ i ] = false;
		}
	m_wheelDelta = 0;
}

void InputManager::clear( bool nothold )
{
	for( int i = 0; i < 256; i++ )
	{
		m_keysPressed[ i ] = false;
		if( !nothold )
			m_keysHold[ i ] = false;
		m_keysReleased[ i ] = false;
		m_keysAfter[ i ] = false;
	}
	for( int i = 0; i < ibCount; i++ )
	{
		m_buttonsPressed[ i ] = false;
		if( !nothold )
			m_buttonsHold[ i ] = false;
		m_buttonsReleased[ i ] = false;
		m_buttonsAfter[ i ] = false;
	}
}

void InputManager::pushCharacter( char c )
{
#if defined( XMM_MEMORY_TRACING_MODE )
	CharacterList* n = (CharacterList*)MemoryManager::_newDebug( sizeof( CharacterList ), __FILE__, __LINE__ );
#else
	CharacterList* n = (CharacterList*)MemoryManager::_new( sizeof( CharacterList ) );
#endif
	if( n )
	{
		n->value = c;
		CharacterList* p = m_characters;
		m_characters = n;
		n->prev = p;
	}
}

bool InputManager::popCharacter( char& c, bool leave )
{
	if( !m_characters )
		return( false );
	c = m_characters->value;
	if( !leave )
	{
		CharacterList* p = m_characters->prev;
#if defined( XMM_MEMORY_TRACING_MODE )
		MemoryManager::_deleteDebug( m_characters );
#else
		MemoryManager::_delete( m_characters );
#endif
		m_characters = p;
	}
	return( true );
}

bool InputManager::popString( XeCore::XeString& s, bool leave )
{
	if( !m_characters )
		return( false );
	s.Clear();
	CharacterList* t = m_characters;
	while( t )
	{
		s << ( &t->value );
		t = m_characters->prev;
	}
	if( !leave )
		charactersClear();
	return( true );
}

unsigned int InputManager::charactersCount()
{
	unsigned int s( 0 );
	CharacterList* t = m_characters;
	while( t )
	{
		s++;
		t = m_characters->prev;
	}
	return( s );
}

void InputManager::charactersClear()
{
	char c;
	while( popCharacter( c ) ) {};
}
