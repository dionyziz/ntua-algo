#include <cstdio>
#include <cstdlib>

using namespace std;

struct field {
    int value;
    int x;
    int y;
};
bool B[ 4 ][ 10000 ];
int N;

int cmp( const void* a, const void* b ) {
    return ( ( const field* )b )->value - ( ( const field* )a )->value;
}

bool taken( int x, int y ) {
    if ( ( y + 1 < 4  && B[ y + 1 ][ x ] )
      || ( y - 1 >= 0 && B[ y - 1 ][ x ] )
      || ( x + 1 < N  && B[ y ][ x + 1 ] )
      || ( x - 1 >= 0 && B[ y ][ x - 1 ] ) ) {
        return true;
    }
    return false;
}

int main() {
    field A[ 40000 ];
    int x, y, k = 0, profit = 0;

    scanf( "%i", &N );

    for ( x = 0; x < N; ++x ) {
        for ( y = 0; y < 4; ++y ) {
            scanf( "%i", &A[ k ].value );
            A[ k ].x = x;
            A[ k ].y = y;
            B[ y ][ x ] = false;
            ++k;
        }
    }

    qsort( A, 4 * N, sizeof( field ), cmp );

    for ( k = 0; k < 4 * N; ++k ) {
        if ( !taken( A[ k ].x, A[ k ].y ) ) {
            profit += A[ k ].value;
            B[ A[ k ].y ][ A[ k ].x ] = true;
        }
    }
    printf( "%i\n", profit );

    return 0;
}
