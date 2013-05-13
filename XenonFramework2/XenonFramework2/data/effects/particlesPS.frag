uniform sampler2D in_Tex;

varying vec4 out_Color;

vec4 FixedColor( sampler2D texture, vec4 col, vec2 coord )
{
	return( texture2D( texture, coord ) * col );
}

void main()
{
	gl_FragColor = FixedColor( in_Tex, out_Color, gl_PointCoord );
}
