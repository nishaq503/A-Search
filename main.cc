//
// Created by Najib Ishaq 4/24/18
//

#include <iostream>
#include <cstdlib>
#include <set>
#include <queue>
#include <vector>
#include <chrono>
#include <cmath>
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

// wraps up priority comparison for min-priority queue
struct better_priority_compare {
    bool operator () ( const pair *lhs , const pair *rhs ) const
    { return ! lhs->less( rhs ); }
};

// I don't want to keep retyping this part
typedef std::set< Board * , set_compare > my_set;
typedef std::priority_queue< Board * , std::vector< Board * > , priority_compare > my_queue;
typedef std::priority_queue< pair * , std::vector< pair * > , better_priority_compare > better_queue;

unsigned int get_solution( Board *start , char type ) {
    my_set history; // set of nodes already visited
    my_queue nodes; // min-priority queue of neighboring nodes not yet visited

    nodes.push( start );

    unsigned int count = 0;
    while ( ! nodes.top()->is_goal() ) { // stop when we have reached the goal
        ++count;

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
    std::cout << count << ", ";
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
    auto start = new Board( b , n , 0 , type );

    if ( start->is_solvable() )
        std::cout << "Number of moves: " << get_solution( start , type ) << std::endl;
    else {
        delete [] start;
        std::cout << "Unsolvable board" << std::endl;
    }
}

unsigned int get_better_solution( pair *start , char type ) {
    my_set history; // set of nodes already visited by start
    my_set future; // set of nodes already visited by stop
    better_queue nodes; // min-priority queue of neighboring nodes not yet visited

    nodes.push( start );
    pair *temp = nullptr;

    unsigned int count = 0;
    while ( ! nodes.top()->is_goal() ) { // stop when we have reached the goal
        ++count;

        //nodes.top()->print();

        // pop the pair with the lowest priority
        Board *current = nodes.top()->get_start();
        Board *goal = nodes.top()->get_stop();
        nodes.pop();

        // add the boards to history and future
        history.insert( current );
        future.insert( goal );

        // get all neighbors and insert into queue if they are not already in history or future
        std::vector< Board * > neigh , new_neigh_current , new_neigh_goal;

        current->neighbors( &neigh , type );
        for ( auto i : neigh )
            history.find( i ) == history.end() ? new_neigh_current.push_back( i ) : delete i;

        for ( auto i : new_neigh_current ) {
            if ( future.find( i ) != future.end() ) {
                auto found = future.find( i );
                temp = new pair( i , *found );
                nodes.push( temp );
                break;
            }
        }
        if ( temp ) break;

        goal->neighbors( &neigh , type );
        for ( auto i : neigh )
            future.find( i ) == future.end() ? new_neigh_goal.push_back( i ) : delete i;

        for ( auto i : new_neigh_goal ) {
            if ( history.find( i ) != history.end() ) {
                auto found = history.find( i );
                temp = new pair( i , *found );
                nodes.push( temp );
                break;
            }
        }
        if ( temp ) break;

        for ( auto &i : new_neigh_current ) {
            for ( auto &j : new_neigh_goal ) {
                temp = new pair( i , j );
                nodes.push( temp );
            }
        }
        temp = nullptr;
    }
    nodes.top()->print();

    std::cout << count << " tries, ";
    // get the number of moves made to solve the board.
    unsigned int num_moves = nodes.top()->get_n_moves();

    // clean up all allocated memory.
    for ( auto i : history )
        delete i;

    for ( auto i : future )
        delete i;

    while ( ! nodes.empty() ) {
        delete nodes.top();
        nodes.pop();
    }

    return num_moves;
}

void better_solve( const unsigned int *b , unsigned int n , char type ) {
    auto start = new Board( b , n , 0 , type );

    if ( start->is_solvable() ) {
        unsigned int temp[n];
        for ( unsigned int i = 0 ; i < n - 1 ; ++i )
            temp[i] = i + 1;
        temp[n - 1] = 0;
        auto stop = new Board( temp , n , 0 , type );
        auto my_pair = new pair( start , stop );
        unsigned int moves = get_better_solution( my_pair , type );
        std::cout << "Number of moves: " << moves << std::endl;
    }
    else {
        delete [] start;
        std::cout << "Unsolvable board" << std::endl;
    }
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

    /*
    (void) argv;
    char type = 'm';
    unsigned int n = 9;
    unsigned int b[n] = {0,1,3,4,2,5,7,8,6};
    //unsigned int b[n] = {4,1,2,3,0,6,5,7,8};
    //unsigned int b[n] = {2,3,0,1};
    */

    auto start = std::chrono::steady_clock::now();
    better_solve( b , n , type );

    auto end = std::chrono::steady_clock::now();
    double t_fast = std::chrono::duration< double > ( end - start ).count();

    ( log10( t_fast ) >= 1 )
    ? std::cout.precision( static_cast< std::streamsize >( 7 - floor( log10( t_fast ) ) ) )
    : std::cout.precision( 7 );
    std::cout << "Fast version: " << std::fixed << t_fast << " seconds!" << std::endl;

    start = std::chrono::steady_clock::now();
    solve( b , n , type );
    end = std::chrono::steady_clock::now();
    double t_slow = std::chrono::duration< double > ( end - start ).count();

    ( log10( t_slow ) >= 1 )
    ? std::cout.precision( static_cast< std::streamsize >( 7 - floor( log10( t_slow ) ) ) )
    : std::cout.precision( 7 );
    std::cout << "Slow version: " << std::fixed << t_slow << " seconds!" << std::endl;

    double improvement = t_slow / t_fast;
    ( log10( improvement ) >= 1 )
    ? std::cout.precision( static_cast< std::streamsize >( 7 - floor( log10( t_slow ) ) ) )
    : std::cout.precision( 7 );
    std::cout << "Improvement Factor: " << std::fixed << improvement << std::endl;

    return 0;
}
