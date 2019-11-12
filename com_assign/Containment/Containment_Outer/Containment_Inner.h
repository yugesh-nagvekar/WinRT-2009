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


// CLSID of MultiplicationDivision Component {AF70CE53-3A65-4B89-8A9F-3700B44032BB}
const CLSID CLSID_MultiplicationDivision = { 0xaf70ce53, 0x3a65, 0x4b89, 0x8a, 0x9f, 0x37, 0x0, 0xb4, 0x40, 0x32, 0xbb };

// IID of IMultiplication Interface {B788C2D5-F42D-4B31-82BC-A0AE3C4787D3}
const IID IID_IMultiplication = { 0xb788c2d5, 0xf42d, 0x4b31, 0x82, 0xbc, 0xa0, 0xae, 0x3c, 0x47, 0x87, 0xd3 };

// IID of IDivision Interface {366A609C-8ECC-41C5-84B7-ACAC5857D47F}
const IID IID_IDivision = { 0x366a609c, 0x8ecc, 0x41c5, 0x84, 0xb7, 0xac, 0xac, 0x58, 0x57, 0xd4, 0x7f };


