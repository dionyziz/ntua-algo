#include <cstdio>

using namespace std;

inline int min( int a, int b ) {
    return a < b? a: b;
}

int main() {
    int N, K, i, j;
    int B[ 10000 ], C[ 10000 ], J[ 10000 ], JS[ 10000 ];

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
    }

    JS[ K ] = 0;
    for ( i = K - 1; i >= 1; --i ) {
        JS[ i ] = J[ i + 1 ] + C[ i ];
        for ( j = i; j <= K; ++j ) {
            J[ i ] = min( J[ i ], JS[ j ] + B[ i ] * ( j - i ) );
        }
    }
    printf( "%i\n", J[ 0 ] );

    return 0;
}
