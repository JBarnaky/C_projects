// MyInd.cpp : Implementation of CMyInd

#include "stdafx.h"
#include "MyInd.h"


// CMyInd



STDMETHODIMP CMyInd::Fun151(LONG x, LONG y, DOUBLE* z)
{
	// TODO: Add your implementation code here
	*z=x+y;
	return S_OK;
}


STDMETHODIMP CMyInd::Fun152(LONG x, LONG y,  LONG n, DOUBLE* z)
{
	// TODO: Add your implementation code here
	*z=(double)x - y - n;
	return S_OK;
}


STDMETHODIMP CMyInd::Fun153(DOUBLE x, DOUBLE* y)
{
	// TODO: Add your implementation code here
	*y=x*x;
	return S_OK;
}


STDMETHODIMP CMyInd::GetAuthor(wchar_t** pResult)
{
	wchar_t* name=TEXT("PAUL YATSK 70322");
	wchar_t* p =(wchar_t*)CoTaskMemAlloc(wcslen(name));

	wcscpy(p,name);
	*pResult=p;
	return S_OK;
}
