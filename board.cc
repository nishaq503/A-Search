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
    for ( unsigned int i = 0 ; i < n ; ++ i )
        this->b[i] = b[i];
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
        unsigned int row_0 = loc_0 / l;
        return static_cast< bool >( ( inv + row_0 ) % 2 );
    }
}

void Board::swap( unsigned int i , unsigned int j ) {
    b[i] ^= b[j];
    b[j] ^= b[i];
    b[i] ^= b[j];
}

void Board::neighbors( std::vector< Board * > *neigh , char type ) const {
    neigh->clear();
    unsigned int loc_0 = locate_0( );
    auto l = static_cast<unsigned int>( sqrt( n ) );

    if ( loc_0 == 0 ) { // top left corner
        auto temp_1 = new Board( b , n , moves + 1 , type );
        temp_1->swap( loc_0 , loc_0 + 1 );
        neigh->push_back( temp_1 );

        auto temp_2 = new Board( b , n , moves + 1 , type );
        temp_2->swap( loc_0 , loc_0 + l );
        neigh->push_back( temp_2 );
    }
    else if ( loc_0 == l - 1 ) { // top right corner
        auto temp_1 = new Board( b , n , moves + 1 , type );
        temp_1->swap( loc_0 , loc_0 - 1 );
        neigh->push_back( temp_1 );

        auto temp_2 = new Board( b , n , moves + 1 , type );
        temp_2->swap( loc_0 , loc_0 + l );
        neigh->push_back( temp_2 );
    }
    else if ( loc_0 == n - l ) { // bottom left corner
        auto temp_1 = new Board( b , n , moves + 1 , type );
        temp_1->swap( loc_0 , loc_0 - l );
        neigh->push_back( temp_1 );

        auto temp_2 = new Board( b , n , moves + 1 , type );
        temp_2->swap( loc_0 , loc_0 + 1 );
        neigh->push_back( temp_2 );
    }
    else if ( loc_0 == n - 1 ) { // bottom right corner
        auto temp_1 = new Board( b , n , moves + 1 , type );
        temp_1->swap( loc_0 , loc_0 - 1 );
        neigh->push_back( temp_1 );

        auto temp_2 = new Board( b , n , moves + 1 , type );
        temp_2->swap( loc_0 , loc_0 - l );
        neigh->push_back( temp_2 );
    }
    else if ( loc_0 % l == 0 ) { // top edge
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
    else if ( loc_0 % l == l - 1 ) { // right edge
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
    else if ( loc_0 / l == 0 ) { // left edge
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
    else if ( loc_0 / l == l - 1 ) { // bottom egde
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
    else { // center
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

unsigned int Board::hamming( const Board *that ) const {
    unsigned int count = 0;
    for ( unsigned int i = 0 ; i < n ; ++i )
        if ( this->b[i] && this->b[i] != that->b[i] )
            ++count;
    return count;
}

unsigned int Board::manhattan( ) const {
    unsigned int count = 0;
    auto l = static_cast< int >( sqrt( n ) );
    for ( unsigned int i = 0 ; i < n ; ++i ) {
        if ( b[i] ) {
            double dx = static_cast< int >( i ) % l - ( static_cast< int >( b[i] ) - 1 ) % l;
            double dy = static_cast< int >( i ) / l - ( static_cast< int >( b[i] ) - 1 ) / l; // NOLINT
            auto diff = static_cast< int >( std::abs( dx ) + std::abs( dy ) );
            count += diff;
        }
    }
    return count;
}

unsigned int Board::manhattan( const Board *that ) const {
    std::vector< double > dx( this->n ) , dy( this->n );
    auto l = static_cast< int >( sqrt( n ) );
    for ( unsigned int i = 0 ; i < this->n ; ++i ) {
        if ( this->b[i] ) {
            dx[ this->b[i] ] = static_cast< int >( i ) % l - ( static_cast< int >( this->b[i] ) - 1 ) % l;
            dy[ this->b[i] ] = static_cast< int >( i ) / l - ( static_cast< int >( this->b[i] ) - 1 ) / l; // NOLINT
        }
    }

    for ( unsigned int i = 0 ; i < that->n ; ++i ) {
        if ( that->b[i] ) {
            dx[ that->b[i] ] -= static_cast< int >( i ) % l - ( static_cast< int >( that->b[i] ) - 1 ) % l;
            dy[ that->b[i] ] -= static_cast< int >( i ) / l - ( static_cast< int >( that->b[i] ) - 1 ) / l; // NOLINT
        }
    }

    unsigned int result = 0;
    for ( unsigned int i = 1 ; i < dx.size() ; ++i )
        result += static_cast< unsigned int >( std::abs( dx[i] ) + std::abs( dy[i] ) );

    return result;
}

unsigned int Board::inversions( ) const {
    unsigned int count = 0;
    for ( unsigned int i = 0 ; i < n ; ++i )
        if ( b[i] )
            for ( unsigned int j = i + 1 ; j < n ; ++j )
                if ( b[j] && b[j] < b[i] )
                    ++count;
    return count;
}

bool Board::less( const Board *that ) const {
    for ( unsigned int i = 0 ; i < n ; ++i ) {
        if ( this->b[i] < that->b[i] ) return true;
        else if ( this->b[i] > that->b[i] ) return false;
    }
    return false;
}

void Board::print_board() const {
    for (unsigned int i = 0 ; i < n ; i ++)
        std::cout << b[i] << " ";
}

bool Board::equals( const Board *that ) const {
    for ( unsigned int i = 0 ; i < n ; ++i )
        if ( this->b[i] != that->b[i] )
            return false;
    return true;
}

pair::pair( const Board *start , const Board *stop ) {
    this->start = new Board( start->b , start->n , start->moves , start->type );
    this->stop = new Board( stop->b , stop->n , stop->moves , stop->type );
    this->type = start->type;
    this->priority = this->type == 'm'
                     ? start->moves + stop->moves + start->manhattan( stop )
                     : start->moves + stop->moves + start->hamming( stop );
}

pair::~pair() {
    delete start;
    delete stop;
}

void pair::print() const {
    auto l = static_cast< unsigned int >( sqrt ( start->n ) );
    for ( unsigned int i = 0 ; i < l ; ++i ) {
        for ( unsigned int j = 0 ; j < l ; ++j )
            std::cout << start->b[l * i + j] << " ";
        std::cout << "    ";
        for ( unsigned int j = 0 ; j < l ; ++j )
            std::cout << stop->b[l * i + j] << " ";
        std::cout << std::endl;
    }
    std::cout << "history: " << start->moves << ", future: " << stop->moves << std::endl;
    //std::cout << "start hamming: " << start->hamming() << ", stop hamming: " << stop->hamming() << std::endl;
    //std::cout << "diff hamming: " << start->hamming( stop ) << std::endl;
    std::cout << "start manhattan: " << start->manhattan() << ", stop manhattan: " << stop->manhattan() << std::endl;
    std::cout << "diff manhattan: " << start->manhattan( stop ) << std::endl;
    std::cout << "start priority: " << start->priority() << ", stop priority: " << stop->priority() << std::endl;
    std::cout << "diff priority: " << this->priority << std::endl << std::endl;
}
