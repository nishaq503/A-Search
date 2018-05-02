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
    { return ( ! lhs->equals( rhs ) ) ; }
};

struct priority_compare {
    bool operator () ( const Board *lhs , const Board *rhs ) const
    { return lhs->priority() > rhs->priority(); }
};

typedef std::set< Board * , set_compare > my_set;
typedef std::priority_queue< Board * , std::vector< Board * > , priority_compare > my_queue;

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
            unsigned int temp = i->priority();
            if ( history.find( i ) == history.end() ) {
                nodes.push( i );
            }
            else {
                delete i;
            }
        }
        
        neigh.clear();

        return r_get_solution( history , nodes , type );
    }
}

unsigned int get_solution( Board *start , char type ) {
    my_set history;
    my_queue nodes;

    history.insert( start );
    nodes.push( start );

    unsigned int num_moves = r_get_solution( history , nodes , type );

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

    if ( start->is_goal() ) std::cout << "Number of moves: " << 0 << std::endl;
    else if ( start->is_solvable() ) std::cout << "Number of moves: " << get_solution( start , type ) << std::endl;
    else std::cout << "Unsolvable Board" << std::endl;
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// it all starts here
// -----------------------------------------------------------------------
int main( int argc , char **argv ) {
    // reads the search type from a command line argument (either h or m)
    // reads all initial Board values from the stdin
    // calls the solver passing the values of the Board and the search type

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
    
    solve( b , n , type );

    return 0;
}
