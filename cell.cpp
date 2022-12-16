#include "piece.h"
#include "cell.h"
#include "playerEnum.h"
#include "config.h"
#include "statusEnum.h"
#include <iostream>


Cell::Cell() {
    this->index = -1;
}

Cell::Cell(const Cell& other) {
    std::copy(std::begin(other.stack), std::end(other.stack), std::begin(this->stack));
    this->index = other.index;
}

bool Cell::canPush(const Piece &piece) {
    if (piece.getSize() == NONE) {
        return false; //On ne peut pas ajouter une pièce sans taille
    }
    else if (this->index == -1) {
        return true; //Aucune pièce n'est présente
    }
    else if (piece.getSize() == SMALL) {
        if (this->stack[this->index].getSize() == NONE ) {
            return true;
        }
        else {return false;}
    }
    else if (piece.getSize() == MEDIUM) {
        if (this->stack[this->index].getSize() == NONE || this->stack[this->index].getSize() == SMALL ) {
            return true;
        }
        else {return false;}

    }
    else if (piece.getSize() == LARGE) {
        if (this->stack[this->index].getSize() != LARGE ) {
            return true;
        }
        else {return false;}

    }
}

void Cell::push(const Piece& piece) {
    this->index ++;
    this->stack[this->index] = piece;
}

bool Cell::canPop() {
    if (this->index == -1) {
        return false;
    }
    else {
        return true;
    }
}

Piece& Cell::pop() {
    Piece piece = this->stack[this->index];
    this->index --;
    return piece;
}

Piece& Cell::peek(){
    if (this->index == -1 ) {
        return this->stack[this->index+1 ];
    }
    else {
        return this->stack[this->index];
    }
}

Cell& Cell::operator=(const Cell& other){
    std::copy(std::begin(other.stack), std::end(other.stack), std::begin(this->stack));
    this->index = other.index;
    return *this;
}
