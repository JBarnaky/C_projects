// 
// Client.cpp 
// 
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>

#include <initguid.h>

 
#include "D:\ServerInd_SOL\ServerInd\IFN_15.h" 


int main( int argc, char *argv[] ) 
  { 
  printf( "Initializing COM \n"); 
  if ( FAILED( CoInitialize( NULL ))) 
      { printf( "Unable to initialize COM \n"); return -1; } 
  char* szProgID = "YatskCOM.1"; 
  WCHAR szWideProgID[128]; 
  CLSID clsid; 
  long lLen = MultiByteToWideChar( CP_ACP, 0, szProgID, 
                             strlen( szProgID ), szWideProgID, sizeof( szWideProgID ) ); 
  szWideProgID[ lLen ] = '\0'; 
  HRESULT hr = ::CLSIDFromProgID( szWideProgID, &clsid ); 
  if ( FAILED( hr )) 
       { printf("Unable to get CLSID from ProgID. HR = %X \n",hr); return -1; }
 
  IClassFactory* pCF; 
  // Получить фабрику класса для CFN_15 
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
  pMath->WINAPIFun71( 20, 7, &result ); 
  printf("20 + 7 is %lf \n",result); 

  float result2; 
  pMath->Fun72( 20, 12, 6, &result2 ); 
  printf("20 - 12 - 6 is %lf \n",result2);  

    double result3; 
  pMath->Fun73 ( 1.5, &result3 ); 
  printf("1.5 * 1.5 is %lf \n",result3); 
  printf("Releasing instance \n"); 

  pMath->Release(); 

  IUnknown* pUnk2; 
  hr = pCF->CreateInstance( NULL, IID_IVer, (void**) &pUnk2 ); 
  // Release the class factory pCF->Release(); 
  if ( FAILED( hr )) 
        { printf("Failed to create server instance. HR =%X \n",hr); return -1; } 
  printf("Instance IVer created \n"); 
  IVer* pMath2 = NULL; 
  hr = pUnk2->QueryInterface( IID_IVer, (LPVOID*)&pMath2 ); 
  pUnk2->Release(); 
  if ( FAILED( hr )) 
        { printf("QueryInterface() for IVer failed \n"); return -1; } 
  
  wchar_t* result4; 
  pMath2->GetAuthor(  &result4 ); 
  printf("Author: ");
  wprintf(result4); 

   pMath2->Release(); 
  printf("\nShuting down COM\n"); 
  CoUninitialize(); 
  return 0; 
} 
 

