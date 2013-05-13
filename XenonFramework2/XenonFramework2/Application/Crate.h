#pragma once

#include "../XeFramework/IActor.h"
#include "../XeFramework/ICollisional.h"
#include "../XeFramework/SpriteBatch.h"

class Crate : public virtual IRtti, public IActor, public ICollisional, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Crate );

public:
							Crate( XeCore::XeHalfVector& pos, float angle, float spdx, float spdy, float rot );
							~Crate();
	void					update();
	void					input();
	void					render();
	SpriteBatch::Sprite*	getSprite();

private:
	SpriteBatch::Sprite*	m_sprite;
	XeCore::XeHalfVector	m_spd;
	float					m_rot;
};