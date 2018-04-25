//
// Created by Najib Ishaq 4/24/18
//

#include "Board.h"
#include <cmath>

Board::Board ( const unsigned int *b , unsigned int n , unsigned int m , char type ) {
    this->n = n;
    this->type = type;
    this->moves = m;
    this->b = new unsigned int[n+1];
    for ( unsigned int i = 0 ; i < n+1 ; ++i )
        this->b[i] = b[i];
}

bool Board::is_goal () {
    for ( unsigned int i = 0 ; i < n ; ++i )
        if ( b[i] != i+1 )
            return false;
    return true;
}

bool Board::is_solvable () {
    return false;
}

void Board::neighbors ( std::vector < const Board * > *neigh , char type ) {

}

unsigned int Board::hamming () {
    return 0;
}

unsigned int Board::manhattan () {
    return 0;
}

unsigned int Board::inversions () {
    return 0;
}
