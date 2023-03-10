#include "piece.h"
#include "cell.h"
#include "playerEnum.h"
#include "config.h"
#include "statusEnum.h"
#include "board.h"
#include <string>

using namespace std;

Board::Board(){
    for (int i=0; i<DIMENSIONS; i++){
        for (int j=0; j<DIMENSIONS; j++){
            this->state[i][j]=Cell();
        }
    }
    for (int i = 0; i<NB_SIZE; i++) {
        this->p1Pieces[i] = NB_INITIAL_PIECES;
        this->p2Pieces[i] = NB_INITIAL_PIECES;
    }
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
    //    delete(state);
    //    delete(p1Pieces);
    //    delete(p2Pieces);
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
        return this->p1Pieces[pieceSize-1];
    }
    if (checkedPlayer == PLAYER_2) {
        return this->p2Pieces[pieceSize-1];
    }
    return -1;
}


StatusEnum Board::placePiece(Player currentPlayer, Size pieceSize, int line, int column){
    if (this->getNbPiecesInHouse(currentPlayer,pieceSize) == 0){
        return INVALID_SOURCE;
    }
    Piece piece = Piece(currentPlayer, pieceSize);
    if (!this->state[line][column].canPush(piece)){
        return INVALID_TARGET;
    }
    if (((currentPlayer!=PLAYER_1)&&(currentPlayer!=PLAYER_2))||(line>=DIMENSIONS)||(column>=DIMENSIONS)){
        return INVALID_ENTRY;
    }
    else{
        piece = Piece(currentPlayer,pieceSize);
        if (currentPlayer == PLAYER_1){
            this->p1Pieces[pieceSize-1] --;
            this->state[line][column].push(piece);
        }
        else {
            this->p2Pieces[pieceSize-1] --;
            this->state[line][column].push(piece);
        }
        return OK;
    }
}

StatusEnum Board::movePiece(int sourceLine, int sourceColumn, int targetLine, int targetColumn){
    if ((sourceLine>=DIMENSIONS)||(sourceColumn>=DIMENSIONS)||(targetLine>=DIMENSIONS)||(targetColumn>=DIMENSIONS)){
        return INVALID_ENTRY;
    }
    if (this->getPieceSize(sourceLine,sourceColumn)==NONE){
        return INVALID_SOURCE;
    }
    Piece sourcePiece = this->state[sourceLine][sourceColumn].peek();
    Cell targetCell = this->state[targetLine][targetColumn];
    if (this->state[sourceLine][sourceColumn].canPop() == false){
        return INVALID_SOURCE;
    }
    if (!targetCell.canPush(sourcePiece)){
        return INVALID_TARGET;
    }
    else {
        Piece sourcePiece = this->state[sourceLine][sourceColumn].pop();
        this->state[targetLine][targetColumn].push(sourcePiece);
        return OK;
    }
}

Player Board::getWinner() {
    //LIGNES
    for (int i=0; i<DIMENSIONS; i++) {
        Player player_0 = this->state[i][0].peek().getOwner();
        if (player_0 != NO_PLAYER) {
            bool same_player = true;
            for (int j=1; j<DIMENSIONS; j++){
                Player player_j = this->state[i][j].peek().getOwner();
                if (player_0 != player_j) {
                    same_player = false;
                }
            }
            if (same_player) {
                return player_0;
            }
        }
        //COLONNES
        for (int i=0; i<DIMENSIONS; i++) {
            Player player_0 = this->state[0][i].peek().getOwner();
            if (player_0 != NO_PLAYER) {
                bool same_player = true;
                for (int j=1; j<DIMENSIONS; j++){
                    Player player_j = this->state[j][i].peek().getOwner();
                    if (player_0 != player_j) {
                        same_player = false;
                    }
                }
                if (same_player) {
                    return player_0;
                }
            }
        }
        //DIAG 1
        player_0 = this->state[0][0].peek().getOwner();
        if (player_0 != NO_PLAYER) {
            bool same_player = true;
            for (int j=1; j<DIMENSIONS; j++){
                Player player_j = this->state[j][j].peek().getOwner();
                if (player_0 != player_j) {
                    same_player = false;
                }
            }
            if (same_player) {
                return player_0;
            }
        }
        player_0 = this->state[DIMENSIONS-1][0].peek().getOwner();
        //DIAG 2
        if (player_0 != NO_PLAYER) {
            bool same_player = true;
            for (int j=1; j<DIMENSIONS; j++){
                Player player_j = this->state[DIMENSIONS-1-j][j].peek().getOwner();
                if (player_0 != player_j) {
                    same_player = false;
                }
            }
            if (same_player) {
                return player_0;
            }
        }
        return NO_PLAYER;
    }
}


std::ostream& Board::printHouses(std::ostream& stream, Player player) {
    std::string ligne = " ";
    std::string ligne2 = "|";
    std :: string p1 = "|PLAY|ER 1|    |";
    std :: string p2 = "|PLAY|ER 2|    |";
    for (int k = 0; k<DIMENSIONS; k++){
        ligne.append("____ ");
        ligne2.append("____|");
    }
    stream << ligne << endl;
    stream << "|";
    if (player==PLAYER_1){
        for (int i=0; i<NB_SIZE; i++){
            stream << PIECES_P1[i];
            stream << " :";
            stream << p1Pieces[i];
            stream << "|";
        }
        stream << endl;
        stream << p1 << endl;
    }
    if (player == PLAYER_2){
        for (int i=0; i<NB_SIZE; i++){
            stream << PIECES_P2[i];
            stream << " :";
            stream << p2Pieces[i];
            stream << "|";
        }
        stream << endl;
        stream << p2 << endl;
    }
    stream <<  ligne2 << endl;
    return stream;
}

std::ostream& operator<<(std::ostream& stream, Board& board){
    std::string ligne1 = "|";
    std::string ligne2 = "|";
    std::string ligne3 = " ";
    for (int k = 0; k<DIMENSIONS; k++){
        ligne1.append( "    |");
        ligne2.append("____|");
        ligne3.append("____ ");
    }



    //    stream << ligne1 << endl;
    stream << ligne3 << endl;

    for (int i = 0; i<DIMENSIONS;i++){
        stream << "| ";
        for (int j = 0; j<DIMENSIONS;j++){
            if (board.state[i][j].peek().getOwner() == PLAYER_1){
                if (board.state[i][j].peek().getSize() == SMALL){
                    stream << SMALLP1<< "  | ";
                }
                if (board.state[i][j].peek().getSize() == MEDIUM){
                    stream << MEDIUMP1 << "  | ";
                }
                if (board.state[i][j].peek().getSize() == LARGE){
                    stream << LARGEP1 << "  | ";
                }
            }
            else if (board.state[i][j].peek().getOwner() == PLAYER_2){
                if (board.state[i][j].peek().getSize() == SMALL){
                    stream << SMALLP2 << "  | ";
                }
                if (board.state[i][j].peek().getSize() == MEDIUM){
                    stream << MEDIUMP2 << "  | ";
                }
                if (board.state[i][j].peek().getSize() == LARGE){
                    stream << LARGEP2 << "  | ";
                }
            }
            else if (board.state[i][j].peek().getOwner() == NO_PLAYER){
                stream << " " << "  | ";
            }
        }
        stream << endl;
        stream << ligne2 << endl;
    }

    board.printHouses(stream,PLAYER_1);
    board.printHouses(stream,PLAYER_2);

    return stream;
}

