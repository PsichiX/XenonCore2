uniform sampler2D in_Tex;
uniform float in_Size;
uniform float in_Intensity;
uniform float in_Scale;

varying vec4 out_Color;
varying vec2 out_Coord;

vec4 BluredColorV( sampler2D texture, vec4 col, vec2 coord, float height, float size, float intensity, float scale )
{
	if( height <= 0.0 )
		return( col );
	if( size <= 0.0 )
		return( col );
	vec4 color = texture2D( texture, coord ) * intensity * ( 1.0 / size );
	float pix = 1.0 / height;
	float temp;
	for( float i = 1.0; i <= size; i += 1.0 )
	{
		temp = ( 1.0 - ( 1.0 / size * i ) ) * ( 1.0 / size );
		color += texture2D( texture, coord + vec2( 0.0, pix * i * scale ) ) * intensity * temp;
		color += texture2D( texture, coord - vec2( 0.0, pix * i * scale ) ) * intensity * temp;
	}
	return( color * col );
}

void main()
{
	gl_FragColor = BluredColorV( in_Tex, out_Color, out_Coord, XE_WINDOW_SIZE.y, in_Size, in_Intensity, in_Scale );
}