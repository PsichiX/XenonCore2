#include "Skeleton.h"
#include "IScene.h"

RTTI_CLASS_DERIVATIONS(	Skeleton,
						RTTI_DERIVATIONS_END
						);

Skeleton::Skeleton():
RTTI_CLASS_DEFINE( Skeleton ),
m_root( 0 ),
m_scale( 1.0f, 1.0f, 1.0f )
{
	m_root = xnew Node( NameID( "root" ) );
}

Skeleton::~Skeleton()
{
	DELETE_OBJECT( m_root );
}

Skeleton::Node* Skeleton::getRoot()
{
	return( m_root );
}

void Skeleton::setPosition( XeCore::XeHalfVector& v )
{
	m_position = v;
}

void Skeleton::setRotation( XeCore::XeAngleHalfVector& v )
{
	m_rotation = v;
}

void Skeleton::setScale( XeCore::XeHalfVector& v )
{
	m_scale = v;
}

XeCore::XeHalfVector& Skeleton::getPosition()
{
	return( m_position );
}

XeCore::XeAngleHalfVector& Skeleton::getRotation()
{
	return( m_rotation );
}

XeCore::XeHalfVector& Skeleton::getScale()
{
	return( m_scale );
}

void Skeleton::update()
{
	m_root->applyTransform( m_position, m_rotation, m_scale );
}

RTTI_CLASS_DERIVATIONS(	Skeleton::Node,
						RTTI_DERIVATIONS_END
						);

Skeleton::Node::Node( NameID& name ):
RTTI_CLASS_DEFINE( Skeleton::Node ),
m_name( name ),
m_object( 0 ),
m_removeable( false ),
m_boneLength( 0.0f ),
m_boneScale( 1.0f, 1.0f, 1.0f )
{
}

Skeleton::Node::~Node()
{
	detach();
	for( XeCore::XeElementPointer< Node* > n = m_nodes.FirstPointer(); !n.IsEmpty(); n.Next() )
	{
		Node* node = n();
		DELETE_OBJECT( node );
	}
	m_nodes.Clear();
}

void Skeleton::Node::attach( IRenderable* object )
{
	detach();
	m_object = object;
}

void Skeleton::Node::detach()
{
	if( m_removeable && m_object )
		DELETE_OBJECT( m_object );
	m_object = 0;
}

IRenderable* Skeleton::Node::getObject()
{
	return( m_object );
}

void Skeleton::Node::setRemoveable( bool mode )
{
	m_removeable = mode;
}

void Skeleton::Node::setBoneRotation( XeCore::XeAngleHalfVector& v )
{
	m_boneRotation = v;
}

void Skeleton::Node::setBoneLength( float v )
{
	m_boneLength = v;
}

bool Skeleton::Node::getRemoveable()
{
	return( m_removeable );
}

XeCore::XeAngleHalfVector& Skeleton::Node::getBoneRotation()
{
	return( m_boneRotation );
}

float Skeleton::Node::getBoneLength()
{
	return( m_boneLength );
}

bool Skeleton::Node::applyTransform( XeCore::XeHalfVector& p, XeCore::XeAngleHalfVector& r, XeCore::XeHalfVector& s )
{
	if( !m_object )
		return( false );
	XeCore::XeHalfVector scale = m_boneScale * s;
	XeCore::XeAngleHalfVector rot = r + m_boneRotation;
	float rad = (float)PI * rot.Alpha / 180.0f;
	XeCore::XeHalfVector pos = p + ( XeCore::XeHalfVector( cos( rad ) * m_boneLength, sin( rad ) * m_boneLength ) * scale );
	m_object->setPosition( pos );
	m_object->setRotation( rot );
	m_object->setScale( scale );
	for( XeCore::XeElementPointer< Node* > n = m_nodes.FirstPointer(); !n.IsEmpty(); n.Next() )
		n()->applyTransform( pos, rot, scale );
	return( true );
}

bool Skeleton::Node::addNode( NameID& name )
{
	if( findNode( name ) )
		return( false );
	Node* node = xnew Node( name );
	if( m_nodes.AddPointer( node ).IsEmpty() )
	{
		DELETE_OBJECT( node );
		return( false );
	}
	return( true );
}

bool Skeleton::Node::removeNode( NameID& name )
{
	for( XeCore::XeElementPointer< Node* > n = m_nodes.FirstPointer(); !n.IsEmpty(); n.Next() )
		if( n() && n()->m_name == name )
		{
			Node* node = n();
			DELETE_OBJECT( node );
			m_nodes.ErasePointer( n );
			return( true );
		}
	return( false );
}

Skeleton::Node* Skeleton::Node::findNode( NameID& name )
{
	for( XeCore::XeElementPointer< Node* > n = m_nodes.FirstPointer(); !n.IsEmpty(); n.Next() )
		if( n()->m_name == name )
			return( n() );
	return( 0 );
}
