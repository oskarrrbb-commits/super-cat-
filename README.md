# Super Cat

A small 2D platformer written in C++ with SDL2. You play as a cat going through 11 rooms, jumping over spikes, dodging birds, fighting frogs with a sword and finally beating the King Frog.

> **Note:** I know the code is far from perfect (one big `main.cpp`, lots of globals and copy-paste). This was my first project made completely on my own, from start to finish, and I'm keeping it as it is.

## Controls

| Key   | Action                     |
|-------|----------------------------|
| A / D | Move left / right          |
| Space | Jump                       |
| K     | Sword attack (once picked up) |

## What it uses

- C++ (g++ / MinGW on Windows)
- [SDL2](https://github.com/libsdl-org/SDL/releases) – window, rendering, input
- [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer/releases) – music (MP3)
- BMP sprites and MP3 music in `assets/`

## How to compile (Windows, MinGW)

1. Install MinGW-w64 (g++ and `mingw32-make`).
2. Download the **MinGW development** packages for SDL2 and SDL2_mixer
   (`SDL2-devel-2.x.x-mingw.zip` and `SDL2_mixer-devel-2.x.x-mingw.zip`).
3. From the `x86_64-w64-mingw32` folder of each package copy:
   - `include/SDL2/*` → `src/include/SDL2/`
   - `lib/*` → `src/lib/`
4. Build:
   ```
   mingw32-make
   ```
   or directly:
   ```
   g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer
   ```
5. Copy `SDL2.dll`, `SDL2_mixer.dll` (and `libmpg123-0.dll` from SDL2_mixer for MP3 support) from the packages' `bin` folders next to `main.exe`.
6. Run `main.exe` from the project folder, so it can find `assets/`.
