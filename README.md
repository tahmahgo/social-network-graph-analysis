# Social Network Graph Analysis

A command-line application written in **C** that models an anonymized social network as an undirected graph. It loads friendship data from a text file and lets users view an account's friends or check whether two accounts are **directly** connected.

This was developed as a group project for **Data Structures and Algorithms (2023)** at De La Salle University.

## Features

- Loads a social network from a user-provided text file.
- Represents friendships using a dynamically allocated **adjacency matrix**.
- Lists a user's friends and displays their total number of friends.
- Checks whether two user IDs have a **direct friendship**.
- Validates whether an entered user ID is within the loaded network's range.
- Displays elapsed time for the interactive operations (see [Limitations](#limitations)).

## Technologies and concepts

- **Language:** C
- **Libraries:** Standard C library and POSIX `sys/time.h`
- **Data structure:** Two-dimensional adjacency matrix
- **Concepts:** File I/O, dynamic memory allocation, arrays, graph representation, and time/space complexity

## How it works

Each user is represented by an integer ID from `0` to `n - 1`. The program stores friendships in a matrix called `Records`:

- `Records[a][b] = 1` means users `a` and `b` are direct friends.
- `Records[a][b] = 0` means there is no direct friendship recorded between them.
- Because friendships are undirected, the program sets **both** `Records[a][b]` and `Records[b][a]` to `1` when loading an edge.

### Operations and complexity

| Operation | Implementation | Time complexity |
| --- | --- | --- |
| Direct friendship check | Read `Records[a][b]` | **O(1)** |
| Retrieve a user's friends | Scan one full row of the matrix | **O(n)** |
| Initialize the adjacency matrix | Set every cell to zero | **O(n²)** |

The adjacency matrix uses **O(n²) space**, even when the network contains relatively few edges. The program allocates each row dynamically and frees the allocated memory before exiting normally.

## Repository structure

```text
social-network-graph-analysis/
├── v5.c
├── data/
│   └── Caltech36.txt
└── README.md
```

The structure above uses the original source filename from the project archive. You can rename `v5.c` to `main.c` if you prefer; update the compilation command accordingly.

## Build and run

### Requirements

- A C compiler, such as **GCC**
- A POSIX-compatible environment with `sys/time.h` (for example, Linux, macOS, or WSL on Windows)
- A friendship dataset in the expected text format

From the repository root, compile the source:

```bash
gcc -std=c11 -Wall -Wextra v5.c -o social-graph
```

Run it:

```bash
./social-graph
```

When prompted, enter the path to the dataset relative to the directory where you ran the program:

```text
Enter file name: data/Caltech36.txt
Data loaded!

MAIN MENU
[1] View friends list
[2] Check connection
[3] Exit
```

Choose **1** to list a user's friends, **2** to check a direct connection between two IDs, or **3** to exit. The menu repeats after each successful operation.

## Dataset format

The program expects a plain-text file with the following format:

```text
6 5
0 1
0 3
1 4
2 3
3 5
```

- The first line contains the **number of users** (`n`) and **number of friendships** (`e`).
- Each remaining line contains two user IDs that share a friendship.
- IDs must be within the range `0` through `n - 1`.

The original course materials use anonymized Facebook university-network datasets associated with the research below. If publishing a sample dataset in this repository, check its redistribution terms and provide appropriate attribution.

**Dataset reference:** Traud, A. L., Mucha, P. J., & Porter, M. A. (2012). *Social structure of Facebook networks*. *Physica A: Statistical Mechanics and its Applications, 391*(16), 4165–4180.

## Limitations

- **Direct connections only:** The `checkConnection()` function tests whether two users share an edge. It does not search for indirect paths through mutual friends (no BFS or DFS is implemented).
- **Timing includes user input:** The elapsed-time display measures the whole interactive function, including time spent entering IDs. It should **not** be interpreted as a reliable algorithm benchmark.
- **Input handling is basic:** Out-of-range user IDs are handled, but nonnumeric input, malformed files, and memory-allocation failures are not robustly handled.
- **Memory use grows quadratically:** An adjacency list would be more space-efficient for sparse graphs.

## Possible improvements

- Implement BFS to discover indirect paths and optionally return the shortest connection path.
- Separate user input from timing measurements for more meaningful performance comparisons.
- Validate dataset headers, file contents, and allocation results more thoroughly.
- Compare adjacency-matrix performance with an adjacency-list implementation.

## Project scope

This repository is an educational implementation of graph representation and lookup operations, **not** a production social-network service. It is intended to demonstrate foundational C programming and data-structure concepts.
