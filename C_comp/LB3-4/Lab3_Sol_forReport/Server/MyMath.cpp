// MyMath.cpp : Implementation of CMyMath

#include "stdafx.h"
#include "MyMath.h"


// CMyMath



STDMETHODIMP CMyMath::Add(LONG x, LONG y, LONG* z)
{
	// TODO: Add your implementation code here
	*z=x+y;
	return S_OK;
}


STDMETHODIMP CMyMath::Subtract(LONG x, LONG y, LONG* z)
{
	// TODO: Add your implementation code here
	*z=x-y;
	return S_OK;
}


STDMETHODIMP CMyMath::Multiply(LONG x, LONG y, LONG* z)
{
	// TODO: Add your implementation code here
	*z=x*y;
	return S_OK;
}


STDMETHODIMP CMyMath::Divide(LONG x, LONG y, LONG* z)
{
	// TODO: Add your implementation code here
	*z=x/y;
	return S_OK;
}
