#pragma once

#include <Windows.h>
#include <tlhelp32.h>
#include <string>
#include <iostream>

class Memory
{
public:
	Memory();

	template <typename T>
	T Read(uintptr_t offset)
	{
		T buffer;
		ReadProcessMemory(hProcess, (LPCVOID)(playerBase + offset), &buffer, sizeof(T), NULL);
		return buffer;
	}

	template <typename T>
	void Write(uintptr_t offset, const T& value)
	{
		WriteProcessMemory(hProcess, (LPVOID)(playerBase + offset), &value, sizeof(T), NULL);
	}

private:
	uintptr_t getModuleBaseAddress(DWORD pid, const std::wstring& moduleName);
	void initPlayerBaseAddress();

	DWORD pid;
	HWND hwnd;
	HANDLE hProcess;
	uintptr_t baseAddress;
	uintptr_t playerBase;
};
