#include "includes/win_modules.hpp"
#include "sdk/sdk.hpp"
DWORD WINAPI start(LPVOID hModule)//данный поток не затрагивает процессы игры
{
    bool bnExit = true;
    if ((bnExit = c_sdk->initialize()))c_sdk->hook();
    while (!GetAsyncKeyState(VK_HOME) && bnExit)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    c_sdk->unhook();

    return 0;
}
BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    DisableThreadLibraryCalls(hModule);
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, start, hModule, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:   
        FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);
       // Beep(1000, 1000);   
        break;
    }
    return TRUE;
}

