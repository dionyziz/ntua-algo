#include <cstdio>
#include <cstdlib>
#include <list>
#include <queue>
#include <cassert>

#define MAX( a, b ) ( ( a ) > ( b )? ( a ): ( b ) )
#define MIN( a, b ) ( ( a ) < ( b )? ( a ): ( b ) )

using namespace std;

typedef unsigned long long int LL;

const int UNVISITED = 0;
const LL INF = 900000000000;

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
int** W;
int* MSTParent;

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

    W = ( int** )malloc( N * sizeof( int* ) );
    for ( i = 0; i < N; ++i ) {
        W[ i ] = ( int* )malloc( N * sizeof( int ) );
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
}

LL secondBestMST() {
    int i;
    LL diff = INF;

    buildW();

    for ( i = 0; i < N; ++i ) {
        for ( list< edge >::iterator it = E[ i ].begin(); it != E[ i ].end(); ++it ) {
            if ( MSTParent[ it->u ] != it->v && MSTParent[ it->v ] != it->u ) {
                diff = MIN( diff, it->w - W[ it->u ][ it->v ] );
            }
        }
    }

    return diff;
}

LL prim() {
    priority_queue< edge > q;
    edge e;
    int i, j;
    LL cost;

    MSTParent = ( int* )malloc( N * sizeof( int ) );

    for ( i = 0; i < N; ++i ) {
        T.push_back( list< edge >() );
        MSTParent[ i ] = -1;
    }

    MSTParent[ 0 ] = 0;
    for ( list< edge >::iterator it = E[ 0 ].begin(); it != E[ 0 ].end(); ++it ) {
        q.push( *it );
    }
    cost = 0;
    while ( !q.empty() ) {
        e = q.top();
        q.pop();
        if ( MSTParent[ e.v ] == -1 ) {
            cost += e.w;
            T[ e.u ].push_back( makeEdge( e.u, e.v, e.w ) );
            T[ e.v ].push_back( makeEdge( e.v, e.u, e.w ) );
            MSTParent[ e.v ] = e.u;
            for ( list< edge >::iterator it = E[ e.v ].begin(); it != E[ e.v ].end(); ++it ) {
                q.push( *it );
            }
        }
    }

    return cost;
}

int main() {
    int i, u, v, M;
    int w;
    LL a, b;

    scanf( "%i %i", &N, &M );

    for ( i = 0; i < N; ++i ) {
        E.push_back( list< edge >() );
    }
    
    for ( i = 0; i < M; ++i ) {
        scanf( "%i %i %i", &u, &v, &w );
        --u; --v;
        E[ u ].push_back( makeEdge( u, v, w ) );
        E[ v ].push_back( makeEdge( v, u, w ) );
    }
    a = prim();
    b = secondBestMST();
    printf( "%lli %lli\n", a, a + b );

    return 0;
}
