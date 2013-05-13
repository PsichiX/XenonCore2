uniform vec3 in_SkyColor;
uniform vec3 in_SkyColorRed;
uniform vec3 in_SunColorYellow;
uniform vec3 in_SunColorAura;
uniform vec3 in_SunPos;
uniform int in_SunPosFactor;
uniform int in_PosHorFactor;

varying vec4 out_Position;
varying float out_SunHorIntensity;
varying float out_SunHorIntensityP;
varying float out_SunVertIntensity;
varying float out_SunVertIntensityNP;

void main()
{
	float f = 0.0;
	
	// sun pos intensity
	float sunInt = dot( normalize( out_Position.xyz ), normalize( in_SunPos ) );
	sunInt = clamp( sunInt, 0.0, 1.0 );
	float sunIntP = pow( sunInt, in_SunPosFactor );
	
	// pos hor intensity
	float horPosInt = dot( normalize( vec3( out_Position.xy, 0.0 ) ), normalize( out_Position.xyz ) );
	horPosInt = clamp( horPosInt, 0.0, 1.0 );
	float horPosIntP = pow( horPosInt, in_PosHorFactor );
	
	// sky color
	vec4 sky = vec4( in_SkyColor, out_SunVertIntensityNP );
	
	// sky redness
	f = horPosInt * out_SunHorIntensityP * sunInt;
	sky += vec4( in_SkyColorRed - in_SkyColor, 1.0 ) * vec4( f );
	
	// hor color
	sky += vec4( in_SunColorAura, 1.0 ) * vec4( horPosIntP * 0.5 * ( 1.0 - out_SunVertIntensity ) );
	
	// sun color
	sky += vec4( mix( vec3( sunIntP ), in_SunColorYellow * sunIntP, out_SunHorIntensity ), sunIntP );
	
	gl_FragColor = sky;
}
