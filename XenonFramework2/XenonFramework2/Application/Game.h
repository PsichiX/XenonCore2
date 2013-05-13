#pragma once

#include "../XeFramework/IRtti.h"
#include "../XeFramework/IGame.h"

class Game : public virtual IRtti, public IGame
{
	RTTI_CLASS_DECLARE( Game );

public:
	Game( char* name, int width = 0, int height = 0, Engine::WindowMode wm = Engine::wmWindowed );
	~Game();
};
