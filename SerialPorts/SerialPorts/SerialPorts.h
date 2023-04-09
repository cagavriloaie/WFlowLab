#pragma once

#include <iostream>
#include <map>

#define EXTERN_DLL_EXPORT  __declspec(dllexport)

// Return list of serial ports as (number, name)
EXTERN_DLL_EXPORT const wchar_t* enumerateSerialPorts();
