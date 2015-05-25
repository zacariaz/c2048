#include "main.h"

int main(int argc, char* argv[]) {
    Initialize();
    // char font[][][] used for pretty output
    const char font[5][18][12] = {
{"           ","         # ","      #### ","      #### ","      #  # ","      #### ","      #    ","      #### ","      #### ","      #### ","    # #### ","    #    # ","    # #### ","    # #### ","    # #  # ","    # #### ","    # #    ","    # #### "},
{"           ","         # ","         # ","         # ","      #  # ","      #    ","      #    ","         # ","      #  # ","      #  # ","    # #  # ","    #    # ","    #    # ","    #    # ","    # #  # ","    # #    ","    # #    ","    #    # "},
{"           ","         # ","      #### ","      #### ","      #### ","      #### ","      #### ","         # ","      #### ","      #### ","    # #  # ","    #    # ","    # #### ","    # #### ","    # #### ","    # #### ","    # #### ","    #    # "},
{"           ","         # ","      #    ","         # ","         # ","         # ","      #  # ","         # ","      #  # ","         # ","    # #  # ","    #    # ","    # #    ","    #    # ","    #    # ","    #    # ","    # #  # ","    #    # "},
{"           ","         # ","      #### ","      #### ","         # ","      #### ","      #### ","         # ","      #### ","         # ","    # #### ","    #    # ","    # #### ","    # #### ","    #    # ","    # #### ","    # #### ","    #    # "}};
    
    // initialize curses and all that.
    initscr();
    raw();
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    // if there is a game to load, load it, otherwise start new game.
    int ch = (LoadGame("save.bin")) ? ('n') : (0);
    // catch various keys untill quit.
    do {
        switch(ch) {
            case 'w':
            case 'W':
            case KEY_UP:
                Move(3);
                break;
            case 's':
            case 'S':
            case KEY_DOWN:
                Move(1);
                break;
            case 'a':
            case 'A':
            case KEY_LEFT:
                Move(0);
                break;
            case 'd':
            case 'D':
            case KEY_RIGHT:
                Move(2);
                break;
            case 'n':
            case 'N':
                SetSeed(time(0));
                NewGame();
        }
        
        // print the board.
        mvprintw(0, 0, "+-----------+-----------+-----------+-----------+\n"); 
        for(uint8_t y = 0; y < 4; y++) {
            for(uint8_t n = 0; n < 5; n++) {
                printw("|%s|%s|%s|%s|\n", font[n][GetTile(y, 0)], font[n][GetTile(y, 1)], font[n][GetTile(y, 2)], font[n][GetTile(y, 3)]);
            }
            printw("+-----------+-----------+-----------+-----------+\n");
        }
        printw("Score: %d\n", GetScore());
        printw("Moves: %d\n\n", GetMoves());
        printw("Press'n' for new game and 'q' for quits.\nUse the arrow keys or 'a, s, d, w' to play.\n");
        
        // get key;
        ch = getch();
    } while(ch != 'q' && ch != 'Q');
    // end curses.
    endwin();
    // save game.
    SaveGame("save.bin");
    // clean up.
    Finalize();
    return 0;
}
