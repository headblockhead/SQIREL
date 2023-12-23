# kbd

## Tasks

### Build
Env: PICO_SDK_PATH
Directory: ./build

Builds the keyboard firmware.

```bash
cmake ..
make -j4
cp compile_commands.json ../ # Required file for LSP autocomplete.
```

### Clean
Cleans the build directory for a fresh build.

```bash
rm -rf ./build
mkdir build
```
