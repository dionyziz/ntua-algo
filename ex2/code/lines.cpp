#include <cstdio>
#include <cstring>

using namespace std;

const int INFINITY = 1000000;

int main() {
    int C;
    int L[ 10000 ];
    int J[ 10000 ];
    int K[ 10000 ];
    char W[ 10000 ][ 20 ];
    int cost;
    int i;

    scanf( "%i", &C );

    J[ 0 ] = 0;
    for ( i = 1; scanf( "%s", &W[ i ] ) != EOF; ++i ) {
        L[ i ] = strlen( W[ i ] );
        J[ i ] = INFINITY;
        cost = C + 1;
        for ( int j = i; j >= 1; --j ) {
            cost -= L[ j ] + 1;
            if ( cost < 0 ) {
                break;
            }
            if ( cost * cost + J[ j - 1 ] < J[ i ] ) {
                J[ i ] = cost * cost + J[ j - 1 ];
                K[ i ] = j - 1;
            }
        }
        // printf( "%i\n", J[ i ] );
    }
    --i;
    printf( "Minimized sum square error = %i\n", J[ i ] );
    for ( ; i > 0; i = K[ i ] ) {
        for ( int j = K[ i ] + 1; j <= i; ++j ) {
            printf( "%s ", W[ j ] );
        }
        printf( "\n" );
    }

    return 0;
}
