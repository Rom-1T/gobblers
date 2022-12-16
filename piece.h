#ifndef PIECE_H
#define PIECE_H

#include "playerEnum.h"

enum Size{
    NONE,
    SMALL,
    MEDIUM,
    LARGE
};

class Piece
{
    private:
        Player owner;
        Size size;

    public:
        Piece();
        Piece(Player owner, Size size);
        Piece(const Piece& other);

        Player getOwner() const;
        Size getSize() const;

        Piece& operator=(const Piece& other);
};

#endif // PIECE_H
