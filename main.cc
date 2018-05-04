//
// Created by Najib Ishaq 4/24/18
//

#include <iostream>
#include <cstdlib>
#include <set>
#include <queue>
#include <vector>
#include "board.h"

// wraps up board comparison for set. will soon switch to hash.
struct set_compare {
    bool operator () (const Board *lhs , const Board *rhs ) const
    { return ( lhs->less( rhs ) ) ; }
};

// wraps up priority comparison for min-priority queue
struct priority_compare {
    bool operator () ( const Board *lhs , const Board *rhs ) const
    { return lhs->priority() > rhs->priority(); }
};

// I don't want to keep retyping this part
typedef std::set< Board * , set_compare > my_set;
typedef std::priority_queue< Board * , std::vector< Board * > , priority_compare > my_queue;

unsigned int get_solution( Board *start , char type ) {
    my_set history; // set of nodes already visited
    my_queue nodes; // min-priority queue of neighboring nodes not yet visited

    nodes.push( start );

    while ( ! nodes.top()->is_goal() ) { // stop when we have reached the goal
        // pop the board with the lowest priority and add it to history
        Board *current = nodes.top();
        nodes.pop();
        history.insert( current );

        // get all neighbors and insert into queue if they are not already in history
        std::vector< Board * > neigh;
        current->neighbors( &neigh , type );

        for ( auto i : neigh )
            history.find( i ) == history.end() ? nodes.push( i ) : delete i;
    }

    // get the number of moves made to solve the board.
    unsigned int num_moves = nodes.top()->get_n_moves();

    // clean up all allocated memory.
    for ( auto i : history )
        delete i;

    while ( ! nodes.empty() ) {
        Board *temp = nodes.top();
        nodes.pop();
        delete temp;
    }

    return num_moves;
}

// This function off-shores all the work and only prints the correct output.
void solve( const unsigned int *b , unsigned int n , char type ) {
    auto *start = new Board( b , n , 0 , type );

    start->is_solvable()
    ? std::cout << "Number of moves: " << get_solution( start , type ) << std::endl
    : std::cout << "Unsolvable board" << std::endl;
}

int main( int argc , char **argv ) {
    (void) argc;
    char type = argv[1][0];

    unsigned int l;
    std::cin >> l;

    unsigned int n = l * l;
    unsigned int b[n];

    for ( unsigned int i = 0 ; i < l ; ++i )
        for ( unsigned int j = 0 ; j < l ; ++j )
            std::cin >> b[l * i + j];

    solve( b , n , type );

    return 0;
}
