#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

const int INF = 123456789;
const float EPSILON = 0.00001;

typedef pair< int, int > point;
typedef pair< float, float > fpoint;
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

inline float fnorm( point P, fpoint Q ) {
    return abs( ( float )P.first - Q.first ) + abs( ( float )P.second - Q.second );
}

int dynamic() {
    point P[ 2 ];
    utility J[ 2 ];
    bool parity = false;
    int cost;
    state key;

    scanf( "%i %i", &P[ parity ].first, &P[ parity ].second );
    J[ parity ][ make_pair( 0, B ) ] = norm( A, P[ parity ] );
    J[ parity ][ make_pair( 1, A ) ] = norm( B, P[ parity ] );

    for ( int i = 1; i < N; ++i ) {
      //  printf( "Dumping utility function before induction step %i over point [%i, %i]:\n", i, P[ parity ].first, P[ parity ].second );
      //  for ( utility::iterator u = J[ parity ].begin(); u != J[ parity ].end(); ++u ) {
      //      printf( "( %s, [ %i, %i ] ) = %i\n", u->first.first? "B": "A", u->first.second.first, u->first.second.second, u->second );
      //  }
      //  printf( "\n" );

        parity = !parity;
        scanf( "%i %i", &P[ parity ].first, &P[ parity ].second );
        J[ parity ].clear();
        // look at the previous utility function and update accordingly
        for ( utility::iterator u = J[ !parity ].begin(); u != J[ !parity ].end(); ++u ) {
            if ( J[ parity ].find( u->first ) == J[ parity ].end() ) {
                J[ parity ][ u->first ] = INF;
            }
            // same key: two consequent forces of the same agent
            J[ parity ][ u->first ] = min(
                J[ parity ][ u->first ],
                u->second + norm( P[ parity ], P[ !parity ] )
            );
            // different key: the two agents have swapped during this and the previous induction step
            key = make_pair( !u->first.first, P[ !parity ] );
            if ( J[ parity ].find( key ) == J[ parity ].end() ) {
                J[ parity ][ key ] = INF;
            }
            J[ parity ][ key ] = min(
                J[ parity ][ key ],
                u->second + norm( u->first.second, P[ parity ] )
            );
        }
    }
  //  printf( "Dumping utility function after final induction step over point [%i, %i]:\n", P[ parity ].first, P[ parity ].second );
  //  for ( utility::iterator u = J[ parity ].begin(); u != J[ parity ].end(); ++u ) {
  //      printf( "( %s, [ %i, %i ] ) = %i\n", u->first.first? "B": "A", u->first.second.first, u->first.second.second, u->second );
  //  }
  //  printf( "\n" );

    cost = INF;
    for ( utility::iterator u = J[ parity ].begin(); u != J[ parity ].end(); ++u ) {
        cost = min( cost, u->second );
    }
    return cost;
}

int kMeans() {
    point P[ N ];
    vector< bool > cluster( N );
    int assignCounts[ 2 ];
    fpoint means[ 2 ];
    point T;
    int cost;

    for ( int i = 0; i < N; ++i ) {
        scanf( "%i %i", &P[ i ].first, &P[ i ].second );
        // randomly partition the dataset
        cluster[ i ] = rand() % 2 == 1;
    }

    for ( int iteration = 0; iteration < 10; ++iteration ) {
        // update step: calculate new means
        means[ 0 ] = make_pair( 0.0, 0.0 );
        means[ 1 ] = make_pair( 0.0, 0.0 );
        assignCounts[ 0 ] = assignCounts[ 1 ] = 0;
        for ( int i = 0; i < N; ++i ) {
            printf( "Means in %i-th iteration after %i-th point: A = ( %2.2f, %2.2f ), B = ( %2.2f, %2.2f ).\n",
                    iteration, i, means[ 0 ].first, means[ 0 ].second, means[ 1 ].first, means[ 1 ].second );
            means[ cluster[ i ] ].first += ( float )P[ i ].first;
            means[ cluster[ i ] ].second += ( float )P[ i ].second;
            ++assignCounts[ cluster[ i ] ];
        }
        if ( assignCounts[ 0 ] == 0 ) {
            // remove cluster 0
            means[ 0 ] = make_pair( -1.0, -1.0 );
        }
        else {
            means[ 0 ].first /= ( float )assignCounts[ 0 ];
            means[ 0 ].second /= ( float )assignCounts[ 0 ];
        }
        if ( assignCounts[ 0 ] == 1 ) {
            // remove cluster 1
            means[ 1 ] = make_pair( -1.0, -1.0 );
        }
        else {
            means[ 1 ].first /= ( float )assignCounts[ 1 ];
            means[ 1 ].second /= ( float )assignCounts[ 1 ];
        }
        printf( "Means in %i-th iteration: A = ( %2.2f, %2.2f ), B = ( %2.2f, %2.2f ).\n",
                iteration, means[ 0 ].first, means[ 0 ].second, means[ 1 ].first, means[ 1 ].second );

        // assignment step: assign each data point to the cluster whose mean it's closest to
        for ( int i = 0; i < N; ++i ) {
            if ( ( fnorm( P[ i ], means[ 0 ] ) > fnorm( P[ i ], means[ 1 ] )
                   || means[ 0 ].first + 1 < EPSILON )
                 && means[ 1 ].first + 1 > EPSILON ) {
                cluster[ i ] = 1;
            }
            else {
                cluster[ i ] = 0;
            }
        }
    }
    if ( norm( A, means[ 0 ] ) + norm( B, means[ 1 ] )
       > norm( A, means[ 1 ] ) + norm( B, means[ 0 ] ) ) {
        // assign initial points optimally to cluster centers
        T = A;
        A = B;
        B = T;
    }
    printf( "Cluster centers at A = ( %i, %i ), B = ( %i, %i ).\n", means[ 0 ].first, means[ 0 ].second, means[ 1 ].first, means[ 1 ].second );
    cost = 0;
    for ( int i = 0; i < N; ++i ) {
        // calculate the cost of travel assigning each point to the agent
        // whose cluster it was assigned to
        if ( cluster[ i ] ) {
            // printf( "%i belongs to B.\n", i + 1 );
            cost += norm( B, P[ i ] );
            B = P[ i ];
        }
        else {
            // printf( "%i belongs to A.\n", i + 1 );
            cost += norm( A, P[ i ] );
            A = P[ i ];
        }
    }
    return cost;
}

int main() {
    // limits: 1 <= N <= 100,000
    //         1 <= R, C <= 10
    // rarely: 1 <= R, C <= 1000
    
    scanf( "%i %i %i", &N, &R, &C );
    scanf( "%i %i", &A.first, &A.second );
    scanf( "%i %i", &B.first, &B.second );

    if ( R * C > 110 ) {
        // dynamic programming is too slow, so use a k-means heuristic in O( N )
        // printf( "Using k-means algorithm.\n" );
        printf( "%i\n", kMeans() );
    }
    else {
        // dynamic programming will work fast enough for given data in O( RCN )
        // printf( "Using dynamic programming algorithm.\n" );
        printf( "%i\n", dynamic() );
    }

    return 0;
}
