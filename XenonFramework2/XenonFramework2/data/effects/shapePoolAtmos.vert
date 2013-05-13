uniform mat4 in_ProjectionMatrix;
uniform vec3 in_SunPos;
uniform int in_SunHorFactor;
uniform int in_SunVertFactor;

attribute vec4 in_Position;
attribute vec4 in_ModelViewTransform1;
attribute vec4 in_ModelViewTransform2;
attribute vec4 in_ModelViewTransform3;
attribute vec4 in_ModelViewTransform4;

varying vec4 out_Position;
varying float out_SunHorIntensity;
varying float out_SunHorIntensityP;
varying float out_SunVertIntensity;
varying float out_SunVertIntensityNP;

void main()
{
	out_Position = in_Position;
	
	out_SunHorIntensity = dot( normalize( vec3( in_SunPos.xy, 0.0 ) ), normalize( in_SunPos ) );
	out_SunHorIntensity = clamp( out_SunHorIntensity, 0.0, 1.0 );
	out_SunHorIntensityP = pow( out_SunHorIntensity, in_SunHorFactor );
	
	out_SunVertIntensity = dot( normalize( vec3( 0.0, 0.0, 1.0 ) ), normalize( in_SunPos ) );
	out_SunVertIntensity = abs( clamp( out_SunVertIntensity, -1.0, 0.0 ) );
	out_SunVertIntensityNP = pow( 1.0 - out_SunVertIntensity, in_SunVertFactor );
	
	mat4 in_ModelViewMatrix = mat4( in_ModelViewTransform1, in_ModelViewTransform2, in_ModelViewTransform3, in_ModelViewTransform4 );
	gl_Position = in_ProjectionMatrix * in_ModelViewMatrix * in_Position;
}
