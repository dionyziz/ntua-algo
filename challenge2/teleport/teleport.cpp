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
    return ( ( arrow* )a )->s - ( ( arrow* )b )->s;
}

int main() {
    int max = 0;

    scanf( "%i", &N );
    for ( int i = 0; i < N; ++i ) {
        scanf( "%i %i", &A[ i ].s, &A[ i ].f );
        J[ i + 1 ] = INF;
    }
    qsort( A, N, sizeof( arrow ), cmp );
    // LIS
    for ( int i = 0; i < N; ++i ) {
        int x = A[ i ].f;
        int mid, low = 1, high = i;
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

        max = MAX( j + 1, max );
        J[ j + 1 ] = MIN( x, J[ j + 1 ] );
    }
    printf( "%i\n", max );

    return 0;
}
