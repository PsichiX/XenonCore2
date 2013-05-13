#pragma once

#include "IRtti.h"
#include "Engine.h"
#include "IScene.h"
#include "IRenderable.h"
#include "Material.h"
#include "Font.h"
#include "../XeCore/Base/XeArray.h"
#include "../XeCore/Base/XeElements.h"

class ShapePool : public virtual IRtti, public IScene, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( ShapePool );

public:	
	class Shape;

	enum RenderMode
	{
		rmStatic,
		rmDynamic,
		rmStream,
		rmCount
	};

	struct VertexStruct
	{
		XeCore::XeHalfVector				position;
		XeCore::XeHalfVector				color;
		XeCore::XeHalfVector				coords;
		XeCore::XeHalfMatrix				matrix;
	};

	struct Vertex
	{
		friend class ShapePool;

											Vertex() : m_index( -1 ) {}
		unsigned int						getIndex() { return( m_index ); }
		VertexStruct						vertex;

	private:
		unsigned int						m_index;
	};

	enum StaticUpdateMode
	{
		sumNone		= 0,
		sumVertex	= BIT( 0 ),
		sumIndex	= BIT( 1 ),
	};

											ShapePool( unsigned int capacity, bool doublebuff = true, bool staticMode = false, RenderMode vertrm = rmDynamic, RenderMode indrm = rmStream );
											~ShapePool();
	void									render();
	void									update();
	void									optimize();
	void									rebuildRenderQueue();
	unsigned int							renderQueueCount( unsigned int id = 0 );
	FORCEINLINE void						swapBuffers()	{ m_doubleBuffCurr = !m_doubleBuffCurr; }
	FORCEINLINE unsigned int				currentBuffer()	{ return( m_doubleBuffCurr ? 1 : 0 ); }
	bool									attach( IRenderable* s );
	bool									detach( IRenderable* s );
	FORCEINLINE unsigned int				getCapacity() { return( m_capacity ); }
	FORCEINLINE bool						isStaticMode() { return( m_staticMode ); }
	FORCEINLINE void						setStaticRenderMode( XeCore::XeEstate mode ) { m_staticRenderMode = mode; }
	FORCEINLINE XeCore::XeEstate			getStaticRenderMode() { return( m_staticRenderMode ); }
	FORCEINLINE void						setStaticMaterial( Material* m ) { m_staticMaterial = m; }
	FORCEINLINE Material*					getStaticMaterial() { return( m_staticMaterial ); }
	FORCEINLINE VertexStruct*				getStaticVertices() { return( m_staticVetices.Get() ); }
	FORCEINLINE unsigned int*				getStaticIndices() { return( m_staticIndices.Get() ); }
	FORCEINLINE void						setStaticUpdateMode( XeCore::XeDword m ) { m_staticUpdateMode = m; }
	FORCEINLINE XeCore::XeDword				getStaticUpdateMode() { return( m_staticUpdateMode ); }

private:
	struct RenderChunk
	{
		Material*							material;
		XeCore::XeEstate					mode;
		unsigned int						first;
		unsigned int						last;
		IScene*								scene;
	};

	bool									rebuild( unsigned int count, RenderMode vertrm = rmDynamic, RenderMode indrm = rmStream );
	bool									alloc( Shape* s );
	bool									dealloc( Shape* s );
	void									free();
	static int								sort( IRenderable** a, IRenderable** b );

	bool									m_doubleBuff;
	bool									m_doubleBuffCurr;
	unsigned int							m_capacity;
	unsigned int							m_rest;
	XeCore::Photon::XeElmVertexBuffer		m_vbo[2];
	XeCore::XeArray< XeCore::XeByte >		m_allocMap;
	unsigned int							m_allocMapPos;
	XeCore::XeElements< RenderChunk >		m_renderQueue[2];
	bool									m_staticMode;
	XeCore::XeArray< VertexStruct >			m_staticVetices;
	XeCore::XeArray< unsigned int >			m_staticIndices;
	Material*								m_staticMaterial;
	XeCore::XeEstate						m_staticRenderMode;
	XeCore::XeDword							m_staticUpdateMode;

public:
	class Shape : public virtual IRtti, public IRenderable, public virtual MemoryManager::Manageable
	{
		friend class ShapePool;

		RTTI_CLASS_DECLARE( Shape );

	public:
											Shape();
											~Shape();
		void								reserve( unsigned int count );
		unsigned int						size();
		void								setRenderMode( XeCore::XeEstate m );
		XeCore::XeEstate					getRenderMode();
		void								setMaterial( Material* m );
		Material*							getMaterial();
		Vertex*								access( unsigned int i );

	private:
		XeCore::XeArray< Vertex >			m_vertices;
		Material*							m_material;
		XeCore::XeEstate					m_renderMode;
	};

	class Text : public virtual IRtti, public Shape, public virtual MemoryManager::Manageable
	{
		friend class ShapePool;

		RTTI_CLASS_DECLARE( Text );

	public:
											Text();
											~Text();
		bool								build( Font* font = 0, const char* text = 0, XeCore::XeHalfVector& col = XeCore::XeHalfVector( 1.0f, 1.0f, 1.0f ) );
		bool								rebuild( Font* font, const char* text, XeCore::XeHalfVector& col = XeCore::XeHalfVector( 1.0f, 1.0f, 1.0f ) );
		void								changeColor( XeCore::XeHalfVector& col, unsigned int start = 0, unsigned int end = -1 );
		void								applyAlign( Font::Align a );
		float								getWidth();
		float								getHeight();
		float								getOffsetX();
		float								getOffsetY();

	private:
		float								m_width;
		float								m_height;
		float								m_offsetX;
		float								m_offsetY;
		XeCore::XeArray< unsigned int >		m_br;
	};
};
