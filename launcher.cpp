#include <windows.h>
#include <filesystem>
#include <string>

// Exact filename of the original game's executable
const wchar_t* GAME_FILENAME = L"OMORI.exe";

// Exact argument from the original BAT file
const wchar_t* GAME_ARGUMENT = L"--6bdb2e585882fbd48826ef9cffd4c511";

// Display an error message.
void ShowError(const std::wstring& message){
    MessageBoxW(
        nullptr,
        message.c_str(),
        L"Game Launcher Error",
        MB_ICONERROR
    );
}

// Program entry point.
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){

    // 1. Find the directory containing launcher.exe.
    // equivalent of the BAT doing: cd /d "%~dp0"

    wchar_t launcherPath[MAX_PATH];

    DWORD pathLength = GetModuleFileNameW(
        nullptr,
        launcherPath,
        MAX_PATH
    );

    if (pathLength == 0){
        ShowError(
            L"Could not determine the launcher's location."
        );

        return 1;
    }

    std::filesystem::path gameDirectory =
        std::filesystem::path(launcherPath).parent_path();

    // 2. Construct the path to the original game executable
    std::filesystem::path gameExecutable =
        gameDirectory / GAME_FILENAME;

    // 3. Make sure the original game EXE exists. Do not modify
    if (!std::filesystem::exists(gameExecutable)){
        ShowError(
            L"Could not find the game's executable:\n\n" +
            gameExecutable.wstring()
        );

        return 1;
    }

    // 4. Build the exact command line.
    // Equivalent to: game.exe --6bdb2e585882fbd48826ef9cffd4c511
    std::wstring commandLine =
        L"\"" +
        gameExecutable.wstring() +
        L"\" " +
        GAME_ARGUMENT;

    // 5. Configure Windows process startup
    STARTUPINFOW startupInfo{};

    startupInfo.cb = sizeof(startupInfo);

    PROCESS_INFORMATION processInfo{};

    // 6. Start the original game
    BOOL processStarted = CreateProcessW(
        nullptr,
        commandLine.data(),
        nullptr,
        nullptr,
        FALSE,
        0,
        nullptr,
        gameDirectory.c_str(),
        &startupInfo,
        &processInfo
    );

    // 7. Check if Windows successfully launched it
    if (!processStarted){
        DWORD errorCode = GetLastError();

        ShowError(
            L"Windows could not start the game.\n\n"
            L"Error code: " +
            std::to_wstring(errorCode)
        );

        return 1;
    }

    // 8. Wait for the game process to finish
    //
    // Not necessary for launching the game,
    // but it keeps the launcher alive until the game exits

    WaitForSingleObject(
        processInfo.hProcess,
        INFINITE
    );

    // 9. Close handles created by CreateProcessW()
    CloseHandle(
        processInfo.hThread
    );
    CloseHandle(
        processInfo.hProcess
    );

    return 0;
}