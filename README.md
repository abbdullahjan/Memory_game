# Memory Game

This is a terminal-based memory game written in C. The game consists of 36 cards, including two jokers and pairs of uppercase and lowercase alphabets.

## How to Play

- The game is played by two players in turns.
- The objective is to score points by flipping cards and finding pairs.
- **Points system**:
  - Matching a pair of letters (e.g., 'A' and 'a'): **1 point**.
  - Flipping a joker: **1 point**.
- Special rules for jokers:
  - When a joker is flipped, all turned cards in the other player's turn are flipped back.
  - Players must find the flipped joker's pair for additional points.

## Features

- Two-player gameplay.
- 36 cards: 2 jokers and alphabet pairs.
- Scoring system for both pairs and jokers.
- Terminal-based interface for easy interaction.

## Compilation and Execution

### Compilation
Compile the game using GCC:
```bash
gcc -o memory-game memory-game.c
