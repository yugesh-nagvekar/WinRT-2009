#include <windows.h>
#include "Containment_Inner.h"
#include "Containment_Outer.h"

//class Declaration 
class CSumSubtract : public ISum, ISubtract, IMultiplication, IDivision
{
private:
	long m_cRef;
	IMultiplication *m_pIMultiplication;
	IDivision *m_pIDivision;

public:
	// couctructor
	CSumSubtract(void);
	// destructor
	~CSumSubtract(void);

	// IUnknown specific method declaration (inherited method)
	HRESULT __stdcall QueryInterface(REFIID, void **);

	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// ISum specific method declaration (inherited)
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	// ISubtract specific method declaration (inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	// IMultiplication specific method declaration (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	// IDivision specific method declaration (inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);

	// custom method for inner component creation
	HRESULT __stdcall InitializeInnerComponent(void);

};

class CSumSubtractClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	// constructor
	CSumSubtractClassFactory(void);

	// destructor
	~CSumSubtractClassFactory(void);

	// IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void **);

	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// IClassFactory specific method declaration (inherited)
	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);

};

//global variable declaration
long glNumberOfActiveComponents = 0; // number of active components
long glNumberOfServerLocks = 0; // number of locks on this dll

// DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	// code 

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		//MessageBox(NULL, TEXT("In Dll Process Attach .."), TEXT("Debug"), MB_OK);
		break;
	case DLL_PROCESS_DETACH:
		//MessageBox(NULL, TEXT("In Dll Process Detach .."), TEXT("Debug"), MB_OK);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return (TRUE);
}

// constructor implementation CSumSubtract
CSumSubtract::CSumSubtract(void)
{
	// initialization of private data members
	m_cRef = 1; // hardcoded Initialization to anticipate possible failure of QueryInterface()
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;

	// increment global counter
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract(void)
{
	// code
	// decrement global counter
	InterlockedDecrement(&glNumberOfActiveComponents);
	if (m_pIDivision)
	{
		m_pIDivision->Release();	
		m_pIDivision = NULL;
	}
	if (m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}
}

//Implementation of CSumSubtract's IUnknown methods
HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{

	// code 
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CSumSubtract::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtract::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return 0;
	}
	return (m_cRef);
}

// Implementationi of ISum's Methods
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 + num2;
	return (S_OK);
}

// Implementationi of ISubtract's Methods
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 - num2;
	return (S_OK);
}

// Implementationi of IMultiplication's Methods
HRESULT CSumSubtract::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
	// delegate to inner component
	m_pIMultiplication->MultiplicationOfTwoIntegers(num1, num2, pMultiplication);
	return (S_OK);
}

// Implementationi of IDivision's Methods
HRESULT CSumSubtract::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
	m_pIDivision->DivisionOfTwoIntegers(num1, num2, pDivision);
	return (S_OK);
}

HRESULT CSumSubtract::InitializeInnerComponent(void)
{
	// variable declaration
	HRESULT hr;
	//code
	hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication, (void**)&m_pIMultiplication);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultiplication Interface Can  Not Be Obtained From Inner Component."), TEXT("Program Error"), MB_OK);
		return(E_FAIL);
	}
	hr = m_pIMultiplication->QueryInterface(IID_IDivision, (void **)&m_pIDivision);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision Interface Can  Not Be Obtained From Inner Component."), TEXT("Program Error"), MB_OK);
		return(E_FAIL);
	}
	return (S_OK);
}

//Implementation of CSumSubtractClassFactory's constructor
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	//MessageBox(NULL, TEXT("CSumClassfactory Constructor."), TEXT("Debug"), MB_OK);
	// hardcoded initialization to anticipate possible failure of Queryinterface()
	m_cRef = 1;
}

CSumSubtractClassFactory::~CSumSubtractClassFactory()
{
	// code
}

// CSumSubtractClassFactory's QueryInterface() 
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void ** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *> (*ppv)->AddRef();
	return (S_OK);
}


ULONG CSumSubtractClassFactory::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
	// code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return 0;
	}
	return (m_cRef);
}


// Implementations of CSumSubtractClassFactory's IClsasfactory Methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, void **ppv)
{
	//varialbe declaration
	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;

	//MessageBox(NULL, TEXT("In Dll CreateInstance .."), TEXT("Debug"), MB_OK);

	//code
	if (pUnkOuter != NULL)
	{
		return (CLASS_E_NOAGGREGATION);
	}

	//create instance of componenet
	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL)
		return(E_OUTOFMEMORY);

	// initialize inner component
	hr = pCSumSubtract->InitializeInnerComponent();
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed to Initialize Inner Component."), TEXT("Program Error"), MB_OK);
		pCSumSubtract->Release();
		pCSumSubtract = NULL;
		return(hr);
	}

	//get the requested interface
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release(); // anticipate possible failure of QueryInterface
	return (hr);
}


HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	// code
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return (S_OK);
}

//Implementation of Exported functions from dll
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	// variable declaration 
	CSumSubtractClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	//MessageBox(NULL, TEXT("In Dll GetClassObject .."), TEXT("Debug"), MB_OK);

	//code 
	if (rclsid != CLSID_SumSubtract)
		return (CLASS_E_CLASSNOTAVAILABLE);
	// create class factory
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
		return (E_OUTOFMEMORY);
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release(); // anticipapte possible failure of QueryInterface()
	return (hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	// code
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}

