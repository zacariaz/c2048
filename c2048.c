#include "c2048.h"

// variable definitions:
uint8_t boardData[4][4];
uint8_t* const board[4][4][4] = {{
{&boardData[0][0], &boardData[0][1], &boardData[0][2], &boardData[0][3]},
{&boardData[1][0], &boardData[1][1], &boardData[1][2], &boardData[1][3]},
{&boardData[2][0], &boardData[2][1], &boardData[2][2], &boardData[2][3]},
{&boardData[3][0], &boardData[3][1], &boardData[3][2], &boardData[3][3]}
},{
{&boardData[3][0], &boardData[2][0], &boardData[1][0], &boardData[0][0]},
{&boardData[3][1], &boardData[2][1], &boardData[1][1], &boardData[0][1]},
{&boardData[3][2], &boardData[2][2], &boardData[1][2], &boardData[0][2]},
{&boardData[3][3], &boardData[2][3], &boardData[1][3], &boardData[0][3]}
},{
{&boardData[3][3], &boardData[3][2], &boardData[3][1], &boardData[3][0]},
{&boardData[2][3], &boardData[2][2], &boardData[2][1], &boardData[2][0]},
{&boardData[1][3], &boardData[1][2], &boardData[1][1], &boardData[1][0]},
{&boardData[0][3], &boardData[0][2], &boardData[0][1], &boardData[0][0]}
},{
{&boardData[0][3], &boardData[1][3], &boardData[2][3], &boardData[3][3]},
{&boardData[0][2], &boardData[1][2], &boardData[2][2], &boardData[3][2]},
{&boardData[0][1], &boardData[1][1], &boardData[2][1], &boardData[3][1]},
{&boardData[0][0], &boardData[1][0], &boardData[2][0], &boardData[3][0]}
}};
uint32_t seed, score;
int32_t moves;

//function definitions:

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
    // Count empty squares and save coordinates.
    uint8_t count = 0;
    struct {
        uint8_t y, x;
    } p[16];
    for(uint8_t y = 0; y < 4; y++) 
        for(uint8_t x = 0; x < 4; x++)
            if(!*board[0][y][x]) {
                p[count].x = x;
                p[count].y = y;
                count++;
            }
    // If no empty squares, failure. Return 1, else continue.
    if(!count)
        return 1;
    // Initialize c and generate random 1 or 2, with 90% likelyhood of 1.
    uint8_t c = (rand() % 10)?(1):(2);
    // Generate a random number from 0 to count-1.
    count = rand() % count;
    // Assign 'c' to a random empty tile.
    *board[0][p[count].y][p[count].x] = c;    
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
            ++*board[z][y][0];
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
            ++*board[z][y][1];
            *board[z][y][2] = *board[z][y][3];
            score += P2(*board[z][y][1]);
            *board[z][y][3] = 0;
            // if board has changes, success! Set b to 0.
            b = 0;
        }
        else if(*board[z][y][2] && *board[z][y][2] == *board[z][y][3]) {
            ++*board[z][y][2];
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
// Get 2^n - No need to involve math.h, allthough the safeguard may be overdoing it a bit.
uint32_t P2(uint8_t n) {
    return (n < 32) ? (1 << n) : (0);
}

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
