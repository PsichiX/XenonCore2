#pragma once

#include "IRtti.h"
#include "IRenderable.h"
#include "../XeCore/Base/XeElements.h"

class Skeleton : public virtual IRtti, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Skeleton );

public:
	class Node;

									Skeleton();
									~Skeleton();
	Node*							getRoot();
	void							setPosition( XeCore::XeHalfVector& v );
	void							setRotation( XeCore::XeAngleHalfVector& v );
	void							setScale( XeCore::XeHalfVector& v );
	XeCore::XeHalfVector&			getPosition();
	XeCore::XeAngleHalfVector&		getRotation();
	XeCore::XeHalfVector&			getScale();
	void							update();

private:
	Node*							m_root;
	XeCore::XeHalfVector			m_position;
	XeCore::XeAngleHalfVector		m_rotation;
	XeCore::XeHalfVector			m_scale;

public:
	class Node : public virtual IRtti, public virtual MemoryManager::Manageable
	{
		RTTI_CLASS_DECLARE( Node );

	public:
									Node( NameID& name );
									~Node();
		void						attach( IRenderable* object );
		void						detach();
		IRenderable*				getObject();
		void						setRemoveable( bool mode );
		void						setBoneRotation( XeCore::XeAngleHalfVector& v );
		void						setBoneLength( float v );
		void						setBoneScale( XeCore::XeHalfVector& v );
		bool						getRemoveable();
		XeCore::XeAngleHalfVector&	getBoneRotation();
		float						getBoneLength();
		XeCore::XeHalfVector&		getBoneScale();
		bool						applyTransform( XeCore::XeHalfVector& p, XeCore::XeAngleHalfVector& r, XeCore::XeHalfVector& s );
		bool						addNode( NameID& name );
		bool						removeNode( NameID& name );
		Node*						findNode( NameID& name );

	private:
		NameID						m_name;
		IRenderable*				m_object;
		bool						m_removeable;
		XeCore::XeAngleHalfVector	m_boneRotation;
		float						m_boneLength;
		XeCore::XeHalfVector		m_boneScale;
		XeCore::XeElements< Node* >	m_nodes;
	};
};