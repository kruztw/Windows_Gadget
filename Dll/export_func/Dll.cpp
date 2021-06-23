// Dll.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Dll.h"
#include <stdio.h>


// This is an example of an exported variable
DLL_API int nDll=0;

// This is an example of an exported function.
DLL_API int say_hi(void)
{
    printf("hello world\n");
    return 0;
}

// This is the constructor of a class that has been exported.
CDll::CDll()
{
    return;
}
