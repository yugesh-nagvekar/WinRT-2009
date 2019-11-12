#pragma once

class IMultiplication : public IUnknown
{
public:
	//IMultiplication specific method declaration
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;//pure virtual
};

class IDivision : public IUnknown
{
public:
	//IDivision specific method declaration
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0; // pure virtual
};


// CLSID of MultiplicationDivision Component {3B056759-B556-4350-804F-46CEF1B840A9}
const CLSID CLSID_MultiplicationDivision = { 0x3b056759, 0xb556, 0x4350, 0x80, 0x4f, 0x46, 0xce, 0xf1, 0xb8, 0x40, 0xa9 };

// IID of IMultiplication Interface {E0123791-3701-4898-84A4-C2098661E2BC}
const IID IID_IMultiplication = { 0xe0123791, 0x3701, 0x4898, 0x84, 0xa4, 0xc2, 0x9, 0x86, 0x61, 0xe2, 0xbc };

// IID of IDivision Interface {E0D476EE-5F8C-41A5-943F-6352027042AD}
const IID IID_IDivision = { 0xe0d476ee, 0x5f8c, 0x41a5, 0x94, 0x3f, 0x63, 0x52, 0x2, 0x70, 0x42, 0xad };




