#define KERNEL_SIZE	49

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
	c += texture2D( texture, coord + in_Offset[ 25 ] ) * vec4( in_Kernel[ 25 ] );
	c += texture2D( texture, coord + in_Offset[ 26 ] ) * vec4( in_Kernel[ 26 ] );
	c += texture2D( texture, coord + in_Offset[ 27 ] ) * vec4( in_Kernel[ 27 ] );
	c += texture2D( texture, coord + in_Offset[ 28 ] ) * vec4( in_Kernel[ 28 ] );
	c += texture2D( texture, coord + in_Offset[ 29 ] ) * vec4( in_Kernel[ 29 ] );
	c += texture2D( texture, coord + in_Offset[ 30 ] ) * vec4( in_Kernel[ 30 ] );
	c += texture2D( texture, coord + in_Offset[ 31 ] ) * vec4( in_Kernel[ 31 ] );
	c += texture2D( texture, coord + in_Offset[ 32 ] ) * vec4( in_Kernel[ 32 ] );
	c += texture2D( texture, coord + in_Offset[ 33 ] ) * vec4( in_Kernel[ 33 ] );
	c += texture2D( texture, coord + in_Offset[ 34 ] ) * vec4( in_Kernel[ 34 ] );
	c += texture2D( texture, coord + in_Offset[ 35 ] ) * vec4( in_Kernel[ 35 ] );
	c += texture2D( texture, coord + in_Offset[ 36 ] ) * vec4( in_Kernel[ 36 ] );
	c += texture2D( texture, coord + in_Offset[ 37 ] ) * vec4( in_Kernel[ 37 ] );
	c += texture2D( texture, coord + in_Offset[ 38 ] ) * vec4( in_Kernel[ 38 ] );
	c += texture2D( texture, coord + in_Offset[ 39 ] ) * vec4( in_Kernel[ 39 ] );
	c += texture2D( texture, coord + in_Offset[ 40 ] ) * vec4( in_Kernel[ 40 ] );
	c += texture2D( texture, coord + in_Offset[ 41 ] ) * vec4( in_Kernel[ 41 ] );
	c += texture2D( texture, coord + in_Offset[ 42 ] ) * vec4( in_Kernel[ 42 ] );
	c += texture2D( texture, coord + in_Offset[ 43 ] ) * vec4( in_Kernel[ 43 ] );
	c += texture2D( texture, coord + in_Offset[ 44 ] ) * vec4( in_Kernel[ 44 ] );
	c += texture2D( texture, coord + in_Offset[ 45 ] ) * vec4( in_Kernel[ 45 ] );
	c += texture2D( texture, coord + in_Offset[ 46 ] ) * vec4( in_Kernel[ 46 ] );
	c += texture2D( texture, coord + in_Offset[ 47 ] ) * vec4( in_Kernel[ 47 ] );
	c += texture2D( texture, coord + in_Offset[ 48 ] ) * vec4( in_Kernel[ 48 ] );
	return( c * col );
}

void main()
{
	gl_FragColor = KernelColor( in_Tex, out_Color, out_Coord );
}
