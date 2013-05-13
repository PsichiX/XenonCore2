#pragma once

/*=== PROTOTYPE ===*/

#include "IRtti.h"
#include "ShapePool.h"
#include "Asset.h"

class ParticlesStream : public virtual IRtti, public Asset, public ShapePool, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( ParticlesStream );

public:
	struct UnitDescription
	{
		float							lifetime;
		XeCore::XeHalfVector			position;
		XeCore::XeHalfVector			scale;
		XeCore::XeHalfVector			color;
		XeCore::XeHalfVector			velocity;
	};

	class UnitControler : public virtual IRtti, public virtual MemoryManager::Manageable
	{
		RTTI_CLASS_DECLARE( ParticlesStream::UnitControler );

	public:
														UnitControler();
														~UnitControler();
		XeCore::XeArray< XeCore::XeHalfVector >			velocity;
		XeCore::XeArray< XeCore::XeHalfVector >			position;
		XeCore::XeArray< XeCore::XeAngleHalfVector >	direction;
		XeCore::XeArray< XeCore::XeHalfVector >			scale;
		XeCore::XeArray< XeCore::XeHalfVector >			color;
	};

	class Unit
	{
		friend class ParticlesStream;

	public:
										Unit();
										~Unit();
	private:
		void							create( ParticlesStream* sys, UnitDescription& d, UnitControler* c = 0 );
		void							update( ParticlesStream* sys, float dt );
		void							destroy( ParticlesStream* sys );
		void							transform( XeCore::XeHalfMatrix& mat );

		bool							m_active;
		VertexStruct*					m_vertices;
		XeCore::XeHalfVector			m_posStart;
		float							m_lifeTime;
		float							m_lifeTimeLimit;
		XeCore::XeHalfVector			m_velocity;
		XeCore::XeHalfVector			m_position;
		XeCore::XeAngleHalfVector		m_direction;
		XeCore::XeHalfVector			m_scale;
		XeCore::XeHalfVector			m_color;
		UnitControler*					m_controler;
	};

	struct GenerationDescription
	{
		float							lifetimeMin;
		float							lifetimeMax;
		XeCore::XeHalfVector			position;
		XeCore::XeHalfVector			offsetMin;
		XeCore::XeHalfVector			offsetMax;
		XeCore::XeHalfVector			scaleMin;
		XeCore::XeHalfVector			scaleMax;
		XeCore::XeHalfVector			colorMin;
		XeCore::XeHalfVector			colorMax;
		XeCore::XeHalfVector			velocityMin;
		XeCore::XeHalfVector			velocityMax;
		unsigned int					countMin;
		unsigned int					countMax;
	};

	/*class Emitter : public virtual IRtti, public virtual MemoryManager::Manageable
	{
		RTTI_CLASS_DECLARE( Emitter );

	public:
										Emitter();
										~Emitter();
		void							update();
		GenerationDescription&			access() { return( m_desc ); }

	private:
		bool							m_active;
		GenerationDescription			m_desc;
	};*/

										ParticlesStream( unsigned int capacity, bool doublebuff = true, bool pointsprites = false );
										~ParticlesStream();
	void								update();
	void								render();
	bool								generate( GenerationDescription& d, UnitControler* cnt = 0 );
	bool								kill( Unit* u );
	FORCEINLINE void					setMaterial( Material* m )		{ setStaticMaterial( m ); }
	FORCEINLINE Material*				getMaterial()					{ return( getStaticMaterial() ); }
	FORCEINLINE unsigned int			getCount()						{ return( m_units.Size() - m_freeUnitsCount ); }
	FORCEINLINE bool					usesPointSprites()				{ return( m_asPointSprites ); }
	FORCEINLINE void					setPointSpritesSize( float v )	{ m_pointSpritesSize = v; }
	FORCEINLINE float					getPointSpritesSize()			{ return( m_pointSpritesSize ); }

	static Asset*						onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways );
	virtual void						onUnload();

private:
	XeCore::XeArray< Unit >				m_units;
	XeCore::XeArray< Unit* >			m_freeUnits;
	unsigned int						m_freeUnitsCount;
	bool								m_asPointSprites;
	float								m_pointSpritesSize;
};