/*
 An example that demonstrates using Shared memory management for 
 communicating between Mathematica and a DLL.
*/

#include "math.h"
#include "WolframLibrary.h"
#include "WolframRTL.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


DLLEXPORT mint WolframLibrary_getVersion( ) {
	return WolframLibraryVersion;
}


DLLEXPORT int WolframLibrary_initialize( WolframLibraryData libData) {
	return 0;
}

/* Uninitialize Library */
DLLEXPORT void WolframLibrary_uninitialize(WolframLibraryData libData) {
	return;
}

DLLEXPORT int mod2(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {

	MTensor tensor1=MArgument_getMTensor(Args[0]);
	mint *pt=MTensor_getIntegerDataMacro(tensor1); 
	mint len=libData->MTensor_getFlattenedLength(tensor1);
	for(int i=0;i<len;i++){
		pt[i]*=(2-(pt[i]%2));
	}	
	// libData->MTensor_disownAll(tensor1);
	// MArgument_setInteger(Res, 0);
	MArgument_setMTensor(Res, tensor1);
	return 0;
}

DLLEXPORT int mod2omp(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {

	MTensor tensor1=MArgument_getMTensor(Args[0]);
	mint *pt=MTensor_getIntegerDataMacro(tensor1); 
	mint len=libData->MTensor_getFlattenedLength(tensor1);
	#pragma omp parallel for 
	for(int i=0;i<len;i++){
		pt[i]*=(2-(pt[i]%2));
	}	
	// libData->MTensor_disownAll(tensor1);
	// MArgument_setInteger(Res, 0);
	MArgument_setMTensor(Res, tensor1);
	return 0;
}

