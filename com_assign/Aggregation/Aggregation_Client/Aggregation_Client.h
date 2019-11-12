#pragma once

class ISum : public IUnknown
{
public:
	//ISum specific method declaration
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;//pure virtual
};

class ISubtract : public IUnknown
{
public:
	//ISubtract specific method declaration
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0; // pure virtual
};

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

// CLSID of SumSubtract Component {35C24C2E-9FAA-413A-B90F-FC1FE4474DFA}
const CLSID CLSID_SumSubtract = { 0x35c24c2e, 0x9faa, 0x413a, 0xb9, 0xf, 0xfc, 0x1f, 0xe4, 0x47, 0x4d, 0xfa };

// IID of ISum Interface {A982DFF0-AC67-493C-91C6-1FF1156AE205}
const IID IID_ISum = { 0xa982dff0, 0xac67, 0x493c, 0x91, 0xc6, 0x1f, 0xf1, 0x15, 0x6a, 0xe2, 0x5 };

// IID of ISubtract Interface {D107BA2C-964B-4755-87F6-4EDB4A621D92}
const IID IID_ISubtract = { 0xd107ba2c, 0x964b, 0x4755, 0x87, 0xf6, 0x4e, 0xdb, 0x4a, 0x62, 0x1d, 0x92 };

//// CLSID of MultiplicationDivision Component {3B056759-B556-4350-804F-46CEF1B840A9}
//const CLSID CLSID_MultiplicationDivision = { 0x3b056759, 0xb556, 0x4350, 0x80, 0x4f, 0x46, 0xce, 0xf1, 0xb8, 0x40, 0xa9 };

// IID of IMultiplication Interface {E0123791-3701-4898-84A4-C2098661E2BC}
const IID IID_IMultiplication = { 0xe0123791, 0x3701, 0x4898, 0x84, 0xa4, 0xc2, 0x9, 0x86, 0x61, 0xe2, 0xbc };

// IID of IDivision Interface {E0D476EE-5F8C-41A5-943F-6352027042AD}
const IID IID_IDivision = { 0xe0d476ee, 0x5f8c, 0x41a5, 0x94, 0x3f, 0x63, 0x52, 0x2, 0x70, 0x42, 0xad };




