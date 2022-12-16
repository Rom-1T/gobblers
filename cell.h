#ifndef CELL_H
#define CELL_H

#include "config.h"
#include "piece.h"

//Acts as a stack, where only larger pieces can be pushed.
class Cell
{
    private:
    Piece stack[NB_SIZE];
    int index;
    public:
        Cell();
        Cell(const Cell& other);

        bool canPush(const Piece& piece);
        void push(const Piece& piece);
        bool canPop();
        Piece& pop();
        Piece& peek();

        Cell& operator=(const Cell& other);
};

#endif // CELL_H
