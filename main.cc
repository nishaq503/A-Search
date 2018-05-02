//
// Created by Najib Ishaq 4/24/18
//

#include <iostream>
#include <cstdlib>
#include <set>
#include <queue>
#include <vector>
#include "board.h"

struct set_compare {
    bool operator () (const Board *lhs , const Board *rhs ) const
    { return ( lhs->less( rhs ) ) ; }
};

struct priority_compare {
    bool operator () ( const Board *lhs , const Board *rhs ) const
    { return lhs->priority() > rhs->priority(); }
};

typedef std::set< Board * , set_compare > my_set;
typedef std::priority_queue< Board * , std::vector< Board * > , priority_compare > my_queue;

/*
unsigned int r_get_solution( my_set &history , my_queue &nodes , char type ) {
    Board *current = nodes.top();
    nodes.pop();
    history.insert( current );
    
    if ( current->is_goal() ) {
        return current->get_n_moves();
    }
    else {
        std::vector< Board * > neigh;
        current->neighbors( &neigh , type );

        for ( auto i : neigh ) {
            if ( history.find( i ) == history.end() ) {
                nodes.push( i );
            }
            else {
                delete i;
            }
        }
        return r_get_solution( history , nodes , type );
    }
}
*/

unsigned int get_solution( Board *start , char type ) {
    my_set history;
    my_queue nodes;

    unsigned int start_manhattan = start->manhattan(); (void) start_manhattan;
    unsigned int start_hamming = start->hamming(); (void) start_hamming;
    unsigned int start_priority = start->priority(); (void) start_priority;

    nodes.push( start );

    //unsigned int count = 0;
    while ( ! nodes.top()->is_goal() ) {
        Board *current = nodes.top();
        nodes.pop();
        history.insert( current );

        //unsigned int current_manhattan = current->manhattan(); (void) current_manhattan;
        //unsigned int current_hamming = current->hamming(); (void) current_hamming;
        //unsigned int current_priority = current->priority();// (void) current_priority;

        //std::cout << count++ << ": priority = " << current_priority << " and moves = " << current->get_n_moves() << std::endl;

        //current->print();

        std::vector< Board * > neigh;
        current->neighbors( &neigh , type );

        for ( auto i : neigh ) {
            //unsigned int i_manhattan = i->manhattan(); (void) i_manhattan;
            //unsigned int i_priority = i->priority(); (void) i_priority;
            if ( history.find( i ) == history.end() ) {
                nodes.push( i );
            }
            else {
                delete i;
            }
        }

        neigh.clear();
    }

    unsigned int num_moves = nodes.top()->get_n_moves();

    for ( auto i : history )
        delete i;

    while ( ! nodes.empty() ) {
        Board *temp = nodes.top();
        nodes.pop();
        delete temp;
    }

    return num_moves;
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// this is the main solver
// -----------------------------------------------------------------------
// b: an initial Board configuration
// the Board is just a sequence of numbers in row-major order (including the zero element)
// n: number of elements in the Board
// type: distance to be used 'm' for manhattan and 'b' for hamming
void solve( const unsigned int *b , unsigned int n , char type ) {

    auto *start = new Board( b , n , 0 , type );
    //unsigned int inv = start->inversions(); (void) inv;
    //bool sol = start->is_solvable(); (void) sol;

    if ( start->is_goal() ) std::cout << "Number of moves: " << 0 << std::endl;
    else if ( start->is_solvable() ) std::cout << "Number of moves: " << get_solution( start , type ) << std::endl;
    else std::cout << "Unsolvable board" << std::endl;
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// it all starts here
// -----------------------------------------------------------------------
int main( int argc , char **argv ) {
    // reads the search type from a command line argument (either h or m)
    // reads all initial Board values from the stdin
    // calls the solver passing the values of the Board and the search type

    (void) argc;
    char type = argv[1][0];

    unsigned int l , temp;
    std::cin >> l;

    unsigned int n = l * l;
    unsigned int b[n];

    for ( unsigned int i = 0 ; i < l ; ++i ) {
        for ( unsigned int j = 0 ; j < l ; ++j ) {
            std::cin >> temp;
            b[l * i + j] = temp;
        }
    }
    
    /*
    unsigned int n = 16;
    unsigned int b[16] = {3,1,6,4,5,0,9,7,10,2,11,8,13,15,14,12};
    char type = 'm';

    (void) argc; (void) argv;
    */
    solve( b , n , type );

    return 0;
}
