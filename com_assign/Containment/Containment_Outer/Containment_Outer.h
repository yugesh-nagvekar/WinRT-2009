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


// CLSID of SumSubtract Component {2B1303C9-088D-40E6-A7BD-627EE5FA8844}
const CLSID CLSID_SumSubtract = { 0x2b1303c9, 0x88d, 0x40e6, 0xa7, 0xbd, 0x62, 0x7e, 0xe5, 0xfa, 0x88, 0x44 };

// IID of ISum Interface {8A1DF8F3-B841-45A4-9372-F587D37A38D1}
const IID IID_ISum = { 0x8a1df8f3, 0xb841, 0x45a4, 0x93, 0x72, 0xf5, 0x87, 0xd3, 0x7a, 0x38, 0xd1 };

// IID of ISubtract Interface {7BED7432-D78C-441F-A313-362F97CF45AB}
const IID IID_ISubtract = { 0x7bed7432, 0xd78c, 0x441f, 0xa3, 0x13, 0x36, 0x2f, 0x97, 0xcf, 0x45, 0xab };

