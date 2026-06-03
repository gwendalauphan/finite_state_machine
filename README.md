# Finite State Machine

An interactive command-line program written in C for exploring **formal language theory** concepts. It lets you define alphabets, manipulate words, build finite state automata (AEF — *Automate à États Finis*), and run various operations on them — all through a menu-driven interface.

### Features

| Mode | Description |
|------|-------------|
| **Mode 1 — Alphabet** | Define an alphabet and a word, then check membership, compute word power, concatenate, mirror, and more. |
| **Mode 2 — AEF** | Build or load a finite automaton (manual input or from file), check if a word is recognized, verify/make the automaton complete, add/remove letters, states and rules, save to file. |
| **Mode 3 — Regular Expressions** | Placeholder — not yet implemented. |

---

## How to Run

### Prerequisites

- **CMake** ≥ 3.16
- **GCC** (or any C99-compatible compiler)

```bash
# Install CMake on Ubuntu/Debian
sudo apt update
sudo apt install cmake gcc
```

### Build

```bash
cd finite_state_machine
cmake .
make
```

### Run

```bash
./automate
```

Or use the CMake custom target:

```bash
make run
```

> **Note:** The build enables AddressSanitizer and UndefinedBehaviorSanitizer (`-fsanitize=address,undefined`) in debug mode to help catch memory errors at runtime.

---

## How to Test

The project uses **CTest**. After building:

```bash
ctest
```

Or equivalently:

```bash
make test
```

This runs the `test_basic` target, which verifies the build setup is functional.

---

## How to Clean

Remove compiled objects and executables:

```bash
make clean
```

For a full reset (remove all CMake-generated files):

```bash
rm -rf CMakeCache.txt CMakeFiles/ cmake_install.cmake Makefile CTestTestfile.cmake Testing/ automate test_basic
```

Then re-generate with `cmake .` and `make`.

---

## How Does It Work

### Project Structure

```
src/
├── main.c              # Entry point — mode selection menu
├── part_1.c            # Mode 1: Alphabet & word manipulation
├── part_2.c            # Mode 2: Finite automaton (AEF) manipulation
├── part_3.c            # Mode 3: Regular expressions (stub)
├── settings.c          # Global settings (octet display)
├── test_basic.c        # Basic CTest test
└── functions/
    ├── algo.c          # Algorithms (word power, make-complete)
    ├── test.c          # Verification (membership, completeness, word recognition)
    ├── modif.c         # AEF modification (add/remove letters, states, rules)
    ├── input.c         # User input handling
    ├── readFile.c      # Load an AEF from a file
    ├── writeFile.c     # Save an AEF to a file
    ├── ht.c            # Hash table (state → transitions dictionary)
    ├── demo.c          # Dictionary builder for AEF
    ├── librairies.c    # Display helpers
    └── utils_split.c   # String splitting utilities

headers/                # Header files mirroring the src/ layout
data/                   # Input/output data files
```

### Data Structures

- **`Alpha_Mot`** — Holds an alphabet (array of strings) and a word, used in Mode 1.
- **`AEF`** — Represents a finite automaton with:
  - An alphabet
  - States (all / initial / final)
  - Transition rules (source state, symbol, destination state)
  - A hash table mapping each state to its outgoing transitions for efficient lookup

### Mode 1 — Alphabet Operations

After defining an alphabet and a word, you can:
1. Check if the word belongs to the alphabet
2. Compute a power of the word (repeat it *n* times)
3. Check if the word is empty
4. Concatenate another word
5. Compute the mirror (reverse) of the word
6. Check if the word is finite
7. Change the word

### Mode 2 — AEF Operations

First, create an AEF by **manual input** or by **loading from a file** (`data/fileToRead.txt`). Then:

1. Check if a word is recognized by the AEF
2. Verify if the automaton is complete
3. Make the automaton complete (adds a sink state with missing transitions)
4–11. *(Not yet implemented)* — Determinism check, language extraction, epsilon removal, AEF operations (complement, mirror, product, concatenation), equivalence, minimization
12. Modify the AEF (add/remove letters, states, rules)
13. Save the AEF to a file

### AEF File Format

The file `data/fileToRead.txt` uses a 6-line format:

```
nombre_octet 2
alphabet aa-bb-cc
regles 11,aa,22-22,bb,33-11,cc,33-33,cc,22
etats 11-22-33
etat_initiaux 11
etat_finaux 33
```

| Line | Field | Format |
|------|-------|--------|
| 1 | Octet size | Number of bytes per symbol/state |
| 2 | Alphabet | Letters separated by `-` |
| 3 | Rules | Transitions as `src,symbol,dest` separated by `-` |
| 4 | States | All states separated by `-` |
| 5 | Initial states | Separated by `-` |
| 6 | Final states | Separated by `-` |

### Completeness Algorithm

The `RendreComplet` function adds a **sink state** (`&`) and creates missing transitions so every state has exactly one outgoing transition per alphabet symbol. It uses the hash table dictionary for efficient lookups.

---

## References & Others

- [Finite Automaton — Wikipedia](https://en.wikipedia.org/wiki/Finite-state_machine)
- [Deterministic Finite Automaton (DFA)](https://en.wikipedia.org/wiki/Deterministic_finite_automaton)
- [Nondeterministic Finite Automaton (NFA)](https://en.wikipedia.org/wiki/Nondeterministic_finite_automaton)
- [Formal Language — Wikipedia](https://en.wikipedia.org/wiki/Formal_language)
