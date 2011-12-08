#include <cstdio>

int cnt = 0;

int max( int a, int b ) {
    if ( a > b ) {
        return a;
    }
    return b;
}
int min( int a, int b ) {
    if ( a < b ) {
        return a;
    }
    return b;
}

int get( int* A, int i ) {
    return A[ i - 1 ];
}

void print( int* A, int low, int N ) {
    for ( int i = 0; i < N; ++i ) {
        printf( "%i ", get( A, low + i ) );
    }
    printf( "\n" );
}

int kth2( int* A, int lowA, int* B, int lowB, int k ) {
    int midA = ( 2 * lowA + k - 1 ) / 2;
    int midB = ( 2 * lowB + k - 1 ) / 2;

    if ( ++cnt > 10 ) {
        printf( "Stack overflow\n" );
        return 0;
    }

    printf( "Looking for the %i-th element:\n", k );
    print( A, lowA, k );
    print( B, lowB, k );

    if ( k == 1 ) {
        return min( get( A, lowA ), get( B, lowB ) );
    }
    k /= 2;
    if ( get( A, midA ) < get( B, midB ) ) {
        return kth2( A, midA + 1, B, lowB, k );
    }
    return kth2( A, lowA, B, midB + 1, k );
}

int kth( int* A, int* B, int N, int k ) {
    N = min( N, k );
    return kth2( A, 1, B, 1, k );
}

int main() {
    int A[ 5 ] = { 1, 2, 3, 4, 5 };
    int B[ 5 ] = { -1, 7, 8, 9, 10 };
    int k = 2;
    int N = 5;

    printf( "%i-th element is: %i\n", k, kth( A, B, N, k ) );

    return 0;
}
