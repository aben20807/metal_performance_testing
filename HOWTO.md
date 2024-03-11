# Build and Run without GUI

## Tested environmnt

+ macOS 14.3.1 23D60 (`sw_vers`)
+ Darwin Kernel Version 23.3.0 (`uname -a`)
+ `xcode-select -print-path`: /Applications/Xcode-15.2.0.app/Contents/Developer

## Requirements

### Install build tools

```bash
brew install cmake ninja
```

### Your metal-cpp (optional)

metal-cpp_macOS14.2_iOS17.2 has been download in `metal-cpp`

```bash
cd metal_performance_testing/
curl -LO https://developer.apple.com/metal/cpp/files/metal-cpp_macOS14.2_iOS17.2.zip
unzip metal-cpp_macOS14.2_iOS17.2.zip
```

## Generate the build script

In `metal_performance_testing/`:

```bash
cmake -S . -B build -G "Ninja Multi-Config"
```

## Build C++ source files

In `metal_performance_testing/`:

```bash
cmake --build build --config Release
```

One executable (`metal_performance_testing`) will be generated in `metal_performance_testing/build/Release`.

## Compile *.metal files

In `metal_performance_testing/build/Release`:

```bash
xcrun -sdk macosx metal -frecord-sources=flat ../../*.metal
```

Two files (`default.metallib`, `default.metallibsym`) will be generated.

## Run

```bash
./metal_performance_testing
```
