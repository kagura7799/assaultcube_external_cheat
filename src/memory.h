#pragma once

#include <Windows.h>
#include <tlhelp32.h>
#include <string>
#include <iostream>

uintptr_t getModuleBaseAddress(DWORD pid, const std::wstring& moduleName);