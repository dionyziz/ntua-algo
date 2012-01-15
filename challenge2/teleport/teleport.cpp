#include <cstdio>
#include <cstdlib>

using namespace std;

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

const int INF = 987654321;

struct arrow {
    int s;
    int f;
};

int N;
arrow A[ 500010 ];
int J[ 500010 ];

int cmp( const void* a, const void* b ) {
    arrow* one = ( arrow* )a;
    arrow* two = ( arrow* )b;

    int s = one->s - two->s;
    if ( s != 0 ) {
        return s;
    }
    return one->f - two->f;
}

int printJ( int i ) {
    printf( "Cost function after %i-th induction step:\n", i );

    for ( int j = 1; j <= i; ++j ) {
        printf( "J[ %i ] = %i\n", j, J[ j ] );
    }
}

int main() {
    int max = 0;

    scanf( "%i", &N );
    J[ 0 ] = -1;
    for ( int i = 1; i <= N; ++i ) {
        scanf( "%i %i", &A[ i ].s, &A[ i ].f );
        J[ i ] = INF;
    }
    qsort( A + 1, N, sizeof( arrow ), cmp );
  //  for ( int i = 0; i < N; ++i ) {
  //      printf( "( %i, %i )\n", A[ i ].s, A[ i ].f );
  //  }
  //  printf( "\n" );
    // LIS
    for ( int i = 1; i <= N; ++i ) {
        int x = A[ i ].f;
        int mid, low = 0, high = i;
        int j;

        // binary search
        while ( low < high - 1 ) {
            mid = ( low + high ) / 2;
            if ( J[ mid ] > x ) {
                high = mid;
            }
            else {
                low = mid;
            }
        }
        j = 0;
        if ( low == high - 1 ) {
            j = low;
        }
        // printf( "Updating item %i\n", j );

        max = MAX( j + 1, max );
        J[ j + 1 ] = MIN( x, J[ j + 1 ] );

        // printJ( i );
    }
    printf( "%i\n", max );

    return 0;
}
