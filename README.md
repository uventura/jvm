# Java Virtual Machine (jvm)
Implementation of Java Virtual Machine using C language.

## How to Run and Build?
```
    make            => Build JVM project
    make run        => Run generated project
    make test       => Run tests
```

## How to Run Analyzers and Formaters
```
    make ubsa       => Run Undefined Behavior Sanitizer
    make asan       => Run Address Sanitizer
    make cppcheck   => Run CPP Check
    make check      => Run asan, ubsan and cppcheck
    make format     => Run Code Style format
```

## Requirements
In a Linux environment you will need:
    * Clang         (e.g.: sudo apt install clang)
    * LLVM          (e.g.: sudo apt install llvm)
    * CPPCheck      (e.g.: sudo apt install cppcheck)
    * GCC >= 9.0    (e.g.: sudo apt install build-essential)
