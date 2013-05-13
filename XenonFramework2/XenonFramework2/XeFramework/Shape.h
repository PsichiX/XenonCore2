#pragma once

#include "IRtti.h"
#include "../Soul/Soul.h"
#include "../SoulFramework/IRenderable.h"

class Shape : public virtual IRtti, public IRenderable
{
	friend class Scene;

	RTTI_CLASS_DECLARE;

private:
	Soul::SOUL_ENUM					m_type;
	Soul::ITexture*					m_texture;
	unsigned int					m_size;
	Soul::Vector4*					m_vertices;
	Soul::Vector4*					m_colors;
	Soul::Vector4*					m_coords;
	unsigned int					m_iSize;
	unsigned int*					m_indices;
	Soul::Vector4					m_tempV4;
	unsigned int					m_tempUI;

public:
									Shape();
									~Shape();
	void							reserve( unsigned int c, unsigned int i = 0 );
	void							clear();
	Soul::SOUL_ENUM					getType();
	void							setType( Soul::SOUL_ENUM type );
	Soul::ITexture*					getTexture();
	void							setTexture( Soul::ITexture* t );
	Soul::Vector4&					vertice( unsigned int id );
	Soul::Vector4&					color( unsigned int id );
	Soul::Vector4&					coord( unsigned int id );
	unsigned int&					indice( unsigned int id );
};
