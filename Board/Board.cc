//
// Created by Najib Ishaq 4/24/18
//

#include "Board.h"
#include <cmath>

Board::Board ( const unsigned int *b , unsigned int n , unsigned int m , char type ) {
    auto num_rows = static_cast<unsigned int>(sqrt(n));
    this->n = num_rows;
    this->type = type;
    this->moves = m;
    for ( unsigned int i = 0 ; i < num_rows ; ++i ) {
        std::vector < unsigned int > row_grid , row_goal;
        for ( unsigned int j = 0 ; j < num_rows ; ++j ) {
            unsigned int index = 3 * i + j;
            row_grid.push_back( b[index] );
            row_goal.push_back(index);
        }
        grid.push_back(row_grid);
        goal.push_back(row_goal);
    }
    goal[num_rows-1][num_rows-1] = 0;
}

bool Board::is_solvable () {
    return false;
}

bool Board::is_goal () {
    return false;
}

void Board::neighbors ( std::vector < const Board * > *neigh , char type ) {

}

unsigned int Board::get_n_moves () {
    return 0;
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
