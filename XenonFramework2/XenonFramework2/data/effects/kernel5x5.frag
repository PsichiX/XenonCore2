#define KERNEL_SIZE	25

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
	c += texture2D( texture, coord + in_Offset[ 9 ] ) * vec4( in_Kernel[ 9 ] );
	c += texture2D( texture, coord + in_Offset[ 10 ] ) * vec4( in_Kernel[ 10 ] );
	c += texture2D( texture, coord + in_Offset[ 11 ] ) * vec4( in_Kernel[ 11 ] );
	c += texture2D( texture, coord + in_Offset[ 12 ] ) * vec4( in_Kernel[ 12 ] );
	c += texture2D( texture, coord + in_Offset[ 13 ] ) * vec4( in_Kernel[ 13 ] );
	c += texture2D( texture, coord + in_Offset[ 14 ] ) * vec4( in_Kernel[ 14 ] );
	c += texture2D( texture, coord + in_Offset[ 15 ] ) * vec4( in_Kernel[ 15 ] );
	c += texture2D( texture, coord + in_Offset[ 16 ] ) * vec4( in_Kernel[ 16 ] );
	c += texture2D( texture, coord + in_Offset[ 17 ] ) * vec4( in_Kernel[ 17 ] );
	c += texture2D( texture, coord + in_Offset[ 18 ] ) * vec4( in_Kernel[ 18 ] );
	c += texture2D( texture, coord + in_Offset[ 19 ] ) * vec4( in_Kernel[ 19 ] );
	c += texture2D( texture, coord + in_Offset[ 20 ] ) * vec4( in_Kernel[ 20 ] );
	c += texture2D( texture, coord + in_Offset[ 21 ] ) * vec4( in_Kernel[ 21 ] );
	c += texture2D( texture, coord + in_Offset[ 22 ] ) * vec4( in_Kernel[ 22 ] );
	c += texture2D( texture, coord + in_Offset[ 23 ] ) * vec4( in_Kernel[ 23 ] );
	c += texture2D( texture, coord + in_Offset[ 24 ] ) * vec4( in_Kernel[ 24 ] );
	return( c * col );
}

void main()
{
	gl_FragColor = KernelColor( in_Tex, out_Color, out_Coord );
}
