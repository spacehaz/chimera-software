# Chimera — ESP32-S3 project (ESP-IDF 6.1)

Pet "chimera" firmware for an ESP32-S3-DevKitC-1 N16R8 (16MB flash, 8MB Octal PSRAM).
Part of the embedded plan in `../CLAUDE.md`. The project was recreated from scratch, step by step.

## Learning mode (read first)

- The user writes the code. Claude explains, reviews and gives small examples on request.
- Do not hand over finished firmware for the current topic. Give specs, commands and review.
- Explain each step (what the command or line does) before moving on.
- Work one step at a time and wait for the user's output before the next step.

## Environment

- ESP-IDF: `~/.espressif/v6.1/esp-idf`
- Activate in every new terminal tab: `. ~/.espressif/v6.1/esp-idf/export.sh`
- Project path: `/Users/hazobaykulov/www/native-dev/C-CPP/chimera`
- The parent folder is `C-CPP` (no `&` in the path: unquoted `&` breaks the ESP-IDF build).
- The shell does not persist env vars: run `export.sh` again in each new session.

## Current state

Done:
1. `idf.py create-project chimera` (template created `main/chimera.c`, renamed to `main/main.c`)
2. `idf.py set-target esp32s3` (`CONFIG_IDF_TARGET="esp32s3"`)
3. `idf.py menuconfig`: flash 16MB, Octal PSRAM enabled (`CONFIG_SPIRAM_MODE_OCT=y`)
4. `main/CMakeLists.txt` uses `main.c`
5. Component `components/game_logic/`: `CMakeLists.txt`, `game_logic.h`, `game_logic.c`, empty `test/`
6. `main/CMakeLists.txt` has `REQUIRES game_logic`

Next:
7. Write `main/main.c`: pet with `hunger = 50`, loop every 5 s, `feed_pet` when `hunger < 70`. Then `idf.py build`.
8. Unit tests with Unity: `test/` folder in the component, a separate `test_app/` project, `TEST_COMPONENTS "game_logic"` set before `include(project.cmake)` in `test_app/CMakeLists.txt`. Test file: `components/game_logic/test/test_game_logic.c`.
9. `git init` + `.gitignore` (`build/`, `sdkconfig.old`, `managed_components/`, `dependencies.lock`).
10. Flash and run on the board: `idf.py -p <PORT> flash monitor`.

## Rules we learned

- Put `#include <stddef.h>` in any `.c` file that uses `NULL`.
- Headers are not in `SRCS`; they are exposed via `INCLUDE_DIRS`.
- Each component is a folder under `components/` with its own `CMakeLists.txt`.
- Components list dependencies in `REQUIRES`.
- `typedef struct { ... } name_t;` is the standard C pattern for types.
- `sdkconfig` must match the board: changing the target with `set-target` deletes `sdkconfig` and `build/`.
- VS Code: open the project folder itself (not the parent), then run `C/C++: Reset IntelliSense Database`. The compiler in `.vscode/settings.json` must be `xtensa-esp32s3-elf-gcc`.

## Useful commands

```sh
. ~/.espressif/v6.1/esp-idf/export.sh
cd "/Users/hazobaykulov/www/native-dev/C-CPP/chimera"
idf.py build
idf.py -p /dev/cu.usbmodemXXXX flash monitor
idf.py menuconfig
grep -E '^CONFIG_IDF_TARGET=|^CONFIG_ESPTOOLPY_FLASHSIZE=|^CONFIG_SPIRAM=' sdkconfig
```
