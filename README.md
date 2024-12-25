tictactoe_remote

Overview

This is a remote Tic-Tac-Toe game implemented in C++ using sockets for communication. It enables two players to compete against each other, with one player acting as the server and the other as the client. The game logic, communication, and board management allow two computers to play the game over a network.

Features

Real-time multiplayer gameplay: Two players can play the game on separate computers.

Terminal-based interface: The game runs entirely on the terminal without the need for a GUI.

Socket-based communication: Utilizes Winsock2 for network communication between server and client.

Robust game logic: Implements all necessary rules for Tic-Tac-Toe, including win, loss, and draw conditions.

Smart memory management: Uses modern C++ practices like std::shared_ptr for dynamic memory management.

Prerequisites

A Windows environment with support for Winsock2.

A C++ compiler (e.g., MSVC or MinGW).

Both computers must be on the same network or configured to allow communication over the specified port.

How It Works

The server listens on a specified port for a connection from the client.

The client connects to the server using the same port.

Players take turns entering their moves.

The server and client communicate the game state using socket communication.

The game ends when a player wins or the board is filled (draw).

Project Structure

|-- include/
|   |-- board.h        // Contains the `Board` class for managing game logic.
|   |-- client.h       // Defines the `client` class for client-side network handling.
|   |-- server.h       // Defines the `server` class for server-side network handling.
|
|-- src/
|   |-- board.cpp      // Implementation of the `Board` class.
|   |-- client.cpp     // Implementation of the `client` class.
|   |-- server.cpp     // Implementation of the `server` class.
|   |-- main_client.cpp // Entry point for the client.
|   |-- main_server.cpp // Entry point for the server.
|
|-- README.md          // Project documentation.
|-- Makefile           // Build instructions.

How to Build and Run

Server

Navigate to the src directory.

Compile the server:

cmake -S . -B build

cmake --build build

Run the server in the /build/Debug/:

./server.exe

Client

Navigate to the src directory.

Compile the client in the /build/Debug/:

cmake -S . -B build

cmake --build build

Run the client:

./client.exe

Gameplay

The server starts and waits for the client to connect.

The client connects to the server.

Players take turns entering their moves.

Input should be a number between 1 and 9 representing the board position.

Invalid input will prompt for re-entry.

The board state updates and displays on both terminals after every move.

The game ends when a player wins or the board is filled.


