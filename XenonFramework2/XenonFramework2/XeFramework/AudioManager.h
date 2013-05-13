#pragma once

#include "IRtti.h"
#include "INamedItemsManager.h"
#include "Audiere/audiere.h"

#pragma comment(lib,"XeFramework/Audiere/audiere.lib")

class Audio;
class Music;
class Sound;

class AudioManager : public virtual IRtti, public INamedItemsManager< NameID, Audio >, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( AudioManager );

public:
								AudioManager();
								~AudioManager();
	audiere::AudioDevicePtr		getDevice();
	Music*						getMusic( NameID& name );
	Sound*						getSound( NameID& name );

private:
	audiere::AudioDevicePtr		m_device;

protected:
	bool						attach( NameID& n, Audio* i ) { return( false ); }
	bool						detach( NameID& n ) { return( false ); }
};

class Audio : public virtual IRtti, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Audio );

public:
	Audio();
	~Audio();
};