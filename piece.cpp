#include "piece.h"
#include "cell.h"
#include "playerEnum.h"
#include "config.h"
#include "statusEnum.h"
#include <iostream>


Piece::Piece(){
    this->owner = NO_PLAYER;
    this->size = NONE;
}

Piece::Piece(Player owner, Size size){
    this->owner=owner;
    this->size=size;
}

Piece::Piece(const Piece& other){
    this->owner=other.owner;
    this->size=other.size;
}

Player Piece::getOwner() const{
    return this->owner;
}

Size Piece::getSize() const {
    return this->size;
}

Piece& Piece::operator=(const Piece& other){
    this->owner=other.owner;
    this->size=other.size;
    return *this;
}
