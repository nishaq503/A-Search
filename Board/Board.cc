//
// Created by Najib Ishaq 4/24/18
//

#include "Board.h"
#include <cmath>
#include <stdexcept>

Board::Board( const unsigned int *b , unsigned int n , unsigned int m , char type ) {
    this->n = n;
    this->type = type;
    this->moves = m;
    this->b = new unsigned int[n];
    for ( unsigned int i = 0 ; i < n ; ++i )
        this->b[i] = b[i];
}

bool Board::is_goal( ) {
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

bool Board::is_solvable( ) {
    auto l = static_cast< unsigned int >( sqrt( n ) );
    unsigned int inv = inversions( );
    if ( l % 2 ) {
        return inv % 2 == 0;
    } else {
        unsigned int loc_0 = locate_0( );
        unsigned int row_0 = loc_0 / 3 - 1;
        return static_cast< bool >( ( inv + row_0 ) % 2 );
    }
}

void Board::swap( unsigned int i , unsigned int j ) {
    b[i] ^= b[j];
    b[j] ^= b[i];
    b[i] ^= b[j];
}

void Board::neighbors( std::vector< Board * > *neigh , char type ) {
    neigh->clear();

    std::vector< Board * > result;
    unsigned int loc_0 = locate_0( );

    (void) type; (void) loc_0;
}

unsigned int Board::hamming( ) {
    unsigned int count = 0;
    for ( unsigned int i = 0 ; i < n ; ++i )
        if ( b[i] && b[i] != i+1 )
            ++count;
    return count;
}

unsigned int Board::manhattan( ) {
    unsigned int count = 0;
    for ( unsigned int i = 0 ; i < n ; ++i ) {
        if ( b[i] ) {
            double dx = static_cast< int >( i % 3 ) - ( b[i] - 1 ) % 3;
            double dy = static_cast< int >( i / 3 ) - ( b[i] - 1 ) / 3; // NOLINT
            auto diff = static_cast< int >( std::abs( dx ) + std::abs( dy ) );
            count += diff;
        }
    }
    return count;
}

unsigned int Board::inversions( ) {
    unsigned int count = 0;
    for ( unsigned int i = 0 ; i < n ; ++i )
        if ( b[i] )
            for ( unsigned int j = i ; j < n ; ++j )
                if ( b[j] && b[j] < b[i] )
                    ++count;
    return count;
}
