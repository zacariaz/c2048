#include "c2048.h"

// variable definitions:
uint8_t boardData[4][4];
uint8_t* board[4][4][4];
uint32_t seed, score;
int32_t moves;
//function definitions:

void Initialize() {
    for(uint8_t y = 0; y < 4; y++)
        for(uint8_t x = 0; x < 4; x++)
            board[3][3-x][y] = board[2][3-y][3-x] = board[1][x][3-y] = board[0][y][x] = &boardData[y][x];
}

void NewGame() {
    // Initialize random number generator from seed.
    srand(seed);
    // Initialize/reset various variables.
    moves = score = 0;
    // Reset board.
    for(uint8_t y = 0; y < 4; y++)
        for(uint8_t x = 0; x < 4; x++)
            *board[0][y][x] = 0;
    // Call for the initial tiles.
    NewTile();
    NewTile();
}

uint8_t NewTile() {
    // Count empty squares.
    uint8_t count = 0;
    for(uint8_t y = 0; y < 4; y++) 
        for(uint8_t x = 0; x < 4; x++)
            if(!*board[0][y][x])
                count++;
    // If no empty squares, failure. Return 1, else continue.
    if(!count)
        return 1;
    // Initialize c and generate random 1 or 2, with 90% likelyhood of 1.
    uint8_t c = (rand() % 10)?(1):(2);
    // Generate a random number from 1 to count.
    count = (rand() % count) + 1;
    // Run through the board and decrement count for every empty tile.
    // when count is zero, whe're at the right spot and can assign c.
    for(uint8_t y = 0; y < 4 && count; y++) {
        for(uint8_t x = 0; x < 4 && count; x++) {
            if(!*board[0][y][x])
                count--;
            if(!count)
                *board[0][y][x] = c;
        }
    }
    // Return success.
    return 0;
}
// Move board[z] left. Return 1 if not possible.
uint8_t Move(uint8_t z) {
    // Initialize b to 1 / Assume failure.
    uint8_t b = 1;
    // Move all fields left where possible, due to empty squares.
    // do not otherwise change anything.
    for(uint8_t y = 0; y < 4; y++)
        for(uint8_t n = 0; n < 3; n++)
            for(uint8_t x = 3; x > 0; x--)
                if(!*board[z][y][x-1] && *board[z][y][x]) {
                    *board[z][y][x-1] = *board[z][y][x];
                    *board[z][y][x] = 0;
                    // if board has changes, success! Set b to 0.
                    b = 0;
                }
    // Row for Row.
    for(uint8_t y = 0; y < 4; y++) {
        // A whole lot of testing and moving about. Explanation difficult.
        if(*board[z][y][0] && *board[z][y][0] == *board[z][y][1]) {
            (*board[z][y][0])++;
            score += P2(*board[z][y][0]);
            if(*board[z][y][2] && *board[z][y][2] == *board[z][y][3]) {
                *board[z][y][1] = *board[z][y][2]+1;
                score += P2(*board[z][y][1]);
                *board[z][y][2] = *board[z][y][3] = 0;
            }
            else {
                *board[z][y][1] = *board[z][y][2];
                *board[z][y][2] = *board[z][y][3];
                *board[z][y][3] = 0;
            }
            // if board has changes, success! Set b to 0.
            b = 0;
        }
        else if(*board[z][y][1] && *board[z][y][1] == *board[z][y][2]) {
            (*board[z][y][1])++;
            *board[z][y][2] = *board[z][y][3];
            score += P2(*board[z][y][1]);
            *board[z][y][3] = 0;
            // if board has changes, success! Set b to 0.
            b = 0;
        }
        else if(*board[z][y][2] && *board[z][y][2] == *board[z][y][3]) {
            (*board[z][y][2])++;
            score += P2(*board[z][y][2]);
            *board[z][y][3] = 0;
            // if board has changes, success! Set b to 0.
            b = 0;
        }
    }
    // if b == 0, Success! Call NewTile and increment moves.
    if(!b) {
        NewTile();
        moves++;
    }
    // Return success or failure.
    return b;
}
// Set a specific seed. Should be done prior to calling NewGame().

uint32_t P2(uint8_t n) {
    return (n < 32) ? (1 << n) : (0);
}

// Save game
uint8_t SaveGame(const char* fn) {
    // Open file...
    FILE* fp = fopen(fn, "wb");
    // If file is open...
    if (!fp) {
        // Something went wrong. Return 1.
        return 1;
    }
    for(uint8_t y = 0; y < 4; y++)
        for(uint8_t x = 0; x < 4; x++)
            fwrite(board[0][y][x], sizeof(*board[0][y][x]), 1, fp);
    fwrite(&seed, sizeof(seed), 1, fp);
    fwrite(&moves, sizeof(moves), 1, fp);
    fwrite(&score, sizeof(score), 1, fp);
    fclose(fp);
    return 0;
}

// Load game
uint8_t LoadGame(const char* fn) {
    FILE* fp = fopen(fn, "rb");
    if(!fp)
        return 1;
    for(uint8_t y = 0; y < 4; y++)
        for(uint8_t x = 0; x < 4; x++)
            fread(board[0][y][x], sizeof(*board[0][y][x]), 1, fp);
    fread(&seed, sizeof(seed), 1, fp);
    fread(&moves, sizeof(moves), 1, fp);
    fread(&score, sizeof(score), 1, fp);
    fclose(fp);
    // Seed the random nummber generator.
    srand(seed);
    // NB: There must be a better way...
    // Call rand() the appropriate number of times to return to the original state.
    for(int32_t n = -moves; n < moves; n++)
        rand();
    return 0;
}
