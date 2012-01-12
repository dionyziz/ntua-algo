#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

#define MIN(a,b)  ((a) < (b) ? (a) : (b))

const int NUM_K_MEANS_ITERATIONS = 10;
const int NUM_K_MEANS_REPEAT = 10;
const int INF = 987654321;
const float EPSILON = 0.00001;

int N, R, C;
int A[ 2 ], B[ 2 ];
int J[ 2 ][ 2 ][ 10 ][ 10 ];

inline int norm( int P[ 2 ], int Q[ 2 ] ) {
    return abs( P[ 0 ] - Q[ 0 ] ) + abs( P[ 1 ] - Q[ 1 ] );
}

inline float fnorm( int P[ 2 ], float Q[ 2 ] ) {
    return fabs( ( float )P[ 0 ] - Q[ 0 ] ) + fabs( ( float )P[ 1 ] - Q[ 1 ] );
}

int printJ( int parity ) {
    for ( int agent = 0; agent < 2; ++agent ) {
        printf( "Agent %i:\n", agent );
        for ( int x = 0; x < C; ++x ) {
            for ( int y = 0; y < R; ++y ) {
                if ( J[ parity ][ agent ][ x ][ y ] > 100 ) {
                    printf( "INF " );
                }
                else {
                    printf( "%i   ", J[ parity ][ agent ][ x ][ y ] );
                }
            }
            printf( "\n" );
        }
    }
}

int dynamic() {
    int P[ 2 ][ 2 ];
    bool parity = false;
    int cost;

    scanf( "%i %i", &P[ parity ][ 0 ], &P[ parity ][ 1 ] );
    --P[ parity ][ 0 ]; --P[ parity ][ 1 ];

    memset( J[ parity ], 120, 2 * 10 * 10 * sizeof( int ) );
    // printf( "J after iteration 1: " );
    // printJ( parity );

    // printf( "A = ( %i, %i ). B = ( %i, %i ).\n", A[ 0 ], A[ 1 ], B[ 0 ], B[ 1 ] );

    J[ parity ][ 0 ][ B[ 0 ] ][ B[ 1 ] ] = norm( A, P[ parity ] );
    J[ parity ][ 1 ][ A[ 0 ] ][ A[ 1 ] ] = norm( B, P[ parity ] );

    // printf( "J after iteration 1: " );
    // printJ( parity );

    for ( int i = 1; i < N; ++i ) {
        // printf( "J after iteration %i: ", i + 1 );
        parity = !parity;
        scanf( "%i %i", &P[ parity ][ 0 ], &P[ parity ][ 1 ] );
        --P[ parity ][ 0 ]; --P[ parity ][ 1 ];
        memset( J[ parity ], 120, 2 * 10 * 10 * sizeof( int ) );
        // look at the previous utility function and update accordingly
        for ( int agent = 0; agent < 2; ++agent ) {
            for ( int x = 0; x < C; ++x ) {
                for ( int y = 0; y < R; ++y ) {
                    int prevJ = J[ !parity ][ agent ][ x ][ y ];
                    int thisX = P[ parity ][ 0 ];
                    int thisY = P[ parity ][ 1 ];
                    int prevX = P[ !parity ][ 0 ];
                    int prevY = P[ !parity ][ 1 ];

                    // same key: two consequent forces of the same agent
                    J[ parity ][ agent ][ x ][ y ] = MIN(
                        J[ parity ][ agent ][ x ][ y ],
                        prevJ
                        // norm
                        + abs( thisX - prevX )
                        + abs( thisY - prevY )
                    );

                    // different key: the two agents have swapped during this and the previous induction step
                    J[ parity ][ !agent ][ prevX ][ prevY ] = MIN(
                        J[ parity ][ !agent ][ prevX ][ prevY ],
                        prevJ
                        // norm
                        + abs( x - thisX )
                        + abs( y - thisY )
                    );
                }
            }
        }
    }

    cost = INF;
    for ( int agent = 0; agent < 2; ++agent ) {
        for ( int x = 0; x < C; ++x ) {
            for ( int y = 0; y < R; ++y ) {
                cost = MIN( cost, J[ parity ][ agent ][ x ][ y ] );
            }
        }
    }
    return cost;
}

int kMeans() {
    int P[ N ][ 2 ];
    vector< bool > cluster( N );
    int assignCounts[ 2 ];
    float means[ 2 ][ 2 ];
    int T[ 2 ];
    int cost;

    for ( int i = 0; i < N; ++i ) {
        scanf( "%i %i", &P[ i ][ 0 ], &P[ i ][ 1 ] );
        --P[ i ][ 0 ]; --P[ i ][ 1 ];
        // randomly partition the dataset
        cluster[ i ] = rand() % 2 == 1;
        printf( "%i-th point is ( %i, %i ) assigned to cluster %c.\n", i + 1, P[ i ][ 0 ], P[ i ][ 1 ], cluster[ i ]? 'B': 'A' );
    }

    for ( int iteration = 0; iteration < NUM_K_MEANS_ITERATIONS; ++iteration ) {
        // update step: calculate new means
        means[ 0 ][ 0 ] = 0.0;
        means[ 0 ][ 1 ] = 0.0;
        means[ 1 ][ 0 ] = 0.0;
        means[ 1 ][ 1 ] = 0.0;
        assignCounts[ 0 ] = assignCounts[ 1 ] = 0;
        for ( int i = 0; i < N; ++i ) {
            printf( "Means in %i-th iteration before %i-th point: A = ( %2.2f, %2.2f ), B = ( %2.2f, %2.2f ).\n",
                    iteration, i, means[ 0 ][ 0 ] + 1.0, means[ 0 ][ 1 ] + 1.0, means[ 1 ][ 0 ] + 1.0, means[ 1 ][ 1 ] + 1.0 );
            means[ cluster[ i ] ][ 0 ] += ( float )P[ i ][ 0 ];
            means[ cluster[ i ] ][ 1 ] += ( float )P[ i ][ 1 ];
            printf( "Means in %i-th iteration after %i-th point: A = ( %2.2f, %2.2f ), B = ( %2.2f, %2.2f ).\n",
                    iteration, i, means[ 0 ][ 0 ] + 1.0, means[ 0 ][ 1 ] + 1.0, means[ 1 ][ 0 ] + 1.0, means[ 1 ][ 1 ] + 1.0 );
            ++assignCounts[ cluster[ i ] ];
        }
        printf( "%i points belong to cluster A; %i points belong to cluster B.\n", assignCounts[ 0 ], assignCounts[ 1 ] );
        if ( assignCounts[ 0 ] == 0 ) {
            // remove cluster 0
            means[ 0 ][ 0 ] = -1.0;
        }
        else {
            means[ 0 ][ 0 ] /= ( float )assignCounts[ 0 ];
            means[ 0 ][ 1 ] /= ( float )assignCounts[ 0 ];
        }
        if ( assignCounts[ 1 ] == 0 ) {
            // remove cluster 1
            means[ 1 ][ 0 ] = -1.0;
        }
        else {
            means[ 1 ][ 0 ] /= ( float )assignCounts[ 1 ];
            means[ 1 ][ 1 ] /= ( float )assignCounts[ 1 ];
        }
        printf( "Means in %i-th iteration: A = ( %2.2f, %2.2f ), B = ( %2.2f, %2.2f ).\n",
                iteration, means[ 0 ][ 0 ] + 1.0, means[ 0 ][ 1 ] + 1.0, means[ 1 ][ 0 ] + 1.0, means[ 1 ][ 1 ] + 1.0 );

        // assignment step: assign each data point to the cluster whose mean it's closest to
        for ( int i = 0; i < N; ++i ) {
            if ( ( fnorm( P[ i ], means[ 0 ] ) > fnorm( P[ i ], means[ 1 ] )
                   || means[ 0 ][ 0 ] + 1 < EPSILON )
                 && means[ 1 ][ 0 ] + 1 > EPSILON ) {
                cluster[ i ] = 1;
            }
            else {
                cluster[ i ] = 0;
            }
        }
    }
    if ( fnorm( A, means[ 0 ] ) + fnorm( B, means[ 1 ] )
       > fnorm( A, means[ 1 ] ) + fnorm( B, means[ 0 ] ) ) {
        // assign initial points optimally to cluster centers
        T[ 0 ] = A[ 0 ];
        T[ 1 ] = A[ 1 ];
        A[ 0 ] = B[ 0 ];
        A[ 1 ] = B[ 1 ];
        B[ 0 ] = T[ 0 ];
        B[ 1 ] = T[ 1 ];
    }
    printf(
        "Cluster centers at A = ( %2.2f, %2.2f ), B = ( %2.2f, %2.2f ).\n",
        means[ 0 ][ 0 ] + 1.0, means[ 0 ][ 1 ] + 1.0, means[ 1 ][ 0 ] + 1.0, means[ 1 ][ 1 ] + 1.0
    );
    cost = 0;
    for ( int i = 0; i < N; ++i ) {
        // calculate the cost of travel assigning each point to the agent
        // whose cluster it was assigned to
        if ( cluster[ i ] ) {
            // printf( "%i belongs to B.\n", i + 1 );
            cost += norm( B, P[ i ] );
            B[ 0 ] = P[ i ][ 0 ];
            B[ 1 ] = P[ i ][ 1 ];
        }
        else {
            // printf( "%i belongs to A.\n", i + 1 );
            cost += norm( A, P[ i ] );
            A[ 0 ] = P[ i ][ 0 ];
            A[ 1 ] = P[ i ][ 1 ];
        }
    }
    return cost;
}

int main() {
    // limits: 1 <= N <= 100,000
    //         1 <= R, C <= 10
    // rarely: 1 <= R, C <= 1000
    
    scanf( "%i %i %i", &N, &C, &R );
    scanf( "%i %i", &A[ 0 ], &A[ 1 ] );
    scanf( "%i %i", &B[ 0 ], &B[ 1 ] );
    --A[ 0 ]; --A[ 1 ];
    --B[ 0 ]; --B[ 1 ];

    // if ( R > 10 || C > 10 ) {
        // dynamic programming is too slow, so use a k-means heuristic in O( N )
        // printf( "Using k-means algorithm.\n" );
        int cost = INF;

        for ( int i = 0; i < NUM_K_MEANS_REPEAT; ++i ) {
            cost = MIN( cost, kMeans() );
        }
        printf( "%i\n", cost );
  //  }
  //  else {
  //      // dynamic programming will work fast enough for given data in O( RCN )
  //      // printf( "Using dynamic programming algorithm.\n" );
  //      printf( "%i\n", dynamic() );
  //  }

    return 0;
}
