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
void solve ( const unsigned int *b , unsigned int n , char type ) {
    // TODO
    (void) b;
    (void) n;
    (void) type;
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// it all starts here
// -----------------------------------------------------------------------
int main ( int argc , char **argv ) {
    // reads the search type from a command line argument (either h or m)
    // reads all initial board values from the stdin
    // calls the solver passing the values of the board and the search type
    /*
    char type = argv[1][0];
    char *p_end;
    auto l = static_cast<unsigned int>(strtol( argv[2] , &p_end , 10 ));
    unsigned int n = l * l;
    auto *b = new unsigned int[n];
    for ( unsigned int i = 0 ; i < n ; ++i )
        b[i] = static_cast<unsigned int>(strtol( argv[i+3] , &p_end , 10 ));

    Board test( b , n-1 , 0 , type );
    std::cout << "Is it the goal board? " << test.is_goal() << std::endl;
    std::cout << "Is it solvable? " << test.is_solvable() << std::endl;
    std::cout << "Number of inversions: " << test.inversions() << std::endl;
    std::cout << "Number of moves so far: " << test.get_n_moves() << std::endl;
    std::cout << "Hamming Distance: " << test.hamming() << std::endl;
    std::cout << "Manhattan Distance: " << test.manhattan() << std::endl;
     */
    for ( int i = 0 ; i < argc ; ++i )
        std::cout << "i = " << i << ": " << argv[i] << std::endl;

    unsigned int n = 0;
    while ( std::cin >> n )
        std::cout << "just read: " << n << std::endl;

    return 0;
}
