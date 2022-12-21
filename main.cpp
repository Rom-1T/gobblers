#include <iostream>
#include <string>
#include "board.h"

#include "piece.h"
#include "cell.h"
#include "playerEnum.h"
#include "config.h"
#include "statusEnum.h"
#include <iostream>

using namespace std;

int main()
{
    Cell cell_vide;
    Cell cell_2;
    Piece p_1 = Piece(PLAYER_2,MEDIUM);
    Piece p_2 = Piece(PLAYER_2,SMALL);


//    cout << "CAN POP ?  " << cell_vide.canPop() << endl;
//    cout << "CAN PUSH ?  " << cell_vide.canPush(p_1) << endl;
//    cell_vide.push(p_1);
//    cout << "CAN POP ?  " << cell_vide.canPop() << endl;
//    cout << "CAN PUSH SMALL ?  " << cell_vide.canPush(p_2) << endl;
//    Piece piece_peek = cell_vide.peek();
//    cout << "TAILLE :  " << piece_peek.getSize() << endl;
//    cout << "OWNER:  " << piece_peek.getOwner() << endl;
//    cell_2 = cell_vide;
//    piece_peek = cell_2.peek();
//    cout << "TAILLE :  " << piece_peek.getSize() << endl;
//    cout << "OWNER:  " << piece_peek.getOwner() << endl;
//    Piece p3;
//    p3 = piece_peek;
//    cout << "TAILLE :  " << p3.getSize() << endl;
//    cout << "OWNER:  " << p3.getOwner() << endl;

    char action; int l1; int c1; int l2; int c2; int s; //inputs
    StatusEnum status;
    Player winner;

    Board* game = new Board();
    Board plateau = Board();
    Player currentPlayer = PLAYER_1;

    do{
        std::cout << std::endl << std::endl << std::endl;
        cout << *game << endl;


        winner = game->getWinner();
        if(winner != NO_PLAYER){
            switch(currentPlayer){
            case PLAYER_1:
                std::cout << "JOUEUR 1 GAGNE" << std::endl << std::endl;
                break;
            
            case PLAYER_2:
                std::cout << "JOUEUR 2 GAGNE" << std::endl << std::endl;
                break;
            
            default:
                std::cout << "BUG : CURRENTPLAYER = NO_PLAYER" << std::endl << std::endl;
                break;
            }
            return 0;
        }

        
        std::cout << "Action choice. 1: Place, 2: Move, q:Quit" << std::endl;
        std::cin >> action;

        do {
            switch(action){
            case '1':
                std::cout << "Tu as choisi de placer un pièce" << std::endl << std::endl;

                //AJOUTER ICI LA PARTIE PLACER

                break;

            case '2':
                std::cout << "Tu as choisi de déplacer une pièce" << std::endl << std::endl;

                //AJOUTER ICI LA PARTIE DEPLACER

                break;

            case 'q':
                std::cout << "AUREVOIR MON AMI" << std::endl << std::endl;
                break;

            default:
                std::cout << "MAUVAISE INPUT" << std::endl << std::endl;
                break;
            }
        }while(action != '1' && action != '2' && action != 'q' );

        return 0;
        
        // A compléter
        
        /* If an error occurs, print something and replay this turn.*/
        // A compléter


    } while(true);
    return 0;
}

