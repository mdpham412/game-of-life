# Free-est Game of Life

## What is this?

This is my personal implementation of the popular Conway's Game of Life with as many customizable options as possible.

## Why did I make this?

I thought that this project would be interesting for some and that it would be a good project to help me brush up on my C++ skills.

## What features does this have

This is a Game of Life simulator that features:

- customizable graphics
- simulation configuration

## Setup and compilation

> [!NOTE]  
> This project only supports Windows and the GNU C++ compiler as that is my current setup, other configurations may work but are not guaranteed

1. Clone the repository

```bash
git clone https://github.com/mdpham412/game-of-life.git
```

2. Generate build files
   - With the debug console window:

   ```bash
   cmake -B build -G Ninja -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++
   ```

   - Without the debug console window:

   ```bash
   cmake -B build -G Ninja -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ -D HIDE_CONSOLE=ON
   ```

3. Compile

```bash
cmake --build build
```
