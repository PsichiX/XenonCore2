varying vec4 out_Color;
varying vec2 out_Coord;

void main()
{
	if( distance( out_Coord, vec2( 0.5 ) ) > 0.5 )
		discard;
	gl_FragColor = out_Color;
}
