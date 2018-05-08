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

    // helper class for better solve
    friend class pair;

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
    // returns hamming distance to other board
    unsigned int hamming( const Board *that ) const;
    // returns the manhattan distance to the goal
    unsigned int manhattan( ) const;
    // returns manhattan distance to other board
    unsigned int manhattan( const Board *that ) const;
    // counts the number of inversions on a particular Board
    unsigned int inversions( ) const;
    // returns the priority of the Board in the queue
    unsigned int priority( ) const { return type == 'm' ? moves + manhattan() : moves + hamming() ; }
    // returns weather a board should be ordered before or after in the set
    bool less( const Board *that ) const;
    // verifies weather two boards are the same
    bool equals( const Board *that ) const;
    // prints the Board to the terminal
    void print_board() const;
};

class pair {
private:
    Board *start , *stop;
    unsigned int priority;
    char type;

public:
    pair( ) { start = stop = nullptr ; priority = 0 ; type = 'm' ; }
    pair( const Board *start , const Board *stop );
    ~pair( );

    Board *get_start() const { return start; }
    Board *get_stop() const { return stop; }
    unsigned int get_priority( ) const { return priority ; }

    unsigned int get_n_moves( ) const { return start->moves + stop->moves ; }

    unsigned int distance( ) const { return start->type == 'm' ? start->manhattan( stop ) : start->hamming( stop ) ; }
    bool is_goal( ) const { return start->equals( stop ) ; }
    bool less( const pair * that ) const { return this->priority == that->priority
                                                  ? this->distance() == that->distance()
                                                    ? this->get_n_moves() < that->get_n_moves()
                                                    : this->distance() < that->distance()
                                                  : this->priority < that->priority ; }
    void print( ) const;
};

#endif // __BOARD_H__
