#include <iostream>
#include <thread>
#include <windows.h>

bool isRunning = true;

void Initialize() {
    std::cout << "[!] Initializing" << std::endl;


    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "[!] Shutting down" << std::endl;

}

void Release() {
    std::cout << "[!] Releasing resources" << std::endl;

}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD call_reason, void* reserved) {
    switch (call_reason) {
        case DLL_PROCESS_ATTACH:
            if (HANDLE handle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Initialize, nullptr, 0, nullptr)) {
                CloseHandle(handle);
            }
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;

        case DLL_PROCESS_DETACH:
            isRunning = false;

            Release();
            break;

        default:
            break;
    }

    return TRUE;
}
