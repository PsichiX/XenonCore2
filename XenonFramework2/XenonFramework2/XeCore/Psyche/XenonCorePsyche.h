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

#ifndef _XENON_CORE_PSYCHE_H_
#define _XENON_CORE_PSYCHE_H_

#include "../XenonCore2.h"
#ifdef XE_COMPILE_PSYCHE
#include "../XePsyche.h"
#ifdef XE_COMPILE_PHOTON
#include "../XePhoton.h"
#endif // XE_COMPILE_PHOTON
#include "../Base/XeElmUniform.h"
#include "../Base/XeVectorTemplate.h"

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{
//! \namespace XeCore::Psyche Przestrzen nazw modulu Psyche
namespace Psyche
{

/*--- XenoN Core Psyche ---*/
class XenonCoreNeuroBase
{
#ifdef XE_COMPILE_EXPORT
public:
#else
private:
#endif /* XE_COMPILE_EXPORT */
bool IsNeuron;
XeElements<XenonCoreNeuroBase*> Synapsis;
XeDword Gate;
XeHalfVector Pos;
unsigned int IDtemp;
#ifdef XE_COMPILE_EXPORT
XenonCoreNeuroBase();
bool Link(XenonCoreNeuroBase* cell);
bool Unlink(XenonCoreNeuroBase* cell);
#endif /* XE_COMPILE_EXPORT */
};

class XenonCoreNeuron : public XenonCoreNeuroBase
{
#ifdef XE_COMPILE_EXPORT
public:
#else
private:
#endif /* XE_COMPILE_EXPORT */
float Length;
#ifdef XE_COMPILE_EXPORT
XenonCoreNeuron();
#endif /* XE_COMPILE_EXPORT */
};

class XenonCoreDetector : public XenonCoreNeuroBase
{
#ifdef XE_COMPILE_EXPORT
public:
XenonCoreDetector();
void Send(XeDword signal);
#endif /* XE_COMPILE_EXPORT */
};

class XenonCoreEffector : public XenonCoreNeuroBase
{
#ifdef XE_COMPILE_EXPORT
public:
#else
private:
#endif /* XE_COMPILE_EXPORT */
float Length;
#ifdef XE_COMPILE_EXPORT
XenonCoreEffector();
XeDword Receive();
#endif /* XE_COMPILE_EXPORT */
};

class XenonCoreSignal
{
#ifdef XE_COMPILE_EXPORT
public:
#else
private:
#endif /* XE_COMPILE_EXPORT */
XeDword Signal;
XenonCoreNeuroBase* Neuron;
XenonCoreNeuroBase* NeuronLast;
float Position;
#ifdef XE_COMPILE_EXPORT
XenonCoreSignal();
#endif /* XE_COMPILE_EXPORT */
};

class XenonCorePsyche
{
#ifdef XE_COMPILE_EXPORT
public:
#else
private:
#endif /* XE_COMPILE_EXPORT */
XeElements<XenonCoreNeuron> Neurons;
XeElements<XenonCoreDetector> Detectors;
XeElements<XenonCoreEffector> Effectors;
XeElements<XenonCoreSignal> Signals;
#ifdef XE_COMPILE_EXPORT
XenonCorePsyche();
void Progress(float factor);
bool Load(char* fname);
bool Save(char* fname,bool savesignals=false,bool savedetsignal=false,bool saveeffsignal=false);
#endif /* XE_COMPILE_EXPORT */
};

struct XePsycheSignalNeuronInfoStruct
{
XeElmUniform SynapsisFirst;
XeElmUniform SynapsisLast;
XeDword Gate;
XeHalfVector Position;
float Length;
};

#ifdef XE_COMPILE_PHOTON

struct XePsycheDrawDescStruct
{
XeVector DetectorColor;
XeVector EffectorColor;
XeVector NeuronColor;
XeVector SignalColor;
XeVector SynapsisColor;
Photon::XeElmTexture DetectorTexture;
Photon::XeElmTexture EffectorTexture;
Photon::XeElmTexture NeuronTexture;
double DetectorSize;
double EffectorSize;
double NeuronSize;
bool DrawDetectors;
bool DrawEffectors;
bool DrawNeurons;
bool DrawSynapsis;
bool DrawSignals;
};

#endif // XE_COMPILE_PHOTON

} // Psyche
} // XeCore

#endif // XE_COMPILE_PSYCHE

#endif // _XENON_CORE_PSYCHE_H_
