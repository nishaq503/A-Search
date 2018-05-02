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
    std::vector< unsigned int > test_vec;
    unsigned int p;

    unsigned int locate_0( ) const;
    void swap( unsigned int i , unsigned int j );

public:
    // default constructor (for creating an empty Board)
    Board( ) { n = 0 ; type = 'm' ; moves = 0 ; b = nullptr ; } //NOLINT
    // full constructor
    // b: an initial Board configuration
    // the Board is just a sequence of numbers in row-major order (including the zero element)
    // n: number of elements in the Board
    // m: an initial number of moves
    // type: distance to be used 'm' for manhattan and 'b' for hamming
    Board( const unsigned int *b , unsigned int n , unsigned int m , char type );
    // destructor
    ~Board( ) { delete [] b ; }

    // verifies whether the Board is solvable
    bool is_solvable( ) const;
    // verifies whether the Board is a goal Board
    bool is_goal( ) const;
    // returns in neigh a list of neighbors for this node
    void neighbors( std::vector< Board *> *neigh , char type );
    // gets the number of moves made so far (up to this node)
    unsigned int get_n_moves( ) const { return moves ; }
    // returns the hamming distance to the goal
    unsigned int hamming( ) const;
    // returns the manhattan distance to the goal
    unsigned int manhattan( ) const;
    // counts the number of inversions on a particular Board
    unsigned int inversions( ) const;
    // returns the priority of the Board in the queue
    unsigned int priority( ) const { return type == 'm' ? moves + manhattan() : moves + hamming() ; }
    // returns weather two boards are the same
    bool equals( const Board *that ) const;
    // prints the Board to the terminal
    void print( ) const;
    void print_board() const;
};

#endif //__BOARD_H__
