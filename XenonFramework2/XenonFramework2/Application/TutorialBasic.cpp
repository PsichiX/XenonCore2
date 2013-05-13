#include "../XeFramework/Base.h"
#include "../XeFramework/Manager.h"
#include "TutorialBasic.h"

RTTI_CLASS_DERIVATIONS(	TutorialBasic,
						RTTI_DERIVATION( IState ),
						RTTI_DERIVATIONS_END
						);

TutorialBasic::TutorialBasic():
RTTI_CLASS_DEFINE( TutorialBasic )
{
}

TutorialBasic::~TutorialBasic()
{
}

void TutorialBasic::onEnter( IProgressState* p )
{
	LOGNL( "* Enter state: TutorialBasic" );

	PROGRESS_STATE_UPDATE( p );
}

void TutorialBasic::onExit()
{
	LOGNL( "* Exit state: TutorialBasic" );
}

void TutorialBasic::onUpdate()
{
	GLOBAL.manager->update();
}

void TutorialBasic::onRender()
{
	GLOBAL.manager->render();
	GLOBAL.engine->flush();
	GLOBAL.engine->render();
}

void TutorialBasic::onInput()
{
	GLOBAL.manager->input();

	if( KEY_PRESSED( Input::kESC ) )
		GLOBAL.manager->popState();

	if( KEY_HOLD( Input::kCTRL ) && KEY_PRESSED( Input::kTYLDE ) )
	{
		ENTER_RUNTIME_DEBUGGER;
	}
}
