#pragma once

#include "IRtti.h"
#include "ShapePool.h"
#include "Asset.h"

class SpriteBatch : public virtual IRtti, public Asset, public ShapePool, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( SpriteBatch );

public:
								SpriteBatch( unsigned int capacity, bool doublebuff = true );
								~SpriteBatch();
	void						update();

	static Asset*				onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways );
	virtual void				onUnload();

	class Sprite : public virtual IRtti, public ShapePool::Shape, public virtual MemoryManager::Manageable
	{
		RTTI_CLASS_DECLARE( Sprite );

	public:
		enum FlipType
		{
			ftVertical,
			ftHorizontal,
			ftCount
		};

								Sprite();
								~Sprite();
		void					setColor( XeCore::XeHalfVector& col );
		XeCore::XeHalfVector&	getColor();
		void					setWidth( float v );
		float					getWidth();
		void					setHeight( float v );
		float					getHeight();
		void					setXoffset( float v );
		float					getXoffset();
		void					setYoffset( float v );
		float					getYoffset();
		void					setZdepth( float v );
		float					getZdepth();
		void					flip( FlipType ft );

	private:
		void					rebuild();

		float					m_width;
		float					m_height;
		float					m_xoffset;
		float					m_yoffset;
	};

	class CanvasSprite : virtual public IRtti, public Sprite, virtual public MemoryManager::Manageable
	{
		RTTI_CLASS_DECLARE( CanvasSprite );

	public:
		CanvasSprite( Canvas* canvas, Effect* effect );
		~CanvasSprite();

	private:
		Texture*				m_texture;
		Texture*				m_textureDepth;
		Material*				m_material;
	};
};