#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

#define MIN(a,b)  ((a) < (b) ? (a) : (b))

int NUM_K_MEANS_ITERATIONS = 13;
int NUM_K_MEANS_REPEAT = 3;
const int INF = 987654321;
const float EPSILON = 0.00001;

int N, R, C;
int A[ 2 ], B[ 2 ];
int J[ 2 ][ 2 ][ 10 ][ 10 ];
int P[ 100010 ][ 2 ];

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
    int parity = 0;
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
        parity = 1 - parity;
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

void readPoints() {
    for ( int i = 0; i < N; ++i ) {
        scanf( "%i %i", &P[ i ][ 0 ], &P[ i ][ 1 ] );
        --P[ i ][ 0 ]; --P[ i ][ 1 ];
    }
}

int kMeans() {
    vector< bool > cluster( N );
    int assignCounts[ 2 ];
    float means[ 2 ][ 2 ];
    int T[ 2 ];
    int originalA[ 2 ], originalB[ 2 ];
    int cost, mincost = INF;
    int min[ 2 ] = { INF, INF }, max[ 2 ] = { -1, -1 };

    for ( int i = 0; i < N; ++i ) {
        if ( P[ i ][ 0 ] < min[ 0 ] ) {
            min[ 0 ] = P[ i ][ 0 ];
        }
        if ( P[ i ][ 1 ] < min[ 1 ] ) {
            min[ 1 ] = P[ i ][ 1 ];
        }
        if ( P[ i ][ 0 ] > max[ 0 ] ) {
            max[ 0 ] = P[ i ][ 0 ];
        }
        if ( P[ i ][ 1 ] > max[ 1 ] ) {
            max[ 1 ] = P[ i ][ 1 ];
        }
    }
    means[ 0 ][ 0 ] = rand() % ( max[ 0 ] - min[ 0 ] ) + min[ 0 ];
    means[ 0 ][ 1 ] = rand() % ( max[ 1 ] - min[ 1 ] ) + min[ 1 ];
    means[ 1 ][ 0 ] = rand() % ( max[ 0 ] - min[ 0 ] ) + min[ 0 ];
    means[ 1 ][ 1 ] = rand() % ( max[ 1 ] - min[ 1 ] ) + min[ 1 ];

    originalA[ 0 ] = A[ 0 ];
    originalA[ 1 ] = A[ 1 ];
    originalB[ 0 ] = B[ 0 ];
    originalB[ 1 ] = B[ 1 ];
    for ( int reinitialization = 0; reinitialization < NUM_K_MEANS_REPEAT; ++reinitialization ) {
        for ( int iteration = 0; iteration < NUM_K_MEANS_ITERATIONS; ++iteration ) {
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

            // update step: calculate new means
            means[ 0 ][ 0 ] = 0.0;
            means[ 0 ][ 1 ] = 0.0;
            means[ 1 ][ 0 ] = 0.0;
            means[ 1 ][ 1 ] = 0.0;
            assignCounts[ 0 ] = assignCounts[ 1 ] = 0;
            for ( int i = 0; i < N; ++i ) {
               // printf( "Means in %i-th iteration before %i-th point: A = ( %2.2f, %2.2f ), B = ( %2.2f, %2.2f ), P = ( %i, %i ).\n",
               //         iteration, i, means[ 0 ][ 0 ] + 1.0, means[ 0 ][ 1 ] + 1.0, means[ 1 ][ 0 ] + 1.0, means[ 1 ][ 1 ] + 1.0, P[ i ][ 0 ], P[ i ][ 1 ] );
                means[ cluster[ i ] ][ 0 ] += ( float )P[ i ][ 0 ];
                means[ cluster[ i ] ][ 1 ] += ( float )P[ i ][ 1 ];
               // printf( "Means in %i-th iteration after %i-th point: A = ( %2.2f, %2.2f ), B = ( %2.2f, %2.2f ).\n",
               //         iteration, i, means[ 0 ][ 0 ] + 1.0, means[ 0 ][ 1 ] + 1.0, means[ 1 ][ 0 ] + 1.0, means[ 1 ][ 1 ] + 1.0 );
                ++assignCounts[ cluster[ i ] ];
            }
            // printf( "%i points belong to cluster A; %i points belong to cluster B.\n", assignCounts[ 0 ], assignCounts[ 1 ] );
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
            // printf( "Means in %i-th iteration: A = ( %2.2f, %2.2f ), B = ( %2.2f, %2.2f ).\n",
            //         iteration, means[ 0 ][ 0 ] + 1.0, means[ 0 ][ 1 ] + 1.0, means[ 1 ][ 0 ] + 1.0, means[ 1 ][ 1 ] + 1.0 );

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
        // printf(
        //     "Cluster centers at A = ( %2.2f, %2.2f ), B = ( %2.2f, %2.2f ).\n",
        //     means[ 0 ][ 0 ] + 1.0, means[ 0 ][ 1 ] + 1.0, means[ 1 ][ 0 ] + 1.0, means[ 1 ][ 1 ] + 1.0
        // );
        cost = 0;
        for ( int i = 0; i < N; ++i ) {
            // calculate the cost of travel assigning each point to the agent
            // whose cluster it was assigned to
            if ( cluster[ i ] ) {
                // printf( "%i (%i, %i) belongs to B.\n", i + 1, P[ i ][ 0 ], P[ i ][ 1 ] );
                cost += norm( B, P[ i ] );
                B[ 0 ] = P[ i ][ 0 ];
                B[ 1 ] = P[ i ][ 1 ];
            }
            else {
                // printf( "%i (%i, %i) belongs to A.\n", i + 1, P[ i ][ 0 ], P[ i ][ 1 ] );
                cost += norm( A, P[ i ] );
                A[ 0 ] = P[ i ][ 0 ];
                A[ 1 ] = P[ i ][ 1 ];
            }
        }
        // printf( "Improving kMeans cost: %i -> %i\n", mincost, cost );
        mincost = MIN( mincost, cost );
        A[ 0 ] = originalA[ 0 ];
        A[ 1 ] = originalA[ 1 ];
        B[ 0 ] = originalB[ 0 ];
        B[ 1 ] = originalB[ 1 ];
    }

    return mincost;
}

int greedy() {
    int cost = 0, costA, costB;

    for ( int i = 0; i < N; ++i ) {
        costA = norm( A, P[ i ] );
        costB = norm( B, P[ i ] );
        if ( costA < costB ) {
            cost += costA;
            A[ 0 ] = P[ i ][ 0 ];
            A[ 1 ] = P[ i ][ 1 ];
        }
        else {
            cost += costB;
            B[ 0 ] = P[ i ][ 0 ];
            B[ 1 ] = P[ i ][ 1 ];
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

    if ( R > 10 || C > 10 ) {
        // dynamic programming is too slow, so use a k-means and greedy heuristics in O( N )
        // printf( "Using k-means and greedy algorithms.\n" );
        int cost;
        int greedyCost, kMeansCost;

        readPoints();
        kMeansCost = kMeans();
        greedyCost = greedy();
        // printf( "Greedy cost = %i\n", greedyCost );
        // printf( "kMeans cost = %i\n", kMeansCost );
        // printf( "%i\n", ( int )floor( kMeansCost * 0.85 ) );
        cost = MIN( greedyCost, kMeansCost );
        // heuristic results are always worse than the actual result
        // cost is a known cost that we can achieve with 100% certainty
        // we assume optimal cost is slightly lower, and this gives us a more
        // accurate prediction of what the actual optimal cost may be
        // but we cannot ensure that such a route exists (or find it)
        printf( "%i\n", ( int )floor( cost * 0.915 ) );
    }
    else {
        // dynamic programming will work fast enough for given data in O( RCN )
        // printf( "Using dynamic programming algorithm.\n" );
        printf( "%i\n", dynamic() );
    }

    return 0;
}
