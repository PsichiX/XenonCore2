#pragma once

#include "../XeFramework/IActor.h"
#include "../XeFramework/RenderTechnique.h"

class Logo : public virtual IRtti, public IActor, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Logo );

public:
							Logo();
							~Logo();
	void					update();
	void					input();
	void					render();

private:
	SpriteBatch::Sprite*	m_sprite;
};