# Arbitrary Precision Calculator (APC)

A robust Command Line Calculator built in C that performs arithmetic operations on numbers of practically unlimited length.

## Features
- **Arbitrary Precision:** Overcomes the standard 64-bit integer limits of C by utilizing dynamically allocated Doubly Linked Lists to store and manipulate massive numbers.
- **Operations Supported:**
  - Addition (`+`)
  - Subtraction (`-`)
  - Multiplication (`x`)
  - Division (`/`)
- **Memory Safe:** Strict pointer management and automated cleanup routines ensure zero memory leaks or double-frees.
- **CLI Interface:** Fast, non-blocking, scriptable Command Line Argument interface with a formatted ASCII dashboard output.

## Installation & Build

This project utilizes an industry-standard `Makefile` for automated, clean compilation.

1. Clone the repository:
   ```bash
   git clone <your-repo-url>
   cd APC
   ```
2. Build the project using `make` (or `mingw32-make` on some Windows setups):
   ```bash
   make
   ```
   OR
   ```bash
   make -f MakeFile
   ```

## Usage

Run the compiled executable `calc.exe` from your terminal by passing the operands and operator as arguments.

**Syntax:**
```bash
./calc.exe <number1> <operator> <number2>
```
*(Note: If you are using PowerShell on Windows, prefix the command with `.\`)*

**Examples:**
```bash
# Massive Addition
.\calc.exe 12345678901234567890 + 98765432109876543210

# Subtraction
.\calc.exe 100 - 999

# Multiplication (Ensure you use a lowercase 'x')
.\calc.exe 999 x 999

# Division
.\calc.exe 1000 / 3
```

## Output:
![APC Demo](Output1.png)
![APC Demo2](Output2.png)
![APC Demo3](Output3.png)

## Architecture
- **Data Structure:** A custom Doubly Linked List (`Dlist`) where each node is heavily optimized to hold a single decimal digit (`char`).
- **Routing Module:** A centralized controller in `main.c` orchestrates argument parsing, mathematical sign routing, and error validation before dispatching to the core Arithmetic Logic Unit.

## Author
**Akshay Mittha**

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
