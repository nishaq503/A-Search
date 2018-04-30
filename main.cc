//
// Created by Najib Ishaq 4/24/18
//

#include <iostream>
#include <cstdlib>
#include "Board/Board.h"

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// this is the main solver
// -----------------------------------------------------------------------
// b: an initial board configuration
// the board is just a sequence of numbers in row-major order (including the zero element)
// n: number of elements in the board
// type: distance to be used 'm' for manhattan and 'b' for hamming
void solve( const unsigned int *b , unsigned int n , char type ) {
    // TODO
    (void) b;
    (void) n;
    (void) type;
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// it all starts here
// -----------------------------------------------------------------------
int main( int argc , char **argv ) {
    // reads the search type from a command line argument (either h or m)
    // reads all initial board values from the stdin
    // calls the solver passing the values of the board and the search type

    unsigned int b[] = {0, 1, 3, 4, 2, 5, 7, 8, 6};
    unsigned int n = sizeof( b ) / sizeof( b[0] );
    char type = 'h';

    Board test( b , n , 0 , type );
    std::cout << "Is it the goal board? " << test.is_goal() << std::endl;
    std::cout << "Is it solvable? " << test.is_solvable() << std::endl;
    std::cout << "Number of inversions: " << test.inversions() << std::endl;
    std::cout << "Number of moves so far: " << test.get_n_moves() << std::endl;
    std::cout << "Hamming Distance: " << test.hamming() << std::endl;
    std::cout << "Manhattan Distance: " << test.manhattan() << std::endl;


    return 0;
}
