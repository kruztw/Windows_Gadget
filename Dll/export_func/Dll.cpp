// Dll.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Dll.h"
#include <stdio.h>

DLL_API int __cdecl say_hi(void)
{
    printf("hello world\n");
    return 0;
}

