//
// Created by Najib Ishaq 4/24/18
//

#include "board.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

Board::Board( const unsigned int *b , unsigned int n , unsigned int m , char type ) {
    this->n = n;
    this->type = type;
    this->moves = m;
    this->b = new unsigned int[n];
    test_vec.clear();
    for ( unsigned int i = 0 ; i < n ; ++ i ) {
        this->b[i] = b[i];
        test_vec.push_back( b[i] );
    }
    p = priority();
}

bool Board::is_goal( ) const {
    for ( unsigned int i = 0 ; i < n-1 ; ++i )
        if ( b[i] != i+1 )
            return false;
    return true;
}

unsigned int Board::locate_0( ) const {
    unsigned int loc_0;
    for ( loc_0 = 0 ; loc_0 < n ; ++loc_0 )
        if ( ! b[loc_0] )
            break;
    return loc_0;
}

bool Board::is_solvable( ) const {
    auto l = static_cast< unsigned int >( sqrt( n ) );
    unsigned int inv = inversions( );
    if ( l % 2 ) {
        return inv % 2 == 0;
    } else {
        unsigned int loc_0 = locate_0( );
        unsigned int row_0 = loc_0 / 3;
        return static_cast< bool >( ( inv + row_0 ) % 2 );
    }
}

void Board::swap( unsigned int i , unsigned int j ) {
    b[i] ^= b[j];
    b[j] ^= b[i];
    b[i] ^= b[j];

    test_vec[i] = b[i];
    test_vec[j] = b[j];
}

void Board::neighbors( std::vector< Board * > *neigh , char type ) {
    neigh->clear();
    unsigned int loc_0 = locate_0( );
    auto l = static_cast<unsigned int>(sqrt( n ));

    if ( loc_0 == 0 ) {
        auto temp_1 = new Board( b , n , moves + 1 , type );
        temp_1->swap( loc_0 , loc_0 + 1 );
        neigh->push_back( temp_1 );

        auto temp_2 = new Board( b , n , moves + 1 , type );
        temp_2->swap( loc_0 , loc_0 + l );
        neigh->push_back( temp_2 );
    }
    else if ( loc_0 == l - 1 ) {
        auto temp_1 = new Board( b , n , moves + 1 , type );
        temp_1->swap( loc_0 , loc_0 - 1 );
        neigh->push_back( temp_1 );

        auto temp_2 = new Board( b , n , moves + 1 , type );
        temp_2->swap( loc_0 , loc_0 + l );
        neigh->push_back( temp_2 );
    }
    else if ( loc_0 == n - l ) {
        auto temp_1 = new Board( b , n , moves + 1 , type );
        temp_1->swap( loc_0 , loc_0 - l );
        neigh->push_back( temp_1 );

        auto temp_2 = new Board( b , n , moves + 1 , type );
        temp_2->swap( loc_0 , loc_0 + 1 );
        neigh->push_back( temp_2 );
    }
    else if ( loc_0 == n - 1 ) {
        auto temp_1 = new Board( b , n , moves + 1 , type );
        temp_1->swap( loc_0 , loc_0 - 1 );
        neigh->push_back( temp_1 );

        auto temp_2 = new Board( b , n , moves + 1 , type );
        temp_2->swap( loc_0 , loc_0 - l );
        neigh->push_back( temp_2 );
    }
    else if ( loc_0 % l == 0 ) {
        auto temp_1 = new Board( b , n , moves + 1 , type );
        temp_1->swap( loc_0 , loc_0 - l );
        neigh->push_back( temp_1 );

        auto temp_2 = new Board( b , n , moves + 1 , type );
        temp_2->swap( loc_0 , loc_0 + 1 );
        neigh->push_back( temp_2 );

        auto temp_3 = new Board( b , n , moves + 1 , type );
        temp_3->swap( loc_0 , loc_0 + l );
        neigh->push_back( temp_3 );
    }
    else if ( loc_0 % l == l - 1 ) {
        auto temp_1 = new Board( b , n , moves + 1 , type );
        temp_1->swap( loc_0 , loc_0 - l );
        neigh->push_back( temp_1 );

        auto temp_2 = new Board( b , n , moves + 1 , type );
        temp_2->swap( loc_0 , loc_0 - 1 );
        neigh->push_back( temp_2 );

        auto temp_3 = new Board( b , n , moves + 1 , type );
        temp_3->swap( loc_0 , loc_0 + l );
        neigh->push_back( temp_3 );
    }
    else if ( loc_0 / l == 0 ) {
        auto temp_1 = new Board( b , n , moves + 1 , type );
        temp_1->swap( loc_0 , loc_0 - 1 );
        neigh->push_back( temp_1 );

        auto temp_2 = new Board( b , n , moves + 1 , type );
        temp_2->swap( loc_0 , loc_0 + l );
        neigh->push_back( temp_2 );

        auto temp_3 = new Board( b , n , moves + 1 , type );
        temp_3->swap( loc_0 , loc_0 + 1 );
        neigh->push_back( temp_3 );
    }
    else if ( loc_0 / l == l - 1 ) {
        auto temp_1 = new Board( b , n , moves + 1 , type );
        temp_1->swap( loc_0 , loc_0 - 1 );
        neigh->push_back( temp_1 );

        auto temp_2 = new Board( b , n , moves + 1 , type );
        temp_2->swap( loc_0 , loc_0 - l );
        neigh->push_back( temp_2 );

        auto temp_3 = new Board( b , n , moves + 1 , type );
        temp_3->swap( loc_0 , loc_0 + 1 );
        neigh->push_back( temp_3 );
    }
    else {
        auto temp_1 = new Board( b , n , moves + 1 , type );
        temp_1->swap( loc_0 , loc_0 - 1 );
        neigh->push_back( temp_1 );

        auto temp_2 = new Board( b , n , moves + 1 , type );
        temp_2->swap( loc_0 , loc_0 - l );
        neigh->push_back( temp_2 );

        auto temp_3 = new Board( b , n , moves + 1 , type );
        temp_3->swap( loc_0 , loc_0 + 1 );
        neigh->push_back( temp_3 );

        auto temp_4 = new Board( b , n , moves + 1 , type );
        temp_4->swap( loc_0 , loc_0 + l );
        neigh->push_back( temp_4 );
    }
}

unsigned int Board::hamming( ) const {
    unsigned int count = 0;
    for ( unsigned int i = 0 ; i < n ; ++i )
        if ( b[i] && b[i] != i+1 )
            ++count;
    return count;
}

unsigned int Board::manhattan( ) const {
    unsigned int count = 0;
    for ( unsigned int i = 0 ; i < n ; ++i ) {
        if ( b[i] ) {
            double dx = static_cast< int >( i % 3 ) - ( static_cast< int >( b[i] ) - 1 ) % 3;
            double dy = static_cast< int >( i / 3 ) - ( static_cast< int >( b[i] ) - 1 ) / 3; // NOLINT
            auto diff = static_cast< int >( std::abs( dx ) + std::abs( dy ) );
            count += diff;
        }
    }
    return count;
}

unsigned int Board::inversions( ) const {
    unsigned int count = 0;
    for ( unsigned int i = 0 ; i < n ; ++i )
        if ( b[i] )
            for ( unsigned int j = i ; j < n ; ++j )
                if ( b[j] < b[i] )
                    ++count;
    return count;
}

bool Board::equals( const Board *that ) const {
    if ( this->n != that->n ) return false;

    for (unsigned int i = 0 ; i < this->n ; ++i)
        if ( this->b[i] != that->b[i] )
            return false;
    return true;
}

void Board::print() const {
    auto l = static_cast<unsigned int>(sqrt( n ));
    for ( unsigned int i = 0 ; i < l ; ++i ) {
        for ( unsigned int j = 0 ; j < l ; ++j )
            std::cout << b[l * i + j] << " ";
        std::cout << std::endl;
    }
    std::cout << "hamming: " << hamming() << std::endl;
    std::cout << "manhattan: " << manhattan() << std::endl;
    std::cout << "moves: " << get_n_moves() << std::endl;
    std::cout << "type: " << type << std::endl;
    std::cout << "priority: " << priority() << std::endl << std::endl;
}

void Board::print_board() const {
    // the loop below assumes that `N` is the length of your array,
    // if you have another variable name for this, please adjust
    // the code properly
    // (for a 3 by 3 board, the value of N is 9)
    // also, if you have another name for `board` just replace it below
    for (unsigned int i = 0 ; i < n ; i ++) {
        std::cout << b[i] << " ";
    }
}
