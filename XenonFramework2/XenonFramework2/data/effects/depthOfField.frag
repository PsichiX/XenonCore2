#if defined XE_VENDOR_INTEL

uniform sampler2D in_TexDefault;
uniform sampler2D in_TexBlurred;
uniform sampler2D in_TexDepth;
uniform float in_Focus;
uniform float in_Factor;

varying vec4 out_Color;
varying vec2 out_Coord;

vec4 FixedDepth( sampler2D depthTexture, vec2 coord )
{
	float d = texture2D( depthTexture, coord ).x;
	return( vec4( d, d, d, 1.0 ) );
}

vec4 FixedColor( sampler2D texture, vec4 col, vec2 coord )
{
	return( texture2D( texture, coord ) * col );
}

vec4 FocusedColor( vec4 blur, vec4 clear, float depth, float focus, float factor )
{
	return( mix( clear, blur, max( 0.0, min( 1.0, factor * pow( abs( focus - depth ), 0.5 ) ) ) ) );
}

void main()
{
	vec4 cd = FixedColor( in_TexDefault, out_Color, out_Coord );
	vec4 cb = FixedColor( in_TexBlurred, out_Color, out_Coord );
	vec4 d = FixedDepth( in_TexDepth, out_Coord );
	gl_FragColor = FocusedColor( cb, cd, d.r, in_Focus, in_Factor );
}

#else

uniform sampler2D in_TexDefault;
uniform sampler2D in_TexBlurred;
uniform sampler2DShadow in_TexDepth;
uniform float in_Focus;
uniform float in_Factor;

varying vec4 out_Color;
varying vec2 out_Coord;

vec4 FixedDepth( sampler2DShadow depthTexture, vec2 coord )
{
	float d = shadow2D( depthTexture, vec3( coord.x, coord.y, 1.0 ) ).x;
	return( vec4( d, d, d, 1.0 ) );
}

vec4 FixedColor( sampler2D texture, vec4 col, vec2 coord )
{
	return( texture2D( texture, coord ) * col );
}

vec4 FocusedColor( vec4 blur, vec4 clear, float depth, float focus, float factor )
{
	return( mix( clear, blur, max( 0.0, min( 1.0, factor * pow( abs( focus - depth ), 0.5 ) ) ) ) );
}

void main()
{
	vec4 cd = FixedColor( in_TexDefault, out_Color, out_Coord );
	vec4 cb = FixedColor( in_TexBlurred, out_Color, out_Coord );
	vec4 d = FixedDepth( in_TexDepth, out_Coord );
	gl_FragColor = FocusedColor( cb, cd, d.r, in_Focus, in_Factor );
}

#endif
