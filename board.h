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

    // helper function to locate the empty tile
    unsigned int locate_0( ) const;
    // helper function to swap two tiles in the board
    void swap( unsigned int i , unsigned int j );

public:
    // default constructor (for creating an empty Board)
    Board( ) { n = 0 ; type = 'm' ; moves = 0 ; b = nullptr ; }
    // full constructor
    Board( const unsigned int *b , unsigned int n , unsigned int m , char type );
    // destructor
    ~Board( ) { delete [] b ; }

    // verifies whether the Board is solvable
    bool is_solvable( ) const;
    // verifies whether the Board is a goal Board
    bool is_goal( ) const;
    // returns in neigh a list of neighbors for this node
    void neighbors( std::vector< Board *> *neigh , char type ) const;
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
    // returns weather a board should be ordered before or after in the set
    bool less( const Board *that ) const;
    // prints the Board to the terminal
    void print_board() const;
};

#endif // __BOARD_H__
