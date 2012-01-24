#include <cstdio>
#include <queue>

using namespace std;

struct edge {
    int from;
    int to;
    int weight;
};

edge makeEdge( int u, int v, int w ) {
    edge ret;

    ret.from = u;
    ret.to = v;
    ret.weight = w;

    return ret;
}

int main() {
    priority_queue< edge > E;

    scanf( "%i %i", &N, &M );
    scanf( "%i %i", &u, &v, &w );

    for ( i = 0; i < M; ++i ) {
        E.push( makeEdge( u, v, w ) );
    }

    return 0;
}
