#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef unsigned long long int LL;

using namespace std;

int N;

void print( LL **result ) {
    for ( int i = 0; i < N; ++i ) {
        for ( int j = 0; j < N; ++j ) {
            printf( "%lli\t", result[ i ][ j ] );
        }
        printf( "\n" );
    }
    printf( "\n" );
}

void multiply( LL **result, LL **a, LL **b ) {
    for ( int i = 0; i < N; ++i ) {
        for ( int j = 0; j < N; ++j ) {
            result[ i ][ j ] = 0;
            for ( int k = 0; k < N; ++k ) {
                result[ i ][ j ] += a[ i ][ k ] * b[ k ][ j ];
            }
            result[ i ][ j ] = result[ i ][ j ] % 100000007;
        }
    }
}

void zero( LL ***a ) {
    *a = ( LL** )malloc( N * sizeof( LL* ) );
    for ( int i = 0; i < N; ++i ) {
        ( *a )[ i ] = ( LL* )malloc( N * sizeof( LL ) );
        memset( ( *a )[ i ], 0, N * sizeof( LL ) );
    }
}

void copy( LL **destination, LL **src ) {
    for ( int i = 0; i < N; ++i ) {
        for ( int j = 0; j < N; ++j ) {
            destination[ i ][ j ] = src[ i ][ j ];
        }
    }
}

void swap( LL ***a, LL ***b ) {
    LL **t = *a;
    *a = *b;
    *b = t;
}

void identity( LL **a ) {
    for ( int i = 0; i < N; ++i ) {
        for ( int j = 0; j < N; ++j ) {
            a[ i ][ j ] = i == j;
        }
    }
}

void power( LL ***result, LL **base, long int exponent ) {
    LL **temp;

    zero( &temp );
    identity( *result );

    while ( exponent ) {
        if ( exponent & 1 ) {
            multiply( temp, *result, base );
            swap( result, &temp );
        }
        multiply( temp, base, base );
        swap( &base, &temp );
        exponent >>= 1;
    }
}

int main() {
    int u, v, K, M, i, s, t, sum;
    LL **adjacency, **result;

    scanf( "%i %i %i %i %i", &K, &N, &M, &s, &t );
    --s; --t; --K;

    zero( &adjacency ); zero( &result );

    for ( i = 0; i < M; ++i ) {
        scanf( "%i %i", &u, &v );
        --u; --v;
        adjacency[ u ][ v ] = 1;
    }

    power( &result, adjacency, K );
    printf( "%lli\n", result[ s ][ t ] );

    return 0;
}
