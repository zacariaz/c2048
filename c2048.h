#ifndef C2048_H
#define C2048_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// variable declarations:
const uint8_t* const board[4][4];
uint32_t seed;
const uint32_t* const score;
const int32_t* const moves;

// function declaration:

void NewGame();
uint8_t Move(uint8_t);
uint8_t SaveGame(const char*);
uint8_t LoadGame(const char*);

#endif
