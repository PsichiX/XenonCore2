uniform sampler2D in_Tex;

varying vec4 out_Color;
varying vec2 out_Coord;

uniform float in_Luminosity;
uniform float in_Factor;

vec4 FixedColor( sampler2D texture, vec4 col, vec2 coord )
{
	return( texture2D( texture, coord ) * col );
}

vec4 GrayScaleColor( vec4 color, float luminosity, float factor )
{
	vec4 source = color;
	color *= vec4( 0.30, 0.59, 0.11, 1.0 );
	color = vec4( ( color.r + color.g + color.b ) * luminosity );
	color = ( vec4( 1.0 - factor ) * source ) + ( color * vec4( factor ) );
	color.a = source.a;
	return( color );
}

void main()
{
	gl_FragColor = GrayScaleColor( FixedColor( in_Tex, out_Color, out_Coord ), in_Luminosity, in_Factor );
}
