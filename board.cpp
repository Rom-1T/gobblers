#include "piece.h"
#include "cell.h"
#include "playerEnum.h"
#include "config.h"
#include "statusEnum.h"
#include <iostream>
#include "board.h"
#include <array>

Board::Board(){
    Cell state [DIMENSIONS][DIMENSIONS];
    for (int i=0; i<DIMENSIONS; i++){
        for (int j=0; j<DIMENSIONS; j++){
            state[i][j]=Cell();
        }
    }
    int p1Pieces[NB_SIZE];
    int p2Pieces[NB_SIZE];
}

Board::Board(const Board& other){
    for (int i=0;i<DIMENSIONS;i++){
        for (int j=0;j<DIMENSIONS;j++)
            this->state[i][j] = other.state[i][j];
    }
    std::copy(std::begin(other.p1Pieces), std::end(other.p1Pieces), std::begin(this->p1Pieces));
    std::copy(std::begin(other.p2Pieces), std::end(other.p2Pieces), std::begin(this->p2Pieces));
}

Board::~Board(){
    delete(state);
    delete(p1Pieces);
    delete(p2Pieces);
}

Player Board::nextPlayer(Player currentPlayer) const {
    if (currentPlayer == PLAYER_1) {
        return PLAYER_2;
    }
    if (currentPlayer == PLAYER_2) {
        return PLAYER_1;
    }
    else{
        return NO_PLAYER;
    }
}

Player Board::getPlaceHolder(int line, int column){
    Piece piece = state[line][column].peek();
    return piece.getOwner();
}

Size Board::getPieceSize(int line, int column){
    Piece piece = state[line][column].peek();
    return piece.getSize();
}


int Board::getNbPiecesInHouse(Player checkedPlayer, Size pieceSize){
    if (checkedPlayer == PLAYER_1) {
        return this->p1Pieces[pieceSize];
    }
    if (checkedPlayer == PLAYER_2) {
        return this->p2Pieces[pieceSize];
    }
    else{
        return -1;
    }
}


StatusEnum Board::placePiece(Player currentPlayer, Size pieceSize, int line, int column){
    if (this->getNbPiecesInHouse(currentPlayer,pieceSize) <= 0){
        return INVALID_SOURCE;
    }
    Piece piece = Piece(currentPlayer, pieceSize);
    if (!this->state[line][column].canPush(piece)){
        return INVALID_TARGET;
    }
    if (((currentPlayer!=PLAYER_1)&&(currentPlayer!=PLAYER_2))||(line>DIMENSIONS)||(column>DIMENSIONS)){
        return INVALID_ENTRY;
    }
    else{
        return OK;
    }
}

StatusEnum Board::movePiece(int sourceLine, int sourceColumn, int targetLine, int targetColumn){
    if ((sourceLine>DIMENSIONS)||(sourceColumn>DIMENSIONS)||(targetLine>DIMENSIONS)||(targetColumn>DIMENSIONS)){
        return INVALID_ENTRY;
    }
    if (this->getPieceSize(sourceLine,sourceColumn)==NONE){
        return INVALID_SOURCE;
    }
    Piece sourcePiece = this->state[sourceLine][sourceColumn].peek();
    Cell targetCell = this->state[targetLine][targetColumn];
    if (!targetCell.canPush(sourcePiece)){
        return INVALID_TARGET;
    }
    else {
        return OK;
    }
}


std:: array<std::array<Cell,DIMENSIONS>,DIMENSIONS*2 + 2> Board::liste_Cell_To_Verify() {
    std:: array<std::array<Cell,DIMENSIONS>,DIMENSIONS*2 + 2> liste_Cell;
     for (int i=0; i<DIMENSIONS; i++){
         for (int j=0; j<DIMENSIONS; j++){
             liste_Cell[i][j] = this->state[i][j]; //Lignes
             liste_Cell[i+DIMENSIONS][j] = this->state[j][i]; //Colonnes
             liste_Cell[2*DIMENSIONS][j] = this->state[i][i]; // Diag 1
             liste_Cell[2*DIMENSIONS + 1 ][j] = this->state[i][DIMENSIONS - 1 -i]; //Diag 2
         }
     }
     return liste_Cell;
}

Player Board::getWinner(){
    std:: array<std::array<Cell,DIMENSIONS>,DIMENSIONS*2 + 2> liste_Cell = this->liste_Cell_To_Verify();
    for (int i = 0; i<2*DIMENSIONS + 2; i++) {
        bool same_player = true;
        for (int j=0; j<DIMENSIONS - 1; j++) {
            if (liste_Cell[i][j].peek().getOwner() != liste_Cell[i][j+1].peek().getOwner() || liste_Cell[i][j].peek().getOwner() == NO_PLAYER) {
                same_player = false;
                break; //Les deux pièces qui se suivent ne sont pas posséder par le même joueur
            }
        }
        if (same_player) {
            return liste_Cell[i][0].peek().getOwner();
        }
    }
    return NO_PLAYER
}



