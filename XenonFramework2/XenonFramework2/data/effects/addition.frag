uniform sampler2D in_Tex0;
uniform sampler2D in_Tex1;
uniform float in_Factor;

varying vec4 out_Color;
varying vec2 out_Coord;

vec4 FixedColor( sampler2D texture, vec4 col, vec2 coord )
{
	return( texture2D( texture, coord ) * col );
}

void main()
{
	vec4 c0 = FixedColor( in_Tex0, out_Color, out_Coord );
	vec4 c1 = FixedColor( in_Tex1, out_Color, out_Coord );
	gl_FragColor = ( c0 + c1 ) * vec4( in_Factor );
}
