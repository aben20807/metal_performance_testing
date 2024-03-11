# Build and Run without GUI

## Tested environmnt

+ macOS 14.3.1 23D60 (`sw_vers`)
+ Darwin Kernel Version 23.3.0 (`uname -a`)
+ `xcode-select -print-path`: /Applications/Xcode-15.2.0.app/Contents/Developer

## Requirements

### Clone the repo

```bash
git clone https://github.com/aben20807/metal_performance_testing.git
cd metal_performance_testing/metal_performance_testing/
export WORKSPACE=$(pwd)
```

Following commands use `metal_performance_testing/metal_performance_testing/` (`$WORKSPACE`) as the default working directory

### Install build tools

```bash
brew install cmake ninja
```

### Your metal-cpp (optional)

metal-cpp_macOS14.2_iOS17.2 has been download in `metal-cpp`

```bash
rm -r metal-cpp/ # remove the original version
curl -LO https://developer.apple.com/metal/cpp/files/metal-cpp_macOS14.2_iOS17.2.zip
unzip metal-cpp_macOS14.2_iOS17.2.zip
```

## Generate the build script

```bash
cmake -S . -B build -G "Ninja Multi-Config"
```

## Build C++ source files

```bash
cmake --build build --config Release
```

One executable (`metal_performance_testing`) will be generated in `$WORKSPACE/build/Release`.

## Compile *.metal files

```bash
cd $WORKSPACE/build/Release
```

```bash
xcrun -sdk macosx metal -frecord-sources=flat ../../*.metal
```

Two files (`default.metallib`, `default.metallibsym`) will be generated.

## Run

```bash
./metal_performance_testing
```
