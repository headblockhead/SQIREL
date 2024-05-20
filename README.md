# SQUIRREL - Simplified, runtime-configurable QMK as a library
<sup>or: Simplified QMK Uniquely Immaculate (and) Readable Runtime Editable Library</sup>

🚧 This project is currently **under construction**, so do not expect a usable result yet! 🚧

## Goals:
- Create an easy to understand and simple keyboard library that allows for runtime layout and configuration edits.
- Make sure it is as documented and clearly organised as possible.
- Keep it independent of any microcontroller.

For an example implementation of SQUIRREL, see the [SQUIRREL-pico](https://github.com/headblockhead/SQUIRREL-pico) example template.

## Development

SQUIRREL uses [nix](https://nixos.org).
To develop, run the nix shell using `nix develop`. SQUIRREL can also be built using `nix build`.

## Tasks

### Build
Directory: ./build

Builds a static archive library (`.a`).

```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4
```

### Build-debug
Directory: ./build

Builds the library with debug build type.

```bash
cmake -DCMAKE_BUILD_TYPE=Debug .. 
make -j4
cp compile_commands.json ../ # Copies the autocomplete information for ccls.
```

### Clean
Cleans the build directory for a fresh build.

```bash
rm -rf ./build
mkdir build
```

### Test
Directory: ./build

Runs the unit tests.

```bash
cmake -S. -DBUILD_TESTING=true ..
cmake --build .
ctest
```
