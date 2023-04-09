#pragma once

#include <iostream>
#include <map>

// Return list of serial ports as (number, name)
std::map<int, std::wstring> enumerateSerialPorts();
