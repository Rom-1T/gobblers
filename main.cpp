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

    char action;//inputs
    StatusEnum status;
    Player winner;

    Board* game = new Board();
    Player currentPlayer = PLAYER_1;

    do{
        std::cout << std::endl << std::endl << std::endl;
        cout << *game << endl;
        winner = game->getWinner();
        if(winner != NO_PLAYER){
            switch(winner){
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

        std::cout << "PLAYER " << currentPlayer << std::endl << std::endl;
        std::cout << "Action choice. 1: Place, 2: Move, q:Quit" << std::endl;
        std::cin >> action;

        do {
            switch(action){
            case '1':
                char size_char;
                Size size;
                int line;
                int column;
                std::cout << "Tu as choisi de placer un pièce" << std::endl << std::endl;
                do {
                    std::cout << "Size choice: S:Small, M:Medium, L:Large" << std::endl;
                    std::cin >> size_char;
                    switch(size_char){
                    case 'S' :
                        size = SMALL;
                        break;
                    case 'M' :
                        size = MEDIUM;
                        break;
                    case 'L' :
                        size = LARGE;
                        break;
                    default :
                        std::cout << "WRONG PIECE SIZE" << std::endl << std::endl;
                        break;
                    }
                }while(size_char != 'S' && size_char != 'M' && size_char != 'L' );
                std::cout << "Line choice: " << std::endl;
                std::cin >> line;
                std::cout << "Column choice: " << std::endl;
                std::cin >> column;
                status = game->placePiece(currentPlayer, size, line, column);
                break;

            case '2':
                int sourceLine;
                int targetLine;
                int sourceColumn;
                int targetColumn;
                std::cout << "Tu as choisi de déplacer une pièce" << std::endl << std::endl;
                std::cout << "Source line choice: " << std::endl;
                std::cin >> sourceLine;
                std::cout << "Source column choice: " << std::endl;
                std::cin >> sourceColumn;
                std::cout << "Target line choice: " << std::endl;
                std::cin >> targetLine;
                std::cout << "Target column choice: " << std::endl;
                std::cin >> targetColumn;
                status = game->movePiece(sourceLine, sourceColumn, targetLine, targetColumn);
                break;

            case 'q':
                std::cout << "AUREVOIR MON AMI" << std::endl << std::endl;
                break;

            default:
                std::cout << "MAUVAISE INPUT" << std::endl << std::endl;
                break;
            }
        }while(action != '1' && action != '2' && action != 'q' );
        if (status == OK){
            currentPlayer = game->nextPlayer(currentPlayer);
        }
        else{
            if (status == INVALID_SOURCE){
                std::cout << "INVALID SOURCE, TRY AGAIN" << std::endl << std::endl;
            }
            else if (status == INVALID_TARGET){
                std::cout << "INVALID TARGET, TRY AGAIN" << std::endl << std::endl;
            }
            else if (status == INVALID_ENTRY){
                std::cout << "INVALID ENTRY, TRY AGAIN" << std::endl << std::endl;
            }
        }
    }while(true);
    return 0;
}
