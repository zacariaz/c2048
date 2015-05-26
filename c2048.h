#ifndef C2048_H
#define C2048_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// variable declarations:
extern const uint8_t* const board[4][4];
extern uint32_t seed;
extern const uint32_t* const score;
extern const int32_t* const moves;

// function declaration:

extern void NewGame();
extern uint8_t Move(uint8_t);
extern uint8_t SaveGame(const char*);
extern uint8_t LoadGame(const char*);

#endif
