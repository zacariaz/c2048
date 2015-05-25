#ifndef C2048_H
#define C2048_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// variable declarations:
extern uint8_t* board[4][4][4];
extern uint32_t seed, moves, score;

// function declaration:

extern void Initialize();
extern void Finalize();
extern void NewGame();
extern uint8_t NewTile();
extern uint8_t Move(uint8_t);
extern void SetSeed(uint32_t);
extern int8_t GetTile(uint8_t, uint8_t);
extern uint32_t GetScore();
extern uint32_t GetMoves();
extern uint32_t P2(uint8_t);
extern uint8_t SaveGame(char*);
extern uint8_t LoadGame(char*);
#endif
