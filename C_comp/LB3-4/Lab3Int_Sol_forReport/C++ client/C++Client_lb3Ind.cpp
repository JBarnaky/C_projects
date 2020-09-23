// 
// Client.cpp 
// 
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>

#include <initguid.h>


int main( int argc, char *argv[] ) 
  { 
  printf( "Initializing library OLE \n"); 
  HRESULT hr = OleInitialize(NULL);
  if ( FAILED( hr)) 
      { printf( "Unable to initialize OLE \n"); return -1; } 

  //Получаем CLSID приложения через ProgID
    wchar_t progid[] = L"Lb3Ind_autosvr.MyInd.1"; 
	CLSID clsid;
	hr=::CLSIDFromProgID(progid,&clsid);
	if ( FAILED( hr )) 
	{
		printf("Failed CLSIDFromProgID");
		return -1;
	}
	//Создаем компонент
	IDispatch* pIDispatch = NULL;
	hr=::CoCreateInstance(clsid,NULL, CLSCTX_INPROC_SERVER,IID_IDispatch,(void**)&pIDispatch);
	if ( FAILED( hr )) 
	{
		printf("Failed CoCreateInstance");
		return -1;
	}

	
	// Получаем диспетчерский идентификатор
	DISPID dispid; 
	OLECHAR* name = L"Fun71";
	pIDispatch->GetIDsOfNames(
		IID_NULL, // Должно быть IID_NULL
		&name, // Имя функции
		1, // Число имен
		GetUserDefaultLCID(), // Информация локализации
		&dispid
	);	
	
	VARIANTARG rgvarg[2];
	VariantInit(&rgvarg[0]);
	rgvarg[0].vt = VT_I4;
	rgvarg[0].lVal = 22;
	VariantInit(&rgvarg[1]);
	rgvarg[1].vt = VT_I4;
	rgvarg[1].lVal = 11;


	DISPPARAMS dispparams = {
		rgvarg,
		NULL,
		2,
		0
	};		
	
	VARIANT pResult;
	// Простейший вызов Invoke
	pIDispatch->Invoke(dispid, // DISPID
		IID_NULL, // Должно быть IID_NULL
		GetUserDefaultLCID(), // Информация локализации
		DISPATCH_METHOD, // Метод
		&dispparams, // Аргументы метода
		&pResult, // Результаты
		NULL, // Исключение
		NULL); // Ошибка в аргументе 

	printf("Fun151: 22 + 11 = %lf", (float)pResult.lVal);
	return 0;
} 
 

