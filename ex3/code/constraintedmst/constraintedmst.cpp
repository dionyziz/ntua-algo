#include <cstdio>
#include <vector>
#include <list>
#include <set>
#include <queue>

const int INF = 987654321;

using namespace std;

struct edge {
    int from;
    int to;
    int weight;
}

vector< list< edge > > E; // edges of the graph
set< int > L; // set of nodes that we are constrained to keep as leaves
vector< int > best; // minimum weight edge (so far) of a node in the L set

edge makeEdge( int from, int to, int weight ) {
    edge ret;

    return ret;
}

void edgeAdded( int u, int v, int w ) {
    // if u is in the L set and the edge is connecting it with the
    // rest of the graph (v is not in the L set)
    if ( L.find( u ) != L.end() && L.find( v ) != L.end() ) {
        if ( w < best[ u ] ) {
            // remove all other edges connecting u to the rest of the graph
            // and only keep ( u, v ) as it has minimum weight
            E[ u ].clear();
            E[ u ].push_back( makeEdge( u, v, w ) );
            best[ u ] = w;
        }
        return;
    }
    E[ u ].push_back( makeEdge( u, v, w ) );
}

int prim() {
    set< int > subgraph;
    priority_queue< edge > q;
    int s;
    edge e;
    int w = 0;

    s = 0;
    do {
        for ( list< edge >::iterator it = E[ s ].begin(); it != E[ s ].end(); ++it ) {
            q.push( *it );
        }
        do {
            e = q.top();
            q.pop();
        } while ( subgraph.find( e.to ) != subgraph.end() );
        if ( subgraph.fidn( e.to ) != subgraph.end() ) {
            s = e.to;
        }
        subgraph.insert( s );
        w += e.weight;
    }

    return w;
}

int main() {
    int i, u, v, w, N, M, Lsize;
    list< edge > l;

    scanf( "%i %i %i", &N, &M, &Lsize );

    // TODO: special case: N = 2; Lsize = 2; M = 1
    // TODO: special case: N = 1; Lsize <= 1
    // TODO: special case: N = 0

    for ( i = 0; i < N; ++i ) {
        E.push_back( l );
        best.push_back( INF );
    }
    for ( i = 0; i < Lsize; ++i ) {
        scanf( "%i", &u )
        L.insert( u );
    }
    for ( i = 0; i < M; ++i ) {
        scanf( "%i %i %i", &u, &v, &w );
        edgeAdded( u, v, w );
        edgeAdded( v, u, w );
    }
    prim();

    return 0;
}
