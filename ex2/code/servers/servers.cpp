#include <cstdio>

const int INFINITY = 10000;

using namespace std;

inline int min( int a, int b ) {
    return a < b? a: b;
}

int main() {
    int N, K, i, j, l, cost;
    int B[ 10000 ], C[ 10000 ];
    int J[ 10000 ], JS[ 10000 ], W[ 10000 ];

    scanf( "%i", &N );
    K = -1;
    for ( i = 1; i <= N; ++i ) {
        scanf( "%i %i", &B[ i ], &C[ i ] );
        if ( B[ i ] ) {
            K = i;
        }
    }
    if ( K == -1 ) {
        printf( "0\n" );
        return 0;
    }

    JS[ K ] = C[ K ];
    J[ K ] = C[ K ];
    W[ K ] = K;
    for ( i = K - 1; i >= 1; --i ) {
        JS[ i ] = J[ i + 1 ] + C[ i ];
        J[ i ] = INFINITY;
        for ( j = i; j <= W[ i + 1 ]; ++j ) {
            cost = JS[ j ];
            for ( l = i; l <= j; ++l ) {
                cost += B[ l ] * ( j - l );
                if ( cost >= J[ i ] ) {
                    break;
                }
            }
            if ( cost < J[ i ] ) {
                J[ i ] = cost;
                W[ i ] = j;
            }
        }
    }
    printf( "Minimized cost = %i\n", J[ 1 ] );
    printf( "Dynamic programming solution:\n" );
    for ( i = 1; i <= K; ++i ) {
        printf( "( %i, %i, %i ) ", J[ i ], JS[ i ], W[ i ] );
    }
    printf( "\nServer configuration:\n" );
    for ( i = W[ 1 ] + 1; i <= K; i = W[ i ] + 1 ) {
        printf( "%i ", i - 1 );
    }
    printf( "%i", K );
    printf( "\n" );

    return 0;
}
