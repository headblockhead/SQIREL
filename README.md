# SQUIRREL - Simplified QMK as a library
<sup>or: Simple QMK Uniquely Inspired *Really* Runtime Editable Library</sup>

🚧 This project is currently **under construction**, so do not expect a usable result yet! 🚧

## Goals:
- Create an easy to understand and simple keyboard library that allows for runtime layout and configuration edits.
- Make sure it is as documented and clearly organised as possible.
- Keep it independent of any microcontroller.

For an example implementation of SQUIRREL, see the [SQUIRREL-pico](https://github.com/headblockhead/SQUIRREL-pico) example template.

## Tasks

### Build
Directory: ./build

Builds a static archive library (`.a`).

```bash
cmake ..
make -j16
cp compile_commands.json ../ # Required file for LSP autocomplete.
```

### Clean
Cleans the build directory for a fresh build.

```bash
rm -rf ./build
mkdir build
```
