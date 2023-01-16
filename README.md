# Chip8

Chip8 Interpreter written in C using Raylib for Graphics


## Build From Source
```bash
    git clone https://github.com/WuGambinos/chip-8.git
```

### Requirements
    - make
    - gcc 
    - MinGW (Windows)

### Windows
```bash
    cd chip-8
    mkdir build
    cmake -G "MinGW Makefiles"..
    mingw32-make
```

### Mac OS
```bash
    cd chip-8
    mkdir build
    cmake ..
    make
```

### Linux 
```bash
    cd chip-8
    mkdir build
    cmake ..
    make
```

## :joystick: Run Emulator: 

### Windows
```bash
    cd chip-8
    cd build
    ./chip8 ../roms/Fishie.ch8
```

### Mac OS
```bash
    cd chip-8
    cd build
    ./chip8 ../roms/Fishie.ch8
```

### Linux 
```bash
    cd chip-8
    cd build
    ./chip8 ../roms/Fishie.ch8
```

* Fishie.ch8 is just an example rom and can be replaced with any of the roms found in the roms folder

## TODO
* Fix Documentation
