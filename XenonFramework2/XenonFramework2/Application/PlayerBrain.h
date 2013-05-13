#pragma once

#include "../XeFramework/IController.h"

class PlayerBrain : public virtual IRtti, public IController, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( PlayerBrain );

public:
			PlayerBrain();
			~PlayerBrain();
	void	update();
	void	input();
};