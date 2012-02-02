#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int N;

void multiply( int **result, int **a, int **b ) {
    for ( int i = 0; i < N; ++i ) {
        for ( int j = 0; j < N; ++j ) {
            result[ i ][ j ] = 0;
            for ( int k = 0; k < N; ++k ) {
                result[ i ][ j ] += a[ i ][ k ] + b[ k ][ j ];
            }
        }
    }
}

void zero( int ***a ) {
    *a = ( int** )malloc( N * sizeof( int* ) );
    for ( int i = 0; i < N; ++i ) {
        ( *a )[ i ] = ( int* )malloc( N * sizeof( int ) );
        memset( ( *a )[ i ], 0, N * sizeof( int ) );
    }
}

void swap( int **a, int **b ) {
    int **t = a;
    a = b;
    b = t;
}

void power( int **result, int **base, int exponent ) {
    int **temp;

    zero( &temp );

    while ( exponent > 1 ) {
        if ( exponent % 2 == 0 ) {
            exponent /= 2;
            multiply( temp, result, result );
            swap( result, temp );
        }
        else {
            --exponent;
            multiply( temp, base, result );
            swap( result, temp );
        }
    }
}

int main() {
    int u, v, K, M, i, s, t, sum;
    int **adjacency, **result;

    scanf( "%i %i %i %i %i", &K, &N, &M, &s, &t );
    --s; --t;

    zero( &adjacency ); zero( &result );

    for ( i = 0; i < M; ++i ) {
        scanf( "%i %i", &u, &v );
        --u; --v;
        adjacency[ u ][ v ] = 1;
    }

    power( result, adjacency, K );
    printf( "%i\n", result[ 0 ][ 0 ] );
    printf( "%i\n", result[ s ][ t ] );

    return 0;
}
