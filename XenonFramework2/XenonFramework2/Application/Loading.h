#pragma once

#include "../XeFramework/IRtti.h"
#include "../XeFramework/IProgressState.h"
#include "../XeFramework/SpriteBatch.h"

class Manager;

class Loading : public virtual  IRtti, public IProgressState, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Loading );

public:
								Loading();
								~Loading();
	void						onEnter();
	void						onExit();
	bool						onProgress();

private:
	SpriteBatch::Text*			m_text;
	int							m_dots;
};
