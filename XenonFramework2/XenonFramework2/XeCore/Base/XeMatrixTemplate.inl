/*
	Name:			XenoN Core 2
	Version:		2.0.0.0 Frozen Eye
	Update:			2011-06-04
	Copyright:		Copyright © 2007-2011 XenoN Core by PsichiX. All rights reserved.
	Author:			PsichiX
	Website:		http://www.xenon.psichix.com
	Description:	XenoN Core 4D World Engine
*/

/*
	== EN ==
	This file is part of Xenon Core Engine.
	You may distribute it further, but you can not modify it.
	Please do not use in modified form.
	The principles of XenoN Core License available in the file LICENSE_CORE_EN.TXT or visit: http://www.xenon.psichix.com.

	== PL ==
	Ten plik jest czescia XenoN Core Engine.
	Mozesz go rozpowszechniac dalej, jednak nie mozesz go modyfikowac.
	Nalezy uzytkowac w nie zmodyfikowanej formie.
	Nalezy przestrzegac zasad Licencji XenoN Core dostepnej w pliku LICENSE_CORE_PL.TXT oraz na stronie: http://www.xenon.psichix.com.
*/


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

template<typename T>
XeMatrixTemplate<T>::XeMatrixTemplate()
{
Identity();
}

template<typename T>
void XeMatrixTemplate<T>::Identity()
{
Cell[0]=(T)1;	Cell[4]=(T)0;	Cell[8]=(T)0;	Cell[12]=(T)0;
Cell[1]=(T)0;	Cell[5]=(T)1;	Cell[9]=(T)0;	Cell[13]=(T)0;
Cell[2]=(T)0;	Cell[6]=(T)0;	Cell[10]=(T)1;	Cell[14]=(T)0;
Cell[3]=(T)0;	Cell[7]=(T)0;	Cell[11]=(T)0;	Cell[15]=(T)1;
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::Add(XeMatrixTemplate<T>& mat)
{
XeMatrixTemplate<T> temp;
for(int i=0;i<16;i++)
temp.Cell[i]=Cell[i]+mat.Cell[i];
return(temp);
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::Substract(XeMatrixTemplate<T>& mat)
{
XeMatrixTemplate<T> temp;
for(int i=0;i<16;i++)
temp.Cell[i]=Cell[i]-mat.Cell[i];
return(temp);
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::ScalarMultiply(T value)
{
XeMatrixTemplate<T> temp;
for(int i=0;i<16;i++)
temp.Cell[i]=Cell[i]*value;
return(temp);
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::Transpose()
{
XeMatrixTemplate<T> temp;
temp.Cell[0]=Cell[0];	temp.Cell[4]=Cell[1];	temp.Cell[8]=Cell[2];	temp.Cell[12]=Cell[3];
temp.Cell[1]=Cell[4];	temp.Cell[5]=Cell[5];	temp.Cell[9]=Cell[6];	temp.Cell[13]=Cell[7];
temp.Cell[2]=Cell[8];	temp.Cell[6]=Cell[9];	temp.Cell[10]=Cell[10];	temp.Cell[14]=Cell[11];
temp.Cell[3]=Cell[12];	temp.Cell[7]=Cell[13];	temp.Cell[11]=Cell[14];	temp.Cell[15]=Cell[15];
return(temp);
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::Multiply(XeMatrixTemplate<T>& mat)
{
XeMatrixTemplate<T> temp;
temp.Cell[0]=Cell[0]*mat.Cell[0]+Cell[4]*mat.Cell[1]+Cell[8]*mat.Cell[2]+Cell[12]*mat.Cell[3];
temp.Cell[1]=Cell[1]*mat.Cell[0]+Cell[5]*mat.Cell[1]+Cell[9]*mat.Cell[2]+Cell[13]*mat.Cell[3];
temp.Cell[2]=Cell[2]*mat.Cell[0]+Cell[6]*mat.Cell[1]+Cell[10]*mat.Cell[2]+Cell[14]*mat.Cell[3];
temp.Cell[3]=Cell[3]*mat.Cell[0]+Cell[7]*mat.Cell[1]+Cell[11]*mat.Cell[2]+Cell[15]*mat.Cell[3];
temp.Cell[4]=Cell[0]*mat.Cell[4]+Cell[4]*mat.Cell[5]+Cell[8]*mat.Cell[6]+Cell[12]*mat.Cell[7];
temp.Cell[5]=Cell[1]*mat.Cell[4]+Cell[5]*mat.Cell[5]+Cell[9]*mat.Cell[6]+Cell[13]*mat.Cell[7];
temp.Cell[6]=Cell[2]*mat.Cell[4]+Cell[6]*mat.Cell[5]+Cell[10]*mat.Cell[6]+Cell[14]*mat.Cell[7];
temp.Cell[7]=Cell[3]*mat.Cell[4]+Cell[7]*mat.Cell[5]+Cell[11]*mat.Cell[6]+Cell[15]*mat.Cell[7];
temp.Cell[8]=Cell[0]*mat.Cell[8]+Cell[4]*mat.Cell[9]+Cell[8]*mat.Cell[10]+Cell[12]*mat.Cell[11];
temp.Cell[9]=Cell[1]*mat.Cell[8]+Cell[5]*mat.Cell[9]+Cell[9]*mat.Cell[10]+Cell[13]*mat.Cell[11];
temp.Cell[10]=Cell[2]*mat.Cell[8]+Cell[6]*mat.Cell[9]+Cell[10]*mat.Cell[10]+Cell[14]*mat.Cell[11];
temp.Cell[11]=Cell[3]*mat.Cell[8]+Cell[7]*mat.Cell[9]+Cell[11]*mat.Cell[10]+Cell[15]*mat.Cell[11];
temp.Cell[12]=Cell[0]*mat.Cell[12]+Cell[4]*mat.Cell[13]+Cell[8]*mat.Cell[14]+Cell[12]*mat.Cell[15];
temp.Cell[13]=Cell[1]*mat.Cell[12]+Cell[5]*mat.Cell[13]+Cell[9]*mat.Cell[14]+Cell[13]*mat.Cell[15];
temp.Cell[14]=Cell[2]*mat.Cell[12]+Cell[6]*mat.Cell[13]+Cell[10]*mat.Cell[14]+Cell[14]*mat.Cell[15];
temp.Cell[15]=Cell[3]*mat.Cell[12]+Cell[7]*mat.Cell[13]+Cell[11]*mat.Cell[14]+Cell[15]*mat.Cell[15];
return(temp);
}

template<typename T>
XeVectorTemplate<T> XeMatrixTemplate<T>::Multiply(XeVectorTemplate<T>& vec)
{
XeVectorTemplate<T> temp;
temp.X=Cell[0]*vec.X+Cell[4]*vec.Y+Cell[8]*vec.Z+Cell[12]*vec.W;
temp.Y=Cell[1]*vec.X+Cell[5]*vec.Y+Cell[9]*vec.Z+Cell[13]*vec.W;
temp.Z=Cell[2]*vec.X+Cell[6]*vec.Y+Cell[10]*vec.Z+Cell[14]*vec.W;
temp.W=Cell[3]*vec.X+Cell[7]*vec.Y+Cell[11]*vec.Z+Cell[15]*vec.W;
temp.X/=temp.W;
temp.Y/=temp.W;
temp.Z/=temp.W;
return(temp);
}

template<typename T>
void XeMatrixTemplate<T>::Multiply(XeMatrixTemplate<T>& mat,XeMatrixTemplate<T>& ret)
{
ret.Cell[0]=Cell[0]*mat.Cell[0]+Cell[4]*mat.Cell[1]+Cell[8]*mat.Cell[2]+Cell[12]*mat.Cell[3];
ret.Cell[1]=Cell[1]*mat.Cell[0]+Cell[5]*mat.Cell[1]+Cell[9]*mat.Cell[2]+Cell[13]*mat.Cell[3];
ret.Cell[2]=Cell[2]*mat.Cell[0]+Cell[6]*mat.Cell[1]+Cell[10]*mat.Cell[2]+Cell[14]*mat.Cell[3];
ret.Cell[3]=Cell[3]*mat.Cell[0]+Cell[7]*mat.Cell[1]+Cell[11]*mat.Cell[2]+Cell[15]*mat.Cell[3];
ret.Cell[4]=Cell[0]*mat.Cell[4]+Cell[4]*mat.Cell[5]+Cell[8]*mat.Cell[6]+Cell[12]*mat.Cell[7];
ret.Cell[5]=Cell[1]*mat.Cell[4]+Cell[5]*mat.Cell[5]+Cell[9]*mat.Cell[6]+Cell[13]*mat.Cell[7];
ret.Cell[6]=Cell[2]*mat.Cell[4]+Cell[6]*mat.Cell[5]+Cell[10]*mat.Cell[6]+Cell[14]*mat.Cell[7];
ret.Cell[7]=Cell[3]*mat.Cell[4]+Cell[7]*mat.Cell[5]+Cell[11]*mat.Cell[6]+Cell[15]*mat.Cell[7];
ret.Cell[8]=Cell[0]*mat.Cell[8]+Cell[4]*mat.Cell[9]+Cell[8]*mat.Cell[10]+Cell[12]*mat.Cell[11];
ret.Cell[9]=Cell[1]*mat.Cell[8]+Cell[5]*mat.Cell[9]+Cell[9]*mat.Cell[10]+Cell[13]*mat.Cell[11];
ret.Cell[10]=Cell[2]*mat.Cell[8]+Cell[6]*mat.Cell[9]+Cell[10]*mat.Cell[10]+Cell[14]*mat.Cell[11];
ret.Cell[11]=Cell[3]*mat.Cell[8]+Cell[7]*mat.Cell[9]+Cell[11]*mat.Cell[10]+Cell[15]*mat.Cell[11];
ret.Cell[12]=Cell[0]*mat.Cell[12]+Cell[4]*mat.Cell[13]+Cell[8]*mat.Cell[14]+Cell[12]*mat.Cell[15];
ret.Cell[13]=Cell[1]*mat.Cell[12]+Cell[5]*mat.Cell[13]+Cell[9]*mat.Cell[14]+Cell[13]*mat.Cell[15];
ret.Cell[14]=Cell[2]*mat.Cell[12]+Cell[6]*mat.Cell[13]+Cell[10]*mat.Cell[14]+Cell[14]*mat.Cell[15];
ret.Cell[15]=Cell[3]*mat.Cell[12]+Cell[7]*mat.Cell[13]+Cell[11]*mat.Cell[14]+Cell[15]*mat.Cell[15];
}

template<typename T>
void XeMatrixTemplate<T>::Multiply(XeVectorTemplate<T>& vec,XeVectorTemplate<T>& ret)
{
ret.X=Cell[0]*vec.X+Cell[4]*vec.Y+Cell[8]*vec.Z+Cell[12]*vec.W;
ret.Y=Cell[1]*vec.X+Cell[5]*vec.Y+Cell[9]*vec.Z+Cell[13]*vec.W;
ret.Z=Cell[2]*vec.X+Cell[6]*vec.Y+Cell[10]*vec.Z+Cell[14]*vec.W;
ret.W=Cell[3]*vec.X+Cell[7]*vec.Y+Cell[11]*vec.Z+Cell[15]*vec.W;
ret.X/=ret.W;
ret.Y/=ret.W;
ret.Z/=ret.W;
}

template<typename T>
T XeMatrixTemplate<T>::Determinant()
{
T temp
=Cell[0]*Cell[5]*Cell[10]*Cell[15]+Cell[0]*Cell[9]*Cell[14]*Cell[7]+Cell[0]*Cell[13]*Cell[6]*Cell[11]
+Cell[4]*Cell[1]*Cell[14]*Cell[11]+Cell[4]*Cell[9]*Cell[2]*Cell[15]+Cell[4]*Cell[13]*Cell[10]*Cell[3]
+Cell[8]*Cell[1]*Cell[6]*Cell[15]+Cell[8]*Cell[5]*Cell[14]*Cell[3]+Cell[8]*Cell[13]*Cell[2]*Cell[7]
+Cell[12]*Cell[1]*Cell[10]*Cell[7]+Cell[12]*Cell[5]*Cell[2]*Cell[11]+Cell[12]*Cell[9]*Cell[6]*Cell[3]
-Cell[0]*Cell[5]*Cell[14]*Cell[11]-Cell[0]*Cell[9]*Cell[6]*Cell[15]-Cell[0]*Cell[13]*Cell[10]*Cell[7]
-Cell[4]*Cell[1]*Cell[10]*Cell[15]-Cell[4]*Cell[9]*Cell[14]*Cell[3]-Cell[4]*Cell[13]*Cell[2]*Cell[11]
-Cell[8]*Cell[1]*Cell[14]*Cell[7]-Cell[8]*Cell[5]*Cell[2]*Cell[15]-Cell[8]*Cell[13]*Cell[6]*Cell[3]
-Cell[12]*Cell[1]*Cell[6]*Cell[11]-Cell[12]*Cell[5]*Cell[10]*Cell[3]-Cell[12]*Cell[9]*Cell[2]*Cell[7];
return(temp);
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::Inverse()
{
T det=Determinant();
XeMatrixTemplate<T> _temp;
XeMatrixTemplate<T> temp=_temp.ScalarMultiply(((T)1)/det);
return(temp);
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::Translate(T x,T y,T z)
{
XeMatrixTemplate<T> temp;
XeMatrixTemplate<T> mat;
mat.Cell[12]=x;
mat.Cell[13]=y;
mat.Cell[14]=z;
temp=Multiply(mat);
return(temp);
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::Scale(T x,T y,T z)
{
XeMatrixTemplate<T> temp;
XeMatrixTemplate<T> mat;
mat.Cell[0]=x;
mat.Cell[5]=y;
mat.Cell[10]=z;
temp=Multiply(mat);
return(temp);
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::RotateX(T angle)
{
XeMatrixTemplate<T> mat;
angle=XeMath::DegToRad(angle);
T sn=sin(angle);
T cs=cos(angle);
mat.Cell[5]=cs;
mat.Cell[6]=sn;
mat.Cell[9]=-sn;
mat.Cell[10]=cs;
mat=Multiply(mat);
return(mat);
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::RotateY(T angle)
{
XeMatrixTemplate<T> mat;
angle=XeMath::DegToRad(angle);
T sn=sin(angle);
T cs=cos(angle);
mat.Cell[0]=cs;
mat.Cell[2]=-sn;
mat.Cell[8]=sn;
mat.Cell[10]=cs;
mat=Multiply(mat);
return(mat);
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::RotateZ(T angle)
{
XeMatrixTemplate<T> mat;
angle=XeMath::DegToRad(angle);
T sn=sin(angle);
T cs=cos(angle);
mat.Cell[0]=cs;
mat.Cell[1]=sn;
mat.Cell[4]=-sn;
mat.Cell[5]=cs;
mat=Multiply(mat);
return(mat);
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::Rotate(T alpha,T beta,T gamma)
{
XeMatrixTemplate<T> mat;
alpha=XeMath::DegToRad(alpha);
beta=XeMath::DegToRad(beta);
gamma=XeMath::DegToRad(gamma);
T A = sin(gamma);
T B = cos(gamma);
T C = sin(beta);
T D = cos(beta);
T E = sin(alpha);
T F = cos(alpha);
mat.Cell[0]=D*F;
mat.Cell[1]=D*E;
mat.Cell[2]=-C;
mat.Cell[3]=(T)0;
mat.Cell[4]=(A*C*F)-(B*E);
mat.Cell[5]=(A*C*E)+(B*F);
mat.Cell[6]=A*D;
mat.Cell[7]=(T)0;
mat.Cell[8]=(A*E)+(B*C*F);
mat.Cell[9]=(B*C*E)-(A*F);
mat.Cell[10]=B*D;
mat.Cell[11]=(T)0;
mat.Cell[12]=(T)0;
mat.Cell[13]=(T)0;
mat.Cell[14]=(T)0;
mat.Cell[15]=(T)1;
mat=Multiply(mat);
return(mat);
}

template<typename T>
void XeMatrixTemplate<T>::Translate(T x,T y,T z,XeMatrixTemplate<T>& ret)
{
XeMatrixTemplate<T> mat;
mat.Cell[12]=x;
mat.Cell[13]=y;
mat.Cell[14]=z;
Multiply(mat,ret);
}

template<typename T>
void XeMatrixTemplate<T>::Scale(T x,T y,T z,XeMatrixTemplate<T>& ret)
{
XeMatrixTemplate<T> mat;
mat.Cell[0]=x;
mat.Cell[5]=y;
mat.Cell[10]=z;
Multiply(mat,ret);
}

template<typename T>
void XeMatrixTemplate<T>::RotateX(T angle,XeMatrixTemplate<T>& ret)
{
XeMatrixTemplate<T> mat;
angle=XeMath::DegToRad(angle);
T sn=sin(angle);
T cs=cos(angle);
mat.Cell[5]=cs;
mat.Cell[6]=sn;
mat.Cell[9]=-sn;
mat.Cell[10]=cs;
Multiply(mat,ret);
}

template<typename T>
void XeMatrixTemplate<T>::RotateY(T angle,XeMatrixTemplate<T>& ret)
{
XeMatrixTemplate<T> mat;
angle=XeMath::DegToRad(angle);
T sn=sin(angle);
T cs=cos(angle);
mat.Cell[0]=cs;
mat.Cell[2]=-sn;
mat.Cell[8]=sn;
mat.Cell[10]=cs;
Multiply(mat,ret);
}

template<typename T>
void XeMatrixTemplate<T>::RotateZ(T angle,XeMatrixTemplate<T>& ret)
{
XeMatrixTemplate<T> mat;
angle=XeMath::DegToRad(angle);
T sn=sin(angle);
T cs=cos(angle);
mat.Cell[0]=cs;
mat.Cell[1]=sn;
mat.Cell[4]=-sn;
mat.Cell[5]=cs;
Multiply(mat,ret);
}

template<typename T>
void XeMatrixTemplate<T>::Rotate(T alpha,T beta,T gamma,XeMatrixTemplate<T>& ret)
{
XeMatrixTemplate<T> mat;
alpha=XeMath::DegToRad(alpha);
beta=XeMath::DegToRad(beta);
gamma=XeMath::DegToRad(gamma);
T A = sin(gamma);
T B = cos(gamma);
T C = sin(beta);
T D = cos(beta);
T E = sin(alpha);
T F = cos(alpha);
mat.Cell[0]=D*F;
mat.Cell[1]=D*E;
mat.Cell[2]=-C;
mat.Cell[3]=(T)0;
mat.Cell[4]=(A*C*F)-(B*E);
mat.Cell[5]=(A*C*E)+(B*F);
mat.Cell[6]=A*D;
mat.Cell[7]=(T)0;
mat.Cell[8]=(A*E)+(B*C*F);
mat.Cell[9]=(B*C*E)-(A*F);
mat.Cell[10]=B*D;
mat.Cell[11]=(T)0;
mat.Cell[12]=(T)0;
mat.Cell[13]=(T)0;
mat.Cell[14]=(T)0;
mat.Cell[15]=(T)1;
Multiply(mat,ret);
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::operator+ (XeMatrixTemplate<T>& mat)
{
return(Add(mat));
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::operator- (XeMatrixTemplate<T>& mat)
{
return(Substract(mat));
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::operator* (T value)
{
return(ScalarMultiply((T)value));
}

template<typename T>
XeMatrixTemplate<T> XeMatrixTemplate<T>::operator* (XeMatrixTemplate<T>& mat)
{
return(Multiply(mat));
}

template<typename T>
XeVectorTemplate<T> XeMatrixTemplate<T>::operator* (XeVectorTemplate<T>& vec)
{
return(Multiply(vec));
}

} // XeCore
