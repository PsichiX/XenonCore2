#pragma once

#include "Singleton.h"
#include "../XeCore/Base/XeVectorTemplate.h"
#include "../XeCore/Base/XeString.h"
#include <Windows.h>

class Input
{
public:
	enum Key
	{
		kANY = 0x00,
		kMOUSELEFT = 0x01,
		kMOUSERIGHT = 0x02,
		kMOUSEMIDDLE = 0x04,
		kBACKSPACE = 0x08,
		kTAB = 0x09,
		kENTER = 0x0D,
		kSHIFT = 0x10,
		kCTRL = 0x11,
		kALT = 0x12,
		kPAUSE = 0x13,
		kCAPSLOCK = 0x14,
		kESC = 0x1B,
		kSPACE = 0x20,
		kPAGEUP = 0x21,
		kPAGEDOWN = 0x22,
		kEND = 0x23,
		kHOME = 0x24,
		kLEFT = 0x25,
		kUP = 0x26,
		kRIGHT = 0x27,
		kDOWN = 0x28,
		kPRINTSCREEN = 0x2C,
		kINSERT = 0x2D,
		kDELETE = 0x2E,
		k0 = 0x30,
		k1 = 0x31,
		k2 = 0x32,
		k3 = 0x33,
		k4 = 0x34,
		k5 = 0x35,
		k6 = 0x36,
		k7 = 0x37,
		k8 = 0x38,
		k9 = 0x39,
		kA = 0x41,
		kB = 0x42,
		kC = 0x43,
		kD = 0x44,
		kE = 0x45,
		kF = 0x46,
		kG = 0x47,
		kH = 0x48,
		kI = 0x49,
		kJ = 0x4A,
		kK = 0x4B,
		kL = 0x4C,
		kM = 0x4D,
		kN = 0x4E,
		kO = 0x4F,
		kP = 0x50,
		kQ = 0x51,
		kR = 0x52,
		kS = 0x53,
		kT = 0x54,
		kU = 0x55,
		kV = 0x56,
		kW = 0x57,
		kX = 0x58,
		kY = 0x59,
		kZ = 0x5A,
		kWINLEFT = 0x5B,
		kWINRIGHT = 0x5C,
		kSLEEP = 0x5F,
		kNUMPAD0 = 0x60,
		kNUMPAD1 = 0x61,
		kNUMPAD2 = 0x62,
		kNUMPAD3 = 0x63,
		kNUMPAD4 = 0x64,
		kNUMPAD5 = 0x65,
		kNUMPAD6 = 0x66,
		kNUMPAD7 = 0x67,
		kNUMPAD8 = 0x68,
		kNUMPAD9 = 0x69,
		kMULTIPLY = 0x6A,
		kADD = 0x6B,
		kSEPARATOR = 0x6C,
		kSUBTRACT = 0x6D,
		kDECIMAL = 0x6E,
		kDIVIDE = 0x6F,
		kF1 = 0x70,
		kF2 = 0x71,
		kF3 = 0x72,
		kF4 = 0x73,
		kF5 = 0x74,
		kF6 = 0x75,
		kF7 = 0x76,
		kF8 = 0x77,
		kF9 = 0x78,
		kF10 = 0x79,
		kF11 = 0x7A,
		kF12 = 0x7B,
		kF13 = 0x7C,
		kF14 = 0x7D,
		kF15 = 0x7E,
		kF16 = 0x7F,
		kF17 = 0x80,
		kF18 = 0x81,
		kF19 = 0x82,
		kF20 = 0x83,
		kF21 = 0x84,
		kF22 = 0x85,
		kF23 = 0x86,
		kF24 = 0x87,
		kNUMLOCK = 0x90,
		kSCROLLLOCK = 0x91,
		kSHIFTLEFT = 0xA0,
		kSHIFTRIGHT = 0xA1,
		kCTRLLEFT = 0xA2,
		kCTRTRIGHT = 0xA3,
		kALTLEFT = 0xA4,
		kALTRIGHT = 0xA5,
		kSEMICOLON = 0xBA,
		kEQUAL = 0xBB,
		kCOMMA = 0xBC,
		kDASH = 0xBD,
		kPOINT = 0xBE,
		kSHLASH = 0xBF,
		kSQRBRACKETLEFT = 0xDB,
		kBACKSLASH = 0xDC,
		kSQRBRACKETRIGHT = 0xDD,
		kAPOSTROPHE = 0xDE,
		kTYLDE = 0xC0
	};
};

class InputManager : public Singleton< InputManager >
{
	friend class Engine;

private:
	struct CharacterList
	{
		char			value;
		CharacterList*	prev;
	};

public:
	enum InputEvent
	{
		iePressed,
		ieHold,
		ieReleased,
		ieAfter,
		ieCount
	};

	enum InputButton
	{
		ibAny,
		ibLeft,
		ibMiddle,
		ibRight,
		ibCount
	};

									InputManager();
									~InputManager();
	bool							getKey( InputEvent ie, int code );
	bool							getButton( InputEvent ie, InputButton btn );
	void							refreshMousePos();
	void							getMousePos( int& x, int& y, bool winrelative = false );
	XeCore::XeHalfVector&			getMouseVec( bool winrelative = false );
	void							getLastMousePos( int& x, int& y, bool winrelative = false );
	XeCore::XeHalfVector&			getLastMouseVec( bool winrelative = false );
	char							getLastCharacter( bool pop = false );
	bool							mouseIsMoved();
	int								getWheelDelta();
	void							setKey( InputEvent ie, int code, bool mode );
	void							setButton( InputEvent ie, InputButton btn, bool mode );
	void							setMousePos( int x, int y );
	void							setMouseVec( XeCore::XeHalfVector& pos );
	void							clearAfter();
	void							clear( bool nothold = false );
	void							pushCharacter( char c );
	bool							popCharacter( char& c, bool leave = false );
	bool							popString( XeCore::XeString& s, bool leave = false );
	unsigned int					charactersCount();
	void							charactersClear();

private:
	bool							m_keysPressed[ 256 ];
	bool							m_keysHold[ 256 ];
	bool							m_keysReleased[ 256 ];
	bool							m_keysAfter[ 256 ];
	bool							m_buttonsPressed[ ibCount ];
	bool							m_buttonsHold[ ibCount ];
	bool							m_buttonsReleased[ ibCount ];
	bool							m_buttonsAfter[ ibCount ];
	int								m_wheelDelta;
	POINT							m_mousePos;
	POINT							m_lastMousePos;
	XeCore::XeHalfVector			m_mousePosVec;
	XeCore::XeHalfVector			m_lastMousePosVec;
	CharacterList*					m_characters;
	bool							m_pressOnce;
};