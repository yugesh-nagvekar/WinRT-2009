#include <windows.h>
#include "Aggregation_Inner.h"

interface INoAggregationIUnknown
{
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void **) = 0;
	virtual ULONG __stdcall AddRef_NoAggregation(void) = 0;
	virtual ULONG __stdcall Release_NoAggregation(void) = 0;
};


//class Declaration 
class CMultiplicationDivision : public INoAggregationIUnknown, IMultiplication, IDivision
{
private:
	long m_cRef;
	IUnknown *m_pIUnknownOuter;
public:
	// couctructor
	CMultiplicationDivision(IUnknown*);
	// destructor
	~CMultiplicationDivision(void);

	// IUnknown specific method declaration (inherited method)
	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	// INoAggregationIUnknown specific method declaration (inherited method)
	HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void **);
	ULONG __stdcall AddRef_NoAggregation(void);
	ULONG __stdcall Release_NoAggregation(void);
	
	// ISum specific method declaration (inherited)
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	// ISubtract specific method declaration (inherited)
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);

};

class CMultiplicationDivisionClassFactory : public IClassFactory
{
private:
	long m_cRef;

public:
	// constructor
	CMultiplicationDivisionClassFactory(void);

	// destructor
	~CMultiplicationDivisionClassFactory(void);

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

// constructor implementation CMultiplicationDivision
CMultiplicationDivision::CMultiplicationDivision(IUnknown *pIUnknownOuter)
{
	// code 
	m_cRef = 1; // hardcoded Initialization to anticipate possible failure of QueryInterface()

	// increment global counter
	InterlockedIncrement(&glNumberOfActiveComponents);

	if (pIUnknownOuter != NULL)
		m_pIUnknownOuter = pIUnknownOuter;
	else
		m_pIUnknownOuter = reinterpret_cast<IUnknown*>(static_cast<INoAggregationIUnknown*>(this));
}

CMultiplicationDivision::~CMultiplicationDivision(void)
{
	// code
	// decrement global counter
	InterlockedDecrement(&glNumberOfActiveComponents);
}

//Implementation of CMultiplicationDivision's IUnknown methods
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
{
	// code 
	return (m_pIUnknownOuter->QueryInterface(riid, ppv));
}

ULONG CMultiplicationDivision::AddRef(void)
{
	// code
	return (m_pIUnknownOuter->AddRef());
}

ULONG CMultiplicationDivision::Release(void)
{
	// code
	return (m_pIUnknownOuter->Release());
}

//Implementation of CMultiplicationDivision's INoAggregationIUnknown methods
HRESULT CMultiplicationDivision::QueryInterface_NoAggregation(REFIID riid, void **ppv)
{
	// code 
	if (riid == IID_IUnknown)
		*ppv = static_cast<INoAggregationIUnknown*>(this);
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

ULONG CMultiplicationDivision::AddRef_NoAggregation(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMultiplicationDivision::Release_NoAggregation(void)
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

// Implementationi of IMultiplication's Methods
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 * num2;
	return (S_OK);
}

// Implementationi of IDivision's Methods
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 / num2;
	return (S_OK);
}

//Implementation of CMultiplicationDivisionClassFactory's constructor
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	//MessageBox(NULL, TEXT("CMultiplicationDivisionClassFactory Inner Constructor."), TEXT("Debug"), MB_OK);
	// hardcoded initialization to anticipate possible failure of Queryinterface()
	m_cRef = 1;
}

CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory()
{

}

// CMultiplicationDivisionClassFactory's QueryInterface() 
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void ** ppv)
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


ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	// code
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release(void)
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
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, void **ppv)
{
	//varialbe declaration
	CMultiplicationDivision *pCMultiplicationDivision = NULL;
	HRESULT hr;

	//MessageBox(NULL, TEXT("In Dll CreateInstance .."), TEXT("Debug"), MB_OK);

	//code
	if ( (pUnkOuter != NULL)  && (riid != IID_IUnknown) )
	{
		return (CLASS_E_NOAGGREGATION);
	}

	//create instance of componenet
	pCMultiplicationDivision = new CMultiplicationDivision(pUnkOuter);
	if (pCMultiplicationDivision == NULL)
		return(E_OUTOFMEMORY);

	//get the requested interface
	hr = pCMultiplicationDivision->QueryInterface_NoAggregation(riid, ppv);
	pCMultiplicationDivision->Release_NoAggregation(); // anticipate possible failure of QueryInterface
	return (hr);
}


HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
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
	CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;

	//MessageBox(NULL, TEXT("In Dll GetClassObject .."), TEXT("Debug"), MB_OK);

	//code 
	if (rclsid != CLSID_MultiplicationDivision)
		return (CLASS_E_CLASSNOTAVAILABLE);
	// create class factory
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
	if (pCMultiplicationDivisionClassFactory == NULL)
		return (E_OUTOFMEMORY);
	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release(); // anticipapte possible failure of QueryInterface()
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

