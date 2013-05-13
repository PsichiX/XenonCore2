#include "KernelEffects.h"

bool KernelEffects::applyKernelProperties( KernelType kt, KernelFilter kf, Material* m, float factor, int texunit, float* customkernel )
{
	float w( static_cast<float>(m->getTexture( texunit )->getRealWidth()) );
	float h( static_cast<float>(m->getTexture( texunit )->getRealHeight()) );
	float sw( 1.0f / w );
	float sh( 1.0f / h );

	float offset3x3[] = {
		sw * -1.0f, sh * -1.0f,		sw * 0.0f, sh * -1.0f,		sw * 1.0f, sh * -1.0f,
		sw * -1.0f, sh * 0.0f,		sw * 0.0f, sh * 0.0f,		sw * 1.0f, sh * 0.0f,
		sw * -1.0f, sh * 1.0f,		sw * 0.0f, sh * 1.0f,		sw * 1.0f, sh * 1.0f
	};
	float offset5x5[] = {
		sw * -2.0f, sh * -2.0f,		sw * -1.0f, sh * -2.0f,		sw * 0.0f, sh * -2.0f,		sw * 1.0f, sh * -2.0f,		sw * 2.0f, sh * -2.0f,
		sw * -2.0f, sh * -1.0f,		sw * -1.0f, sh * -1.0f,		sw * 0.0f, sh * -1.0f,		sw * 1.0f, sh * -1.0f,		sw * 2.0f, sh * -1.0f,
		sw * -2.0f, sh * 0.0f,		sw * -1.0f, sh * 0.0f,		sw * 0.0f, sh * 0.0f,		sw * 1.0f, sh * 0.0f,		sw * 2.0f, sh * 0.0f,
		sw * -2.0f, sh * 1.0f,		sw * -1.0f, sh * 1.0f,		sw * 0.0f, sh * 1.0f,		sw * 1.0f, sh * 1.0f,		sw * 2.0f, sh * 1.0f,
		sw * -2.0f, sh * 2.0f,		sw * -1.0f, sh * 2.0f,		sw * 0.0f, sh * 2.0f,		sw * 1.0f, sh * 2.0f,		sw * 2.0f, sh * 2.0f
	};
	float offset7x7[] = {
		sw * -3.0f, sh * -3.0f,		sw * -2.0f, sh * -3.0f,		sw * -1.0f, sh * -3.0f,		sw * 0.0f, sh * -3.0f,		sw * 1.0f, sh * -3.0f,		sw * 2.0f, sh * -3.0f,		sw * 3.0f, sh * -3.0f,
		sw * -3.0f, sh * -2.0f,		sw * -2.0f, sh * -2.0f,		sw * -1.0f, sh * -2.0f,		sw * 0.0f, sh * -2.0f,		sw * 1.0f, sh * -2.0f,		sw * 2.0f, sh * -2.0f,		sw * 3.0f, sh * -2.0f,
		sw * -3.0f, sh * -1.0f,		sw * -2.0f, sh * -1.0f,		sw * -1.0f, sh * -1.0f,		sw * 0.0f, sh * -1.0f,		sw * 1.0f, sh * -1.0f,		sw * 2.0f, sh * -1.0f,		sw * 3.0f, sh * -1.0f,
		sw * -3.0f, sh * 0.0f,		sw * -2.0f, sh * -0.0f,		sw * -1.0f, sh * 0.0f,		sw * 0.0f, sh * 0.0f,		sw * 1.0f, sh * 0.0f,		sw * 2.0f, sh * 0.0f,		sw * 3.0f, sh * 0.0f,
		sw * -3.0f, sh * 1.0f,		sw * -2.0f, sh * 1.0f,		sw * -1.0f, sh * 1.0f,		sw * 0.0f, sh * 1.0f,		sw * 1.0f, sh * 1.0f,		sw * 2.0f, sh * 1.0f,		sw * 3.0f, sh * 1.0f,
		sw * -3.0f, sh * 2.0f,		sw * -2.0f, sh * 2.0f,		sw * -1.0f, sh * 2.0f,		sw * 0.0f, sh * 2.0f,		sw * 1.0f, sh * 2.0f,		sw * 2.0f, sh * 2.0f,		sw * 3.0f, sh * 2.0f,
		sw * -3.0f, sh * 3.0f,		sw * -2.0f, sh * 3.0f,		sw * -1.0f, sh * 3.0f,		sw * 0.0f, sh * 3.0f,		sw * 1.0f, sh * 3.0f,		sw * 2.0f, sh * 3.0f,		sw * 3.0f, sh * 3.0f
	};

	float kernelZero3x3[] = {
		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f
	};
	float kernelZero5x5[] = {
		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		0.0f,		0.0f
	};
	float kernelZero7x7[] = {
		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,
	};

	float kernelGaussian3x3[] = {
		1.0f,		2.0f,		1.0f,
		2.0f,		4.0f,		2.0f,
		1.0f,		2.0f,		1.0f
	};
	float kernelGaussian5x5[] = {
		1.0f,		2.0f,		4.0f,		2.0f,		1.0f,
		2.0f,		4.0f,		8.0f,		4.0f,		2.0f,
		4.0f,		8.0f,		16.0f,		8.0f,		4.0f,
		2.0f,		4.0f,		8.0f,		4.0f,		2.0f,
		1.0f,		2.0f,		4.0f,		2.0f,		1.0f
	};
	float kernelGaussian7x7[] = {
		1.0f,		2.0f,		4.0f,		8.0f,		4.0f,		2.0f,		1.0f,
		2.0f,		4.0f,		8.0f,		16.0f,		8.0f,		4.0f,		2.0f,
		4.0f,		8.0f,		16.0f,		32.0f,		16.0f,		8.0f,		4.0f,
		8.0f,		16.0f,		32.0f,		64.0f,		32.0f,		16.0f,		8.0f,
		4.0f,		8.0f,		16.0f,		32.0f,		16.0f,		8.0f,		4.0f,
		2.0f,		4.0f,		8.0f,		16.0f,		8.0f,		4.0f,		2.0f,
		1.0f,		2.0f,		4.0f,		8.0f,		4.0f,		2.0f,		1.0f
	};

	float kernelMean3x3[] = {
		1.0f,		1.0f,		1.0f,
		1.0f,		1.0f,		1.0f,
		1.0f,		1.0f,		1.0f
	};
	float kernelMean5x5[] = {
		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,
		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,
		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,
		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,
		1.0f,		1.0f,		1.0f,		1.0f,		1.0f
	};
	float kernelMean7x7[] = {
		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,
		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,
		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,
		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,
		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,
		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,
		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,		1.0f,		1.0f
	};

	float kernelLaplacian3x3[] = {
		0.0f,		-1.0f,		0.0f,
		-1.0f,		4.0f,		-1.0f,
		0.0f,		-1.0f,		0.0f
	};
	float kernelLaplacian5x5[] = {
		0.0f,		0.0f,		-1.0f,		0.0f,		0.0f,
		0.0f,		-1.0f,		-2.0f,		-1.0f,		0.0f,
		-1.0f,		-2.0f,		16.0f,		-2.0f,		-1.0f,
		0.0f,		-1.0f,		-2.0f,		-1.0f,		0.0f,
		0.0f,		0.0f,		-1.0f,		0.0f,		0.0f
	};
	float kernelLaplacian7x7[] = {
		0.0f,		0.0f,		0.0f,		-1.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		-1.0f,		-2.0f,		-1.0f,		0.0f,		0.0f,
		0.0f,		-1.0f,		-2.0f,		-4.0f,		-2.0f,		-1.0f,		0.0f,
		-1.0f,		-2.0f,		-4.0f,		44.0f,		-4.0f,		-2.0f,		-1.0f,
		0.0f,		-1.0f,		-2.0f,		-4.0f,		-2.0f,		-1.0f,		0.0f,
		0.0f,		0.0f,		-1.0f,		-2.0f,		-1.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		-1.0f,		0.0f,		0.0f,		0.0f
	};

	float kernelEmboss3x3[] = {
		-2.0f,		0.0f,		0.0f,
		0.0f,		1.0f,		0.0f,
		0.0f,		0.0f,		2.0f
	};
	float kernelEmboss5x5[] = {
		-4.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		-2.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		1.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		2.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		0.0f,		4.0f
	};
	float kernelEmboss7x7[] = {
		-8.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		-4.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		-2.0f,		0.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		1.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		0.0f,		2.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		4.0f,		0.0f,
		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		0.0f,		8.0f,
	};

	float kernelSharpness3x3[] = {
		-1.0f,		-1.0f,		-1.0f,
		-1.0f,		9.0f,		-1.0f,
		-1.0f,		-1.0f,		-1.0f
	};
	float kernelSharpness5x5[] = {
		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,
		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,
		-1.0f,		-1.0f,		25.0f,		-1.0f,		-1.0f,
		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,
		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f
	};
	float kernelSharpness7x7[] = {
		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,
		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,
		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,
		-1.0f,		-1.0f,		-1.0f,		49.0f,		-1.0f,		-1.0f,		-1.0f,
		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,
		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,
		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f,		-1.0f
	};

	float* offset( 0 );
	float* kernel( 0 );
	int count( 0 );

	if( kt == kt3x3 )
	{
		offset = offset3x3;
		count = 9;
		if( kf == kfCustom )
			kernel = customkernel;
		else
		if( kf == kfZero )
			kernel = kernelZero3x3;
		else
		if( kf == kfGaussian )
			kernel = kernelGaussian3x3;
		else
		if( kf == kfMean )
			kernel = kernelMean3x3;
		else
		if( kf == kfLaplacian )
			kernel = kernelLaplacian3x3;
		else
		if( kf == kfEmboss )
			kernel = kernelEmboss3x3;
		else
		if( kf == kfSharpness )
			kernel = kernelSharpness3x3;
		else
			return( false );
	}
	else
	if( kt == kt5x5 )
	{
		offset = offset5x5;
		count = 25;
		if( kf == kfCustom )
			kernel = customkernel;
		else
		if( kf == kfZero )
			kernel = kernelZero5x5;
		else
		if( kf == kfGaussian )
			kernel = kernelGaussian5x5;
		else
		if( kf == kfMean )
			kernel = kernelMean5x5;
		else
		if( kf == kfLaplacian )
			kernel = kernelLaplacian5x5;
		else
		if( kf == kfEmboss )
			kernel = kernelEmboss5x5;
		else
		if( kf == kfSharpness )
			kernel = kernelSharpness5x5;
		else
			return( false );
	}
	else
	if( kt == kt7x7 )
	{
		offset = offset7x7;
		count = 49;
		if( kf == kfCustom )
			kernel = customkernel;
		else
		if( kf == kfZero )
			kernel = kernelZero7x7;
		else
		if( kf == kfGaussian )
			kernel = kernelGaussian7x7;
		else
		if( kf == kfMean )
			kernel = kernelMean7x7;
		else
		if( kf == kfLaplacian )
			kernel = kernelLaplacian7x7;
		else
		if( kf == kfEmboss )
			kernel = kernelEmboss7x7;
		else
		if( kf == kfSharpness )
			kernel = kernelSharpness7x7;
		else
			return( false );
	}
	else
		return( false );

	if( !offset || !kernel || count <= 0 )
		return( false );
	float t = 0.0f;
	for( int i = 0; i < count; i++ )
		t += kernel[ i ];
	factor = t != 0.0f ? ( 1.0f / t ) * factor : factor;
	for( int i = 0; i < count; i++ )
		kernel[ i ] *= factor;
	m->getProperties()->setPropertyArrayHalf( "in_Kernel", kernel, count, 1 );
	m->getProperties()->setPropertyArrayHalf( "in_Offset", offset, count, 2 );
	return( true );
}