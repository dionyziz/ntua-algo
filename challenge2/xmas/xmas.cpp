#include <cstdio>
#include <map>
#include <utility>
#include <cmath>

using namespace std;

const int INF = 123456789;

typedef pair< int, int > point;
typedef pair< bool, point > state;
typedef map< state, int > utility;

int N, R, C;
point A, B;

inline int min( int a, int b ) {
    return a < b? a: b;
}

inline int norm( point P, point Q ) {
    return abs( ( double )( P.first - Q.first ) ) + abs( ( double )( P.second - Q.second ) );
}

int dynamic() {
    point P[ 2 ];
    utility J[ 2 ];
    bool parity = false;
    int cost;
    state key;

    scanf( "%i %i", &P[ parity ].first, &P[ parity ].second );
    J[ parity ][ make_pair( 0, A ) ] = norm( A, P[ parity ] );
    J[ parity ][ make_pair( 1, B ) ] = norm( B, P[ parity ] );

    for ( int i = 1; i < N; ++i ) {
        parity = !parity;
        scanf( "%i %i", &P[ parity ].first, &P[ parity ].second );
        J[ parity ].clear();
        for ( utility::iterator u = J[ !parity ].begin(); u != J[ !parity ].end(); ++u ) {
            J[ parity ][ ( *u ).first ] = ( *u ).second + norm( P[ parity ], P[ !parity ] );
            key = make_pair( !( *u ).first.first, P[ !parity ] );
            if ( J[ parity ].find( key ) == J[ parity ].end() ) {
                J[ parity ][ key ] = INF;
            }
            J[ parity ][ key ] = min(
                J[ parity ][ key ],
                ( *u ).second + norm( ( *u ).first.second, P[ !parity ] )
            );
        }
    }
    cost = INF;
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
