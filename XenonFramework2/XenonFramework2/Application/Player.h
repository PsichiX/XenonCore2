#pragma once

#include "../XeFramework/IActor.h"
#include "../XeFramework/IControllable.h"
#include "../XeFramework/ICollisional.h"
#include "../XeFramework/SpriteBatch.h"
#include "../XeFramework/Skeleton.h"

class Player : public virtual IRtti, public IActor, public IControllable, public ICollisional, public virtual MemoryManager::Manageable, public virtual MemoryManager::Printable
{
	RTTI_CLASS_DECLARE( Player );

public:
							Player( XeCore::XeHalfVector& pos );
							~Player();
	void					update();
	void					input();
	void					render();
	void					move( XeCore::XeHalfVector& relativePos );

private:
	Skeleton*				m_skeleton;
};