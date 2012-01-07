#include <cstdio>
#include <map>
#include <utility>

using namespace std;

const int INFINITY = 9876543210;

typedef pair< int, int > point;
typedef pair< bool, point > state;
typedef map< state, int > utility;

int N, R, C;
point A, B;

inline int min( int a, int b ) {
    return a < b? a: b;
}

int main() {
    scanf( "%i %i %i", &N, &R, &C );
    scanf( "%i %i", &A.first, &A.second );
    scanf( "%i %i", &B.first, &B.second );

    if ( R * C < 110 ) {
        kMeans();
    }
    else {
        dynamic();
    }

    return 0;
}

inline int operator - ( point P, point Q ) {
    return abs( P.x - Q.x ) + abs( P.y - Q.y );
}

int dynamic() {
    point P[ 2 ];
    utility J[ 2 ];
    bool parity = false;
    int cost;

    scanf( "%i %i", &P[ parity ].first, &P[ parity ].second );
    J[ parity ][ make_pair( 0, A ) ] = A - P;
    J[ parity ][ make_pair( 1, B ) ] = B - P;

    for ( int i = 1; i < N; ++i ) {
        parity = !parity;
        scanf( "%i %i", &P.first, &P.second );
        J[ parity ].clear();
        for ( utility::iterator u = J[ !parity ].begin(); u != J[ !parity ].end(); ++u ) {
            J[ parity ][ u->first ] = u->second + ( P[ parity ] - P[ !parity ] );
            key = make_pair( !u->first->first, P[ !parity ] );
            if ( J[ parity ].find( key ) == map.end() ) {
                J[ parity ][ key ] = INFINITY;
            }
            J[ parity ][ key ] = min(
                J[ parity ][ key ],
                u->second + ( u->first->second - P[ !parity ] )
            );
        }
    }
    cost = INFINITY;
    for ( utility::iterator u = J[ parity ].begin(); u != J[ parity ].end(); ++u ) {
        cost = min( cost, u->second );
    }
    return cost;
}

int kMeans() {
    point P[ N ];

    for ( int i = 0; i < N; ++i ) {
        scanf( "%i %i", &P[ i ].first, &P[ i ].second );
    }
    // TODO
}
