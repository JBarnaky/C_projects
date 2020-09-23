#include <windows.h>
#include <tchar.h> 
#include <stdio.h>

#include <initguid.h>
#include "D:\server2_for_lb1\server2\IFN_15.h" 

int main( int argc, char *argv[] ) 
  { 
  printf( "Initializing COM \n"); 
  if ( FAILED( CoInitialize( NULL ))) 
      { printf( "Unable to initialize COM \n"); return -1; } 
  char* szProgID = "FN.15.1";// 
  WCHAR szWideProgID[128]; 
  CLSID clsid; 
  long lLen = MultiByteToWideChar( CP_ACP, 0, szProgID, 
                             strlen( szProgID ), szWideProgID, sizeof( szWideProgID ) ); 
  szWideProgID[ lLen ] = '\0'; 
  HRESULT hr = ::CLSIDFromProgID( szWideProgID, &clsid ); 
  if ( FAILED( hr )) 
       { printf("Unable to get CLSID from ProgID. HR = %X \n",hr); return -1; }
 
  IClassFactory* pCF; 
  // Получить фабрику класса для CMath 
  hr = CoGetClassObject( clsid, CLSCTX_INPROC, NULL, 
                                  IID_IClassFactory, (void**) &pCF ); 
  if ( FAILED( hr )) 
        { printf("Failed to GetClassObject server instance. HR = %X \n",hr); return -1; } 
  
  // с помощью фабрики класса создать экземпляр 
  // компонента и получить интерфейс IUnknown. 
  
  IUnknown* pUnk; hr = pCF->CreateInstance( NULL, IID_IUnknown, (void**) &pUnk ); 
  
  // Release the class factory pCF->Release(); 
  if ( FAILED( hr )) 
        { printf("Failed to create server instance. HR =%X \n",hr); return -1; } 
  printf("Instance created \n"); 
  IFN_15* pMath = NULL; 
  hr = pUnk->QueryInterface( IID_IFN_15, (LPVOID*)&pMath ); 
  pUnk->Release(); 
  if ( FAILED( hr )) 
        { printf("QueryInterface() for IMath failed \n"); return -1; } 

 


  
  float result; 
  pMath->Fun151( 20, 7, &result ); 
  printf("20 + 7 is %d \n",result); 

  float result2;
  pMath->Fun152( 20, 12, 6, &result2 ); 
  printf("20 - 12 - 6 is %f \n",result2);

  double result3;
  pMath->Fun153( 1.5, &result3 ); 
  printf("1.5 * 1.5 is %f \n",result3);

Iver* pVer = NULL;
hr = pUnk-> QueryInterface( IID_IVer, (LPVOID*)&pVer );   
pUnk->Release();

  if ( FAILED( hr )) 
        { printf("QueryInterface() for IMath failed \n"); return -1; } 
	wchar_t* result4;
	pVer->GetAuthor(&result4);
	printf("Author\n");
	wprintf(result4);


  printf("\nReleasing instance \n"); 

  pMath->Release();
  //pVer->Release();
  printf("Shuting down COM\n"); 
  CoUninitialize(); 
  return 0; 
}
