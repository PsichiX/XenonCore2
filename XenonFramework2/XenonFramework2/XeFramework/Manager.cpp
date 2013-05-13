#include "Manager.h"

RTTI_CLASS_DERIVATIONS(	Manager,
						RTTI_DERIVATIONS_END
						);

Manager::Manager( const char* name, int width, int height, Engine::WindowMode wm ):
RTTI_CLASS_DEFINE( Manager ),
m_engine( 0 ),
m_game( 0 ),
m_pushState( 0 ),
m_progressState( 0 ),
m_progressStateDefault( 0 ),
m_popState( false ),
m_changeState( false ),
m_loading( false ),
m_states( 0 ),
m_scenes( 0 ),
m_materials( 0 ),
m_effects( 0 ),
m_fonts( 0 ),
m_textures( 0 ),
m_canvases( 0 ),
m_assets( 0 ),
m_assetsLoading( 0 ),
m_actors( 0 ),
m_controls( 0 ),
m_collisions( 0 ),
m_audio( 0 )
{
	m_engine = xnew Engine();
	m_engine->initiation( name, width, height, wm );
	m_states = xnew Stack< IState >();
	m_scenes = xnew SceneManager();
	m_materials = xnew MaterialManager();
	m_effects = xnew EffectManager();
	m_fonts = xnew FontManager();
	m_textures = xnew TextureManager();
	m_canvases = xnew CanvasManager();
	m_assets = xnew AssetManager();
	m_assetsLoading = xnew AssetManager();
	m_actors = xnew Stack< ActorManager >();
	m_controls = xnew Stack< ControlManager >();
	m_collisions = xnew Stack< CollisionManager >();
	m_audio = xnew AudioManager();

	Global::use().engine = m_engine;
	Global::use().scenes = m_scenes;
	Global::use().materials = m_materials;
	Global::use().effects = m_effects;
	Global::use().fonts = m_fonts;
	Global::use().textures = m_textures;
	Global::use().canvases = m_canvases;
	Global::use().assets = m_assets;
	Global::use().assetsLoading = m_assetsLoading;
	Global::use().actors = 0;
	Global::use().controls = 0;
	Global::use().collisions = 0;
	Global::use().audio = m_audio;
}

Manager::~Manager()
{
	while( m_actors->current() )
	{
		ActorManager* am = m_actors->current();
		DELETE_OBJECT( am );
		m_actors->pop();
	}

	DELETE_OBJECT( m_assets );
	Global::use().assets = 0;
	DELETE_OBJECT( m_assetsLoading );
	Global::use().assetsLoading = 0;
	DELETE_OBJECT( m_actors );
	Global::use().actors = 0;
	DELETE_OBJECT( m_controls );
	Global::use().controls = 0;
	DELETE_OBJECT( m_collisions );
	Global::use().collisions = 0;
	DELETE_OBJECT( m_effects );
	Global::use().effects = 0;
	DELETE_OBJECT( m_fonts );
	Global::use().fonts = 0;
	DELETE_OBJECT( m_textures );
	Global::use().textures = 0;
	DELETE_OBJECT( m_canvases );
	Global::use().canvases = 0;
	DELETE_OBJECT( m_materials );
	Global::use().materials = 0;
	DELETE_OBJECT( m_scenes );
	Global::use().scenes = 0;
	DELETE_OBJECT( m_audio );
	Global::use().audio = 0;

	m_engine->closure();
	DELETE_OBJECT( m_engine );
	Global::use().engine = 0;
	DELETE_OBJECT( m_states );
	m_game = 0;

	DELETE_OBJECT( m_progressStateDefault );
}

void Manager::pushState( IState* newstate, IProgressState* newpstate )
{
	m_pushState = newstate;
	m_progressState = newpstate;
}

void Manager::popState( IProgressState* newpstate )
{
	m_popState = true;
	m_progressState = newpstate;
}

void Manager::changeState( IState* newstate, IProgressState* newpstate )
{
	m_changeState = true;
	m_popState = true;
	m_pushState = newstate;
	m_progressState = newpstate;
}

void Manager::setDefaultProgressState( IProgressState* newpstate )
{
	DELETE_OBJECT( m_progressStateDefault );
	m_progressStateDefault = newpstate;
}

bool Manager::_pushState( IState* newstate, IProgressState* newpstate )
{
	if( !newstate )
		return( false );
	if( !newpstate )
		newpstate = m_progressStateDefault;
	IState* c = m_states->current();
	if( m_states->push( newstate ) )
	{
		if( !m_changeState && c )
		{
			m_engine->resetTimer();
			c->onExit();
			m_engine->resetTimer();
		}
		m_actors->push( xnew ActorManager() );
		Global::use().actors = m_actors->current();
		m_controls->push( xnew ControlManager() );
		Global::use().controls = m_controls->current();
		m_collisions->push( xnew CollisionManager() );
		Global::use().collisions = m_collisions->current();
		if( newpstate )
		{
			m_loading = true;
			newpstate->onEnter();
			m_loading = false;
		}
		m_engine->resetTimer();
		newstate->onEnter( newpstate );
		m_engine->resetTimer();
		if( newpstate )
		{
			m_loading = true;
			newpstate->onExit();
			m_loading = false;
			m_assetsLoading->releaseLevel( m_states->count() );
		}
		return( true );
	}
	return( false );
}

bool Manager::_popState( IProgressState* newpstate )
{
	if( !m_states->current() )
		return( false );
	if( !newpstate )
		newpstate = m_progressStateDefault;
	m_engine->resetTimer();
	m_states->current()->onExit();
	m_engine->resetTimer();
	ActorManager* am = m_actors->current();
	DELETE_OBJECT( am );
	m_actors->pop();
	ControlManager* ctm = m_controls->current();
	DELETE_OBJECT( ctm );
	m_controls->pop();
	CollisionManager* clm = m_collisions->current();
	DELETE_OBJECT( clm );
	m_collisions->pop();
	IState* s = m_states->current();
	DELETE_OBJECT( s );
	m_states->pop();
	m_assets->releaseLevel( m_states->count() + 1 );
	IState* c = m_states->current();
	if( !m_changeState && c )
	{
		if( newpstate )
		{
			m_loading = true;
			newpstate->onEnter();
			m_loading = false;
		}
		m_engine->resetTimer();
		c->onEnter( newpstate );
		m_engine->resetTimer();
		if( newpstate )
		{
			m_loading = true;
			newpstate->onExit();
			m_loading = false;
			m_assetsLoading->releaseLevel( m_states->count() + 1 );
		}
	}
	return( true );
}

XeCore::XeHandle Manager::loadingUpdate( XeCore::XePointer input, XeCore::XeDword size )
{
	struct sLoadingDesc{
		IProgressState* p;
		unsigned int s;
	};
	sLoadingDesc* in = (sLoadingDesc*)input;
	while( true )
	{
		in->p->onProgress();
		Sleep( in->s );
	}
}

IState* Manager::getActiveState()
{
	return( m_states->current() );
}

unsigned int Manager::getStatesCount()
{
	return( m_states->count() );
}

bool Manager::isLoadingState()
{
	return( m_loading );
}

void Manager::update()
{
	m_scenes->update();
	m_collisions->current()->update();
	m_controls->current()->update();
	m_actors->current()->update();
}

void Manager::input()
{
	m_actors->current()->input();
	m_controls->current()->input();
}

void Manager::render()
{
	m_scenes->render();
	m_actors->current()->render();
}