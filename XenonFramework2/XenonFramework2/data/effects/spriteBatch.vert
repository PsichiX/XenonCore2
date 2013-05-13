uniform mat4 in_ProjectionMatrix;

attribute vec4 in_Position;
attribute vec4 in_Color;
attribute vec4 in_Coord;
attribute vec4 in_ModelViewTransform1;
attribute vec4 in_ModelViewTransform2;
attribute vec4 in_ModelViewTransform3;
attribute vec4 in_ModelViewTransform4;

varying vec4 out_Color;
varying vec2 out_Coord;

void main()
{
	out_Color = in_Color;
	out_Coord = in_Coord.xy;
	mat4 in_ModelViewMatrix = mat4( in_ModelViewTransform1, in_ModelViewTransform2, in_ModelViewTransform3, in_ModelViewTransform4 );
	gl_Position = in_ProjectionMatrix * in_ModelViewMatrix * in_Position;
}
