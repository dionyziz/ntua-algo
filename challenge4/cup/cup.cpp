#include <cstdio>
#include <vector>
#include <list>

using namespace std;

struct Edge {
    int u;
    int v;
};

Edge makeEdge( int u, int v ) {
    Edge ret;

    ret.u = u;
    ret.v = v;

    return ret;
}

int main() {
    int u, v, i, j, N, M, K;
    vector< list< Edge > > E;

    scanf( "%i %i", &N, &M );
    for ( u = 1; u <= N; ++u ) {
        scanf( "%i", &K );
        E.push_back( list< Edge >() );
        for ( j = 0; j < K; ++j ) {
            scanf( "%i", &v );
            E[ u ].push_back( makeEdge( u, v ) );
        }
    }

    for ( u = 0; u < N; ++u ) {
        for ( list< Edge >::iterator it = E[ u ].begin(); it != E[ u ].end(); ++it ) {
            printf( "%i -> %i\n", it->u, it->v );
        }
    }
    return 0;
}
