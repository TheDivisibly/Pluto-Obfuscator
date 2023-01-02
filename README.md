# Pluto-Obfuscator
Pluto-Obfuscator new Pass Manager port

How to build:
1. build llvm using latest llvm sources.
2. point `include` and `lib` in `CMakeLists.txt` to the right path.

How to use:
```shell
.\clang.exe main.cpp "-fpass-plugin=HelloWorld.dll" -o main.exe
```
