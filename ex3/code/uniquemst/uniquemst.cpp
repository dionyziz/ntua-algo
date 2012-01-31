#include <cstdio>
#include <queue>

using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
};

struct Node {
    Node* parent;
};

Edge makeEdge( int u, int v, int w ) {
    Edge ret;

    ret.from = u;
    ret.to = v;
    ret.weight = w;

    return ret;
}

int cmp( const void* a, const void* b ) {
    return ( ( Edge* )a )->weight - ( ( Edge* )b )->weight;
}

int main() {
    Edge E[ M ];
    Node V[ N ];

    scanf( "%i %i", &N, &M );
    scanf( "%i %i", &u, &v, &w );

    for ( i = 0; i < N; ++i ) {
        V[ i ].parent = V[ i ];
    }

    for ( i = 0; i < M; ++i ) {
        E[ i ] = makeEdge( u, v, w );
    }

    qsort( E, N, sizeof( Edge ), cmp );

    return 0;
}
