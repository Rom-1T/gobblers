#ifndef CONFIG_H
#define CONFIG_H

//Set this to false if ANSI color codes are not working in your terminal
const bool USE_COLORS = true;

//Board dimensions
const int DIMENSIONS = 3;
//Number of players
const int NB_PLAYERS = 2;
//Number of different piece sizes
const int NB_SIZE = 3;
//Number of pieces of each size, for each player
const int NB_INITIAL_PIECES = 2;

const char SMALLP1 = 'x';
const char MEDIUMP1 = 'X';
const char LARGEP1 = '#';
const char SMALLP2 = '.';
const char MEDIUMP2 = 'o';
const char LARGEP2 = 'O';

const char PIECES_P1[3] = {SMALLP1,MEDIUMP1,LARGEP1};
const char PIECES_P2[3] = {SMALLP2,MEDIUMP2,LARGEP2};

#endif // CONFIG_H
