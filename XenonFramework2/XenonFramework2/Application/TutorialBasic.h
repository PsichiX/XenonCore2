#pragma once

#include "../XeFramework/IRtti.h"
#include "../XeFramework/IState.h"

class TutorialBasic : public virtual IRtti, public IState
{
	RTTI_CLASS_DECLARE( TutorialBasic );

public:
									TutorialBasic();
									~TutorialBasic();
	void							onEnter( IProgressState* p );
	void							onExit();
	void							onUpdate();
	void							onRender();
	void							onInput();

private:
};
