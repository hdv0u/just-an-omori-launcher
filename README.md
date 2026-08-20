# Just an OMORI Launcher

A lightweight launcher that replaces the original batch file used to start OMORI.

## Features

- Starts the game's original executable.
- Passes the required command-line argument.
- Sets the working directory to the game's directory.
- Does not modify, replace, rename, or delete the original game files.
- Does not require the original `.bat` file.
- Can be pinned to the Windows taskbar.
- Can be placed outside the game folder as a shortcut or copied elsewhere without needing to keep the `.bat` file itself.

## Installation

1. Obtain a legitimate copy of OMORI.
2. Place `OMORI_Launcher.exe` in the same directory as the game's executable.
3. Run `OMORI_Launcher.exe`.

The launcher must remain able to locate the game's directory.

For convenient access, you can create a shortcut to the launcher on your desktop or pin it to the taskbar.

## Building

Requires:

- MinGW-w64 / GCC
- Windows
- `windres`

Build the resources:

    windres resource.rc resource.o

Compile the launcher:

    g++ launcher.cpp resource.o -std=c++17 -o OMORI_Launcher.exe -mwindows

## Disclaimer

This is an unofficial launcher and is not affiliated with or endorsed by the developers or publishers of OMORI.

The launcher does not include the game itself or any of its original files. Users must obtain the game separately.

## License

[MIT License](LICENSE)