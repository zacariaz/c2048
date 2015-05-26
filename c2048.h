#ifndef C2048_H
#define C2048_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// variable declarations:
extern uint8_t boardData[4][4];
extern uint8_t* const board[4][4][4];
extern uint32_t seed, score;
extern int32_t moves;

// function declaration:

//extern void Initialize();
extern void NewGame();
extern uint8_t NewTile();
extern uint8_t Move(uint8_t);
extern uint32_t P2(uint8_t);
extern uint8_t SaveGame(const char*);
extern uint8_t LoadGame(const char*);
#endif
