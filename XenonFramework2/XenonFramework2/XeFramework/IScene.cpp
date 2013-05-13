#include "IScene.h"

RTTI_CLASS_DERIVATIONS(	IScene,
						RTTI_DERIVATION( IRenderable ),
						RTTI_DERIVATIONS_END
						);

IScene::IScene():
RTTI_CLASS_DEFINE( IScene ),
m_camera( 0 ),
m_canvas( 0 )
{
}

IScene::~IScene()
{
	DELETE_OBJECT( m_camera );
}

void IScene::setCamera( Camera* newcamera )
{
	DELETE_OBJECT( m_camera );
	m_camera = newcamera;
}

Camera* IScene::getCamera()
{
	return( m_camera );
}

void IScene::setCanvas( Canvas* canvas )
{
	m_canvas = canvas;
}

Canvas* IScene::getCanvas()
{
	return( m_canvas );
}

bool IScene::attach( IRenderable* i )
{
	if( !i )
		return( false );
	if( i->m_parent )
		return( false );
	i->m_parent = this;
	return( IItemsManager< IRenderable >::attach( i ) );
}

bool IScene::detach( IRenderable* i )
{
	if( !i )
		return( false );
	if( i->m_parent != this )
		return( false );
	i->m_parent = 0;
	return( IItemsManager< IRenderable >::detach( i ) );
}

void IScene::setParent( IScene* parent, IRenderable* child )
{
	child->m_parent = parent;
}