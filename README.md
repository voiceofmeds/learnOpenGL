## Requirements
- CMake (>=3.11)
- C compiler compatible with CMake (e.g., GCC, Clang, MSVC)

## Recommendations
- Install Ninja and use it as CMake's generator for this project (for faster
builds)

## Compiling
Clone this repository
```
git clone https://github.com/voiceofmeds/learnOpenGL.git
cd learnOpenGL
```

Using default generator
```
cmake -S . -B build
```
Using Ninja (recommended)
```
cmake -G Ninja -S . -B build
```

Build the project
```
cmake --build build --config Release
```

Go to directory where the executable is
```
cd build
```
Then run the executable
```
./learnOpenGL
```
If on Windows, do
```
./learnOpenGL.exe
```
