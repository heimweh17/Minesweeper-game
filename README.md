Minesweeper — C++ SFML Project

A fully functional desktop version of the classic Minesweeper game built from scratch in C++ with SFML. This project was developed as part of a data structures and object-oriented programming course, focusing on clean software design, file I/O, game logic, and UI implementation.

It showcases fundamental computer science concepts — from recursion and file manipulation to event-driven programming and UI rendering — all implemented without external game engines.

Features

Classic Gameplay Mechanics

Left-click to reveal tiles, right-click to place flags.

Recursive reveal of empty regions with zero adjacent mines.

Real-Time Game Timer

Built-in timer that pauses and resumes accurately using std::chrono.

Debug and Developer Tools

Debug mode to instantly reveal all mine locations for testing.

Reset button to restart the game at any time.

Leaderboard System

Automatically records top completion times and player names.

Highlights the most recent entry (without altering saved data).

Robust Game Logic

Full win/lose detection.

Safe recursive reveal algorithm.

Grid initialization from tilemap files.

Tech Stack

Language: C++17

Graphics: SFML 2.6+

Core Concepts:

Object-Oriented Design (Tiles, Board, Leaderboard classes)

Recursion and search algorithms

File I/O (leaderboard.txt)

Event handling and UI rendering

Timer and pause logic with chrono

Project Highlights

This project goes beyond a simple game demo. It demonstrates:

Algorithmic Thinking – recursive reveal, adjacency calculation, and flood-fill logic.

System Design Skills – modular architecture separating logic, rendering, and data handling.

File Management – storing and parsing leaderboard data with structured read/write.

Attention to UX – pause, debug, and reset features to enhance gameplay.

Possible Future Improvements

Difficulty selection (Easy/Medium/Hard)

Custom grid and mine counts

Enhanced UI styling and animations

Cross-platform build setup with CMake presets

What I Learned

Building this project from the ground up taught me how to:

Design and implement a complete application in C++

Structure a codebase with maintainable class hierarchies

Work with a graphics library and handle real-time events

Manage persistent data with file I/O

Debug complex recursive logic and state-driven UI behavior
