#include "memory.h"

uintptr_t getModuleBaseAddress(DWORD pid, const std::wstring& moduleName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (!hSnapshot)
    {
        std::cerr << "[ERROR] Failed to create modules snapshot (errno: " << GetLastError() << ")\n";
        ExitProcess(1);
    }

    MODULEENTRY32W moduleEntry{};
    moduleEntry.dwSize = sizeof(moduleEntry);

    if (Module32FirstW(hSnapshot, &moduleEntry))
    {
        do
        {
            if (moduleName == moduleEntry.szModule)
            {
                CloseHandle(hSnapshot);
                return reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
            }
        } while (Module32NextW(hSnapshot, &moduleEntry));
    }

    return NULL;
}

void initPlayerBaseAddress()
{
    hwnd = FindWindowA(NULL, "AssaultCube");

    if (!GetWindowThreadProcessId(hwnd, &pid))
    {
        std::cerr << "[ERROR] Assault Cube not found" << std::endl;
        ExitProcess(1);
    }

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess != NULL)
    {
        std::cout << "Process opened" << std::endl;
    }

    baseAddress = (DWORD)getModuleBaseAddress(pid, L"ac_client.exe");

    ReadProcessMemory(hProcess, (LPCVOID)(baseAddress + 0x195404), &playerBase, sizeof(DWORD), NULL);
}