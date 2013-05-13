#pragma once

#include "Material.h"

class KernelEffects
{
public:
	enum KernelType
	{
		kt3x3,
		kt5x5,
		kt7x7,

		ktCount
	};

	enum KernelFilter
	{
		kfCustom,
		kfZero,
		kfGaussian,
		kfMean,
		kfLaplacian,
		kfEmboss,
		kfSharpness,

		kfCount
	};

	static bool			applyKernelProperties( KernelType kt, KernelFilter kf, Material* m, float factor = 1.0f, int texunit = 0, float* customkernel = 0 );
};