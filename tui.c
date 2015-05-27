#include "tui.h"
#include "c2048.h"

static const char font[5][18][12] = {
{"         ","        #","     ####","     ####","     #  #","     ####","     #   ","     ####","     ####","     ####","   # ####","   #    #","   # ####","   # ####","   # #  #","   # ####","   # #   ","   # ####"},
{"         ","        #","        #","        #","     #  #","     #   ","     #   ","        #","     #  #","     #  #","   # #  #","   #    #","   #    #","   #    #","   # #  #","   # #   ","   # #   ","   #    #"},
{"         ","        #","     ####","     ####","     ####","     ####","     ####","        #","     ####","     ####","   # #  #","   #    #","   # ####","   # ####","   # ####","   # ####","   # ####","   #    #"},
{"         ","        #","     #   ","        #","        #","        #","     #  #","        #","     #  #","        #","   # #  #","   #    #","   # #   ","   #    #","   #    #","   #    #","   # #  #","   #    #"},
{"         ","        #","     ####","     ####","        #","     ####","     ####","        #","     ####","        #","   # ####","   #    #","   # ####","   # ####","   #    #","   # ####","   # ####","   #    #"}};

static const char message[24][33] = {
"*** C2048 - fork by Zacariaz ***",
"*                              *",
"*  github.com/zacariaz/c2048/  *",
"*                              *",
"*********** Controls ***********",
"Arrow keys                      ",
"w, a, s, d                      ",
"n               New game.       ",
"q               Quit.           ",
"                                ",
"                                ",
"                                ",
"********** High Score **********",
"Score      Best Tile      Moves ",
"3,932,156  131,072(2^17)  13,138",
"                                ",
"                                ",
"                                ",
"                                ",
"                                ",
"********* Current Game *********",
"Best Tile                       ",
"Moves                           ",
"Score                           ",
};

void Run() {
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
                if(!seed) seed = time(0);
                NewGame();
        }
        // print board
        for(uint8_t y = 0; y < 4; y++) {
            for(uint8_t n = 0; n < 5; n++) {
                if((n  == 4 || n == 0) && !(y == 0 && n == 0) && !(y == 3 && n == 4)) mvprintw(5*y+y+n, 0, "%s | %s | %s | %s", font[n][*board[y][0]], font[n][*board[y][1]], font[n][*board[y][2]], font[n][*board[y][3]]);
                else mvprintw(5*y+y+n, 0, "%s   %s   %s   %s", font[n][*board[y][0]], font[n][*board[y][1]], font[n][*board[y][2]], font[n][*board[y][3]]);
            }
            if(y != 3) mvprintw(5*y+y+5, 0, "        --+--       --+--       --+--        ");
        }
         // print message[], *score and *moves
        for(uint8_t y = 0; y < 24; y++ )
            mvprintw(y, 48, "%s", message[y]);
        mvprintw(22, 64, "%16d", *moves);
        mvprintw(23, 64, "%16d", *score);
        
        // get key;
        ch = getch();
    } while(ch != 'q' && ch != 'Q');
    // end curses.
    endwin();
    // save the game before exit.
    SaveGame("save.bin");
}
