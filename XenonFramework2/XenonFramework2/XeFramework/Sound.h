#pragma once

#include "IRtti.h"
#include "Audiere/audiere.h"
#include "AudioManager.h"
#include "Asset.h"

class Sound : public virtual IRtti, public Asset, public Audio, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Sound );

public:
								Sound( NameID& name, AudioManager* m );
								~Sound();
	bool						load( const char* fname );
	bool						load( void* data, int size );
	void						free();
	void						play();
	void						stop();
	void						setVolume( float v );
	void						setPan( float v );
	void						setPitch( float v );
	float						getVolume();
	float						getPan();
	float						getPitch();

	static Asset*				onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways );
	virtual void				onUnload();

private:
	AudioManager*				m_manager;
	NameID						m_name;
	audiere::SoundEffectPtr		m_sound;
	audiere::FilePtr			m_file;
};
