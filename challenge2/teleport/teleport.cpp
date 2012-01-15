#include <cstdio>
#include <cstdlib>

using namespace std;

#define MIN(a,b)  ((a) < (b) ? (a) : (b))
#define MAX(a,b)  ((a) > (b) ? (a) : (b))

struct arrow {
    int s;
    int f;
};

int cmp( const void* a, const void* b ) {
    return ( ( arrow* )a )->s - ( ( arrow* )b )->s;
}

int main() {
    int N;
    arrow A[ 500010 ];
    int max = 0;
    int J[ 500010 ];

    scanf( "%i", &N );
    for ( int i = 0; i < N; ++i ) {
        scanf( "%i %i", &A[ i ].s, &A[ i ].f );
    }
    qsort( A, N, sizeof( arrow ), cmp );
    for ( int i = 0; i < N; ++i ) {
        int x = A[ i ].f;
        int low = 0, high = i;
        int j;

        while ( low != high ) {
            mid = ( low + high ) / 2;
            if ( J[ mid ] > x ) {
                high = mid - 1;
            }
            else if ( J[ mid ] <= x ) {
                low = mid;
            }
        }
        j = low;
        max = MAX( j + 1, max );
        J[ j + 1 ] = MIN( x, J[ j + 1 ] );
    }
    printf( "%i\n", max );

    return 0;
}
