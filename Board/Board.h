//
// Created by Najib Ishaq 4/24/18
//

#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>

class Board {
private:
    unsigned int n;
    char type;
    unsigned int moves;
    unsigned int *b;

public:
    // default constructor (for creating an empty board)
    Board () { n = 0; type = 'm'; moves = 0; } //NOLINT
    // full constructor
    // b: an initial board configuration
    // the board is just a sequence of numbers in row-major order (including the zero element)
    // n: number of elements in the board
    // m: an initial number of moves
    // type: distance to be used 'm' for manhattan and 'b' for hamming
    Board ( const unsigned int *b , unsigned int n , unsigned int m , char type );
    // destructor
    ~Board () { delete [] b; }

    // verifies whether the board is solvable
    bool is_solvable ();
    // verifies whether the board is a goal board
    bool is_goal ();
    // returns in neigh a list of neighbors for this node
    void neighbors ( std::vector<const Board *> *neigh , char type );
    // gets the number of moves made so far (up to this node)
    unsigned int get_n_moves () { return moves; }
    // returns the hamming distance to the goal
    unsigned int hamming ();
    // returns the manhattan distance to the goal
    unsigned int manhattan ();
    // counts the number of inversions on a particular board
    unsigned int inversions ();
};

#endif //__BOARD_H__
