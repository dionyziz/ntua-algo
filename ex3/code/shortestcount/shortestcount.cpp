#include <cstdio>
#include <queue>

const int INF = 987654321;

using namespace std;

struct node {
    int distance;
    int visited;
};

node makeNode( int distance, int visited ) {
    node ret;

    ret.distance = distance;
    ret.visited = visited;

    return ret;
}

int main() {
    int i, u, v, s, t, N, M, d;
    queue< pair< int, int > > q;
    pair< int, int > p;
    vector< list< int > > E;
    vector< node > V;
    list< int > l;

    scanf( "%i %i, %i %i", &N, &M, &s, &t );

    for ( i = 0; i < N; ++i ) {
        E.push_back( l );
        V.push_back( makeNode( INF, 0 ) );
    }

    for ( i = 0; i < M; ++i ) {
        scanf( "%i %i", &u, &v );
        E[ i ].push_back( v );
    }

    q.push( s );
    V[ s ].distance = 0;
    V[ s ].visited = 1;
    while ( !empty( q ) ) {
        u = q.top();
        if ( u == t ) {
            break;
        }
        q.pop();
        for ( list< int >::iterator it = E[ s ]; it != E[ s ]; ++it ) {
            if ( V[ *it ].distance == INF ) {
                q.push( *it );
            }
            if ( V[ u ].distance + 1 <= V[ *it ].distance ) {
                // < is first time visited; = is next
                V[ *it ].distance = V[ u ].distance + 1;
                V[ *it ].visited += V[ u ].visited;
            }
        }
    }
    printf( "%i\n", V[ t ].visited );

    return 0;
}
