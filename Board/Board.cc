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
    auto l = static_cast<unsigned int>( sqrt( n + 1 ) );
    unsigned int inv = inversions();
    if ( l % 2 ) {
        return inv % 2 == 0;
    } else {
        unsigned int loc_0;
        for ( loc_0 = 0 ; loc_0 < n+1 ; ++loc_0 )
            if ( ! b[loc_0] )
                break;
        unsigned int row_0 = loc_0 / 3 - 1;
        return static_cast<bool>( ( inv + row_0 ) % 2 );
    }
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
    unsigned int count = 0;
    for ( unsigned int i = 0 ; i < n+1 ; ++i )
        if ( b[i] )
            for ( unsigned int j = i ; j < n+1 ; ++j )
                if ( b[j] && b[j] < b[i] )
                    ++count;
    return count;
}
