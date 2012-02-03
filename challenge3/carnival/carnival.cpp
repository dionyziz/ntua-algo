#include <cstdio>
#include <vector>
#include <list>
#include <queue>
#include <cassert>

#define MAX( a, b ) ( ( a ) > ( b )? ( a ): ( b ) )
#define MIN( a, b ) ( ( a ) < ( b )? ( a ): ( b ) )

using namespace std;

const int UNVISITED = -1;
const int INF = 987654321;

struct edge {
    int u;
    int v;
    int w;
};

bool operator <( edge e, edge f ) {
    return e.w > f.w;
}

int N;
vector< list< edge > > E;
vector< list< edge > > T;
int W[ 2012 ][ 2012 ];
bool MST[ 2012 ][ 2012 ];

edge makeEdge( int u, int v, int w ) {
    edge ret;

    ret.u = u;
    ret.v = v;
    ret.w = w;

    return ret;
}

void buildW() {
    int root, node, i, j;
    queue< int > frontier;

    // printf( "W building in progress.\n" );

    for ( i = 0; i < N; ++i ) {
        for ( j = 0; j < N; ++j ) {
            W[ i ][ j ] = UNVISITED;
        }
        W[ i ][ i ] = 0;
    }

    for ( root = 0; root < N; ++root ) {
        assert( frontier.empty() );
        frontier.push( root );
        while ( !frontier.empty() ) {
            node = frontier.front();
            frontier.pop();
            for ( list< edge >::iterator it = T[ node ].begin(); it != T[ node ].end(); ++it ) {
                if ( W[ root ][ it->v ] == UNVISITED ) {
                    W[ root ][ it->v ] = MAX( it->w, W[ root ][ node ] );
                    frontier.push( it->v );
                }
            }
        }
    }

    // printf( "W array:\n" );
    // for ( i = 0; i < N; ++i ) {
    //     for ( j = 0; j < N; ++j ) {
    //         printf( "%i\t", W[ i ][ j ] );
    //     }
    //     printf( "\n" );
    // }
}

int secondBestMST() {
    int i, diff = INF;

    // printf( "Second best hello.\n" );
    buildW();

    for ( i = 0; i < N; ++i ) {
        for ( list< edge >::iterator it = E[ i ].begin(); it != E[ i ].end(); ++it ) {
            // printf( "Checking edge (%i, %i).\n", it->u, it->v );
            if ( !MST[ it->u ][ it->v ] ) {
                // printf( "Found an edge not in the MST.\n" );
                diff = MIN( diff, it->w - W[ it->u ][ it->v ] );
            }
        }
    }

    return diff;
}

int prim() {
    bool visited[ N ];
    priority_queue< edge > q;
    edge e;
    list< edge > l;
    int i, j, cost;

    // printf( "Prim hello.\n" );

    for ( i = 0; i < N; ++i ) {
        T.push_back( l );
        for ( j = 0; j < N; ++j ) {
            MST[ i ][ j ] = false;
        }
    }

    visited[ 0 ] = true;
    for ( list< edge >::iterator it = E[ 0 ].begin(); it != E[ 0 ].end(); ++it ) {
        q.push( *it );
    }
    cost = 0;
    while ( !q.empty() ) {
        e = q.top();
        q.pop();
        if ( !visited[ e.v ] ) {
            cost += e.w;
            visited[ e.v ] = true;
            T[ e.u ].push_back( makeEdge( e.u, e.v, e.w ) );
            T[ e.v ].push_back( makeEdge( e.v, e.u, e.w ) );
            MST[ e.u ][ e.v ] = true;
            MST[ e.v ][ e.u ] = true;
            for ( list< edge >::iterator it = E[ e.v ].begin(); it != E[ e.v ].end(); ++it ) {
                q.push( *it );
            }
        }
    }

    // printf( "Prim MST = %i\n", cost );
    // printf( "Here is the MST tree:\n" );

    // for ( i = 0; i < N; ++i ) {
    //     printf( "%i: ", i );
    //     for ( list< edge >::iterator it = T[ i ].begin(); it != T[ i ].end(); ++it ) {
    //         printf( "%i (%i)\t", it->v, it->w );
    //     }
    //     printf( "\n" );
    // }
    // printf( "\nAnd here are the marked edges:\n" );
    // for ( i = 0; i < N; ++i ) {
    //     for ( j = 0; j < N; ++j ) {
    //         printf( "%i\t", MST[ i ][ j ] );
    //     }
    //     printf( "\n" );
    // }

    return cost;
}


int main() {
    int i, u, v, w, M, a, b;
    list< edge > l;

    scanf( "%i %i", &N, &M );
    for ( i = 0; i < N; ++i ) {
        E.push_back( l );
    }
    // printf( "Reading teh edges.\n" );
    for ( i = 0; i < M; ++i ) {
        scanf( "%i %i %i", &u, &v, &w );
        --u; --v;
        E[ u ].push_back( makeEdge( u, v, w ) );
        E[ v ].push_back( makeEdge( v, u, w ) );
    }
    // printf( "Read teh edges.\n" );
    a = prim();
    b = secondBestMST();
    printf( "%i %i\n", a, a + b );

    return 0;
}
