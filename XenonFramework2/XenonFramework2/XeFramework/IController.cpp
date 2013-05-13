#include "IController.h"

RTTI_CLASS_DERIVATIONS(	IController,
						RTTI_DERIVATIONS_END
						);

IController::IController():
RTTI_CLASS_DEFINE( IController ),
m_actor( 0 )
{
}

IController::~IController()
{
}

IActor* IController::getActor()
{
	return( m_actor );
}
