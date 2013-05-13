#define KERNEL_SIZE	9

uniform sampler2D in_Tex;

varying vec4 out_Color;
varying vec2 out_Coord;

uniform float in_Kernel[ KERNEL_SIZE ];
uniform vec2 in_Offset[ KERNEL_SIZE ];

vec4 KernelColor( sampler2D texture, vec4 col, vec2 coord )
{
	vec4 c = vec4( 0.0 );
	c += texture2D( texture, coord + in_Offset[ 0 ] ) * vec4( in_Kernel[ 0 ] );
	c += texture2D( texture, coord + in_Offset[ 1 ] ) * vec4( in_Kernel[ 1 ] );
	c += texture2D( texture, coord + in_Offset[ 2 ] ) * vec4( in_Kernel[ 2 ] );
	c += texture2D( texture, coord + in_Offset[ 3 ] ) * vec4( in_Kernel[ 3 ] );
	c += texture2D( texture, coord + in_Offset[ 4 ] ) * vec4( in_Kernel[ 4 ] );
	c += texture2D( texture, coord + in_Offset[ 5 ] ) * vec4( in_Kernel[ 5 ] );
	c += texture2D( texture, coord + in_Offset[ 6 ] ) * vec4( in_Kernel[ 6 ] );
	c += texture2D( texture, coord + in_Offset[ 7 ] ) * vec4( in_Kernel[ 7 ] );
	c += texture2D( texture, coord + in_Offset[ 8 ] ) * vec4( in_Kernel[ 8 ] );
	return( c * col );
}

void main()
{
	gl_FragColor = KernelColor( in_Tex, out_Color, out_Coord );
}
