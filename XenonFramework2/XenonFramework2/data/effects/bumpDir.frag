uniform sampler2D in_Tex;
uniform sampler2D in_TexNormal;

varying vec4 out_Color;
varying vec2 out_Coord;

uniform vec2 in_Offset;
uniform vec3 in_LightDir;
uniform float in_Shadow;
uniform float in_Specular;
uniform float in_Shine;

vec4 BumpColor( sampler2D texture, sampler2D normalmap, vec4 color, vec2 coord, vec2 offset, vec3 lightdir, float shadow, float specular, float shine )
{
	vec3 light = normalize( lightdir );
	vec3 eye = vec3( 0.0, 0.0, 1.0 );
	
	vec4 src = texture2D( texture, coord ) * color;
	
	vec4 bump = normalize( texture2D( normalmap, coord + offset ) * vec4( 2.0 ) - vec4( 1.0 ) );
	vec3 temp = vec3( 0.0 );
	temp.xy = bump.xy;
	temp = vec3( dot( temp, temp ) );
	bump.z = sqrt( 1.0 - temp.z );
	
	float att = 1.0 - ( pow( 1.0 - max( 0.0, light.z ), 2.0 ) );
	float diffint = dot( light, bump.xyz );
	float specint = pow( dot( normalize( light + eye ), bump.xyz ), shine );
	
	vec4 result = ( ( src * vec4( 1.0 - shadow ) ) + ( src * vec4( diffint ) * vec4( att ) * vec4( shadow ) ) ) + color * vec4( specint ) * vec4( specular );
	return( result );
}

void main()
{
	gl_FragColor = BumpColor( in_Tex, in_TexNormal, out_Color, out_Coord, in_Offset, in_LightDir, in_Shadow, in_Specular, in_Shine );
}
