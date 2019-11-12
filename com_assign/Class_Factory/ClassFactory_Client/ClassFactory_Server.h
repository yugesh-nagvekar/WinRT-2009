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


// CLSID of SumSubtract Component {993E8B7D-6B04-40F3-8DF5-29B86E5D47F7}
const CLSID CLSID_SumSubtract = { 0x993e8b7d, 0x6b04, 0x40f3, 0x8d, 0xf5, 0x29, 0xb8, 0x6e, 0x5d, 0x47, 0xf7 };

// IID of ISum Interface {EA215883-3B1C-47C2-9E85-6DA12C9ADC15}
const IID IID_ISum = { 0xea215883, 0x3b1c, 0x47c2, 0x9e, 0x85, 0x6d, 0xa1, 0x2c, 0x9a, 0xdc, 0x15 };

// IID of ISubtract Interface {7DED31C0-6460-493D-A232-51CAC6368401}
const IID IID_ISubtract = { 0x7ded31c0, 0x6460, 0x493d, 0xa2, 0x32, 0x51, 0xca, 0xc6, 0x36, 0x84, 0x1 };

