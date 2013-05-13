#if defined XE_VENDOR_INTEL

uniform sampler2D in_DepthTex;

varying vec4 out_Color;
varying vec2 out_Coord;

vec4 FixedDepth( sampler2D depthTexture, vec2 coord )
{
	float d = texture2D( depthTexture, coord ).x;
	return( vec4( d, d, d, 1.0 ) );
}

void main()
{
	gl_FragColor = FixedDepth( in_DepthTex, out_Coord );
}

#else

uniform sampler2DShadow in_DepthTex;

varying vec4 out_Color;
varying vec2 out_Coord;

vec4 FixedDepth( sampler2DShadow depthTexture, vec2 coord )
{
	float d = shadow2D( depthTexture, vec3( coord.x, coord.y, 1.0 ) ).x;
	return( vec4( d, d, d, 1.0 ) );
}

void main()
{
	gl_FragColor = FixedDepth( in_DepthTex, out_Coord );
	gl_FragColor.a = 1.0;
}

#endif
