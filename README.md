# Library Utils (v1.0.0)

utils is a basic C library for safe float and integer input taking in CLI
applications. It prevents buffer overflows and program crashes caused by unexpected character types using scanf input. Has a crossplatform sleep function for cli output text.

## Features
* **Safe Integer Parsing:** Validates base-10 integer inputs, handling empty returns and invalid characters.
* **Safe Float Parsing:** Validates float parsing engine with user retry configurations.
* **Cross-Platform Sleep:** Clean, platform-independent sleep utilities for Linux, macOS, and Windows.

## How to Compile

To compile your project alongside this library, include `utils.c` and your main file using GCC:

```bash
gcc -Wall -Wextra -O2 main.c utils.c -o utils