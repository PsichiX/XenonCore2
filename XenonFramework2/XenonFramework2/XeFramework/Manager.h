#pragma once

#include "XenonFramework2.h"
#include "IRtti.h"
#include "Stack.h"
#include "IState.h"
#include "IProgressState.h"
#include "SceneManager.h"
#include "MaterialManager.h"
#include "EffectManager.h"
#include "FontManager.h"
#include "TextureManager.h"
#include "CanvasManager.h"
#include "AssetManager.h"
#include "ActorManager.h"
#include "ControlManager.h"
#include "CollisionManager.h"
#include "AudioManager.h"

class IGame;

class Manager : public virtual IRtti, public virtual MemoryManager::Manageable
{
	friend class IGame;
	friend class RuntimeDebugger;

	RTTI_CLASS_DECLARE( Manager );

public:
											Manager( const char* name, int width = 0, int height = 0, Engine::WindowMode wm = Engine::wmWindowed );
											~Manager();
	void									pushState( IState* newstate, IProgressState* newpstate = 0 );
	void									popState( IProgressState* newpstate = 0 );
	void									changeState( IState* newstate, IProgressState* newpstate = 0 );
	void									setDefaultProgressState( IProgressState* newpstate );
	IState*									getActiveState();
	unsigned int							getStatesCount();
	bool									isLoadingState();
	void									update();
	void									input();
	void									render();

private:
	bool									_pushState( IState* newstate, IProgressState* newpstate );
	bool									_popState( IProgressState* newpstate );
	static XeCore::XeHandle					loadingUpdate( XeCore::XePointer input, XeCore::XeDword size );

	Engine*									m_engine;
	IGame*									m_game;
	IState*									m_pushState;
	IProgressState*							m_progressState;
	IProgressState*							m_progressStateDefault;
	bool									m_popState;
	bool									m_changeState;
	bool									m_loading;
	Stack< IState >*						m_states;
	SceneManager*							m_scenes;
	MaterialManager*						m_materials;
	EffectManager*							m_effects;
	FontManager*							m_fonts;
	TextureManager*							m_textures;
	CanvasManager*							m_canvases;
	AssetManager*							m_assets;
	AssetManager*							m_assetsLoading;
	Stack< ActorManager >*					m_actors;
	Stack< ControlManager >*				m_controls;
	Stack< CollisionManager >*				m_collisions;
	AudioManager*							m_audio;
};
