#pragma once

#include "Singleton.h"

class IGame;
class Manager;
class Engine;
class SceneManager;
class MaterialManager;
class EffectManager;
class FontManager;
class TextureManager;
class CanvasManager;
class AssetManager;
class ActorManager;
class ControlManager;
class CollisionManager;
class AudioManager;

class Global : public Singleton< Global >
{
public:
							Global();
							~Global();
	IGame*					game;
	Manager*				manager;
	Engine*					engine;
	SceneManager*			scenes;
	MaterialManager*		materials;
	EffectManager*			effects;
	FontManager*			fonts;
	TextureManager*			textures;
	CanvasManager*			canvases;
	AssetManager*			assets;
	AssetManager*			assetsLoading;
	ActorManager*			actors;
	ControlManager*			controls;
	CollisionManager*		collisions;
	AudioManager*			audio;
};