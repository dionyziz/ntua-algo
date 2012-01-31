#include <cstdio>
#include <list>
#include <vector>

using namespace std;

bool UNDEFINED = 2;

vector< int > colors;
vector< list< int > > E;

bool DFS( int s, bool color ) {
    if ( colors[ s ] != UNDEFINED ) {
        if ( colors[ s ] != color ) {
            // not bipartite graph
            return false;
        }
        return true;
    }
    colors[ s ] = color;
    for ( list< int >::iterator it = E[ s ].begin(); it != E[ s ].end(); ++it ) {
        DFS( *it, !color );
    }
    return true;
}

int main() {
    list< int > l;
    int i, m, N, M, u, v;

    scanf( "%i %i", &N, &M );

    for ( int i = 0; i < N; ++i ) {
        E.push_back( l );
        colors.push_back( UNDEFINED );
    }

    for ( int m = 0; m < M; ++m ) {
        scanf( "%i %i", &u, &v );
        E[ u ].push_back( v );
    }

    if ( DFS( 0, 0 ) ) {
        printf( "0\n" );
    }
    else {
        printf( "1\n" );
    }

    return 0;
}
