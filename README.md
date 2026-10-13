# 🖥️ C/C++ Algorithms & Games Portfolio

A portfolio of algorithms, data structures and games implemented in C and C++.

## 🧮 Stack-Based Processor Emulator

**[Source code](./Low_Level_Algorithms/StackProcessor.cpp)**

An emulator for a custom stack-based processor. A program is a sequence of single-character instructions executed by an instruction pointer, operating on a stack of character lists. Numbers are stored as digit lists, so arithmetic is not limited to the range of built-in integer types.

### Instruction set

| Category | Instructions | Description |
|---|---|---|
| Stack manipulation | `'` `,` `:` `;` `@` | Push empty list, pop, duplicate, swap, copy the n-th element |
| Arithmetic | `+` `-` `^` | Addition, negation, absolute value |
| Comparison & logic | `<` `=` `!` | Less-than, equality, logical NOT |
| Control flow | `~` `?` | Push instruction pointer, conditional jump |
| List & character ops | `$` `#` `[` `]` | Split first character, concatenate lists, character → ASCII code, ASCII code → character |
| I/O | `.` `>` `&` | Read a character, print a character, print the whole stack |
| Any other character | | Prepended to the list on top of the stack |

### Implementation highlights

- **Arbitrary-precision signed integers:** numbers are stored as digit lists (least significant digit first, sign at the end), with addition and comparison implemented digit by digit.
- **No STL and no arrays:** apart from the program and input buffers, all data structures are hand-written and pointer-based.
- **Recursion instead of loops:** the specification allowed at most one loop, so all other iteration is implemented recursively.
- Handles programs and inputs of up to 20,000 characters each.

### How to run

```bash
g++ -O2 -o stack_processor Low_Level_Algorithms/StackProcessor.cpp
./stack_processor < input.txt
```

The first line of the input is the program; the second line is the data passed to its standard input. Because of deep recursion, larger programs may need a bigger stack (e.g. `ulimit -s unlimited` on Linux, or *Stack Reserve Size* in Visual Studio).

## ⚙️ Other Algorithms & Data Structures

* **[Dijkstra's Algorithm](./Low_Level_Algorithms/DijkstraBoard.cpp):** A custom implementation of Dijkstra's shortest-path algorithm, extended with waiting times on routes.
* **[Sparse Table](./Low_Level_Algorithms/SparseTable.cpp):** A dynamic sparse table supporting lookups and updates in **O(log n)** time.
* **[Market Lamps](./Low_Level_Algorithms/MarketLamps.cpp):** An algorithm that visualises stock price data using a "market lamps" representation.

## 🎮 Console Games

* **[Frogger](./Console_Games/Frogger.cpp):** A console adaptation of the classic arcade game, in which the player guides a frog safely across a hazardous river.
* **[BlackBox](./Console_Games/BlackBox.cpp):** An implementation of the classic deductive logic puzzle, inspired by the [original BlackBox game](https://apps.microsoft.com/detail/9wzdncrfk15d?hl=pl-PL&gl=PL).

## 🐍 SDL Snake

A modern version of the classic Snake game built with the **SDL library**. Movement speed is frame-rate independent (delta time), so gameplay is consistent regardless of hardware performance.

### 🚀 How to Run

Open [`snake.sln`](./Snake_SDL/snake.sln) in Visual Studio and build the project.
