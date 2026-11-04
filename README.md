# Tic-Tac-Toe (C Edition)

A fully playable, unbeatable Tic-Tac-Toe game written in C.

This project is a direct translation of an Object-Oriented Python implementation into procedural C. It serves as a demonstration of how to build the "Object-Oriented" pattern using C structs, explicit pointer passing (`self`), and file-scoped private functions, while implementing a recursive Minimax AI engine.

## Features

- **Unbeatable AI**: Uses the Minimax algorithm with alternating maximizing/minimizing branches to guarantee at least a draw.
- **Zero Allocation**: The game board and state are stored entirely on the stack. No `malloc` or `free` required.
- **Stateful Mutation**: Demonstrates mutating struct state by passing pointers (`TicTacToe *self`) instead of passing by value.
- **Safe Terminal I/O**: Handles invalid inputs (like typing letters instead of numbers) gracefully using `scanf` and buffer clearing.

## How to Build and Run

You just need a standard C compiler (like `gcc`). Open your terminal in the project directory and run:

1. Compile the code:
   ```sh
   gcc main.c -o ttt
