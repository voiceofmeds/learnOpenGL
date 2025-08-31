## Requirements
- CMake (>=3.11)
- A C compiler compatible with CMake

## Recommendations
- Install Ninja and use it as CMake's generator for this project

## Compiling
Clone this repository
```
git clone https://github.com/voiceofmeds/learnOpenGL.git
cd learnOpenGL
```

Run CMake
```
cmake -S . -B build
```
or if you want to use Ninja
```
cmake -G Ninja -S . -B build
```

Build the project
```
cmake --build build --config Release
```
