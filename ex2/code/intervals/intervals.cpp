#include <cstdio>
#include <cstdlib>

using namespace std;

struct interval {
    int s;
    int f;
    bool covered;
};
int N;
interval A[ 100000 ];

bool cover( s1, f1, s2, f2 ) {
    return ( s1 < s2 && f1 > s2 )
        || ( s2 < s1 && f2 > s1 );
}

int cmp( const void* a, const void* b ) {
    return ( ( const interval* )a )->f - ( ( const interval* )b )->f;
}

int main() {
    int cost;

    scanf( "%i", &N );
    for ( int i = 0; i < N; ++i ) {
        scanf( "%i %i", &A[ i ].s, &A[ i ].f );
        A[ i ].covered = false;
    }

    qsort( A, N, sizeof( interval ), cmp );

    for ( int i = 0; i < N; ++i ) {
        // printf( "%i %i\n", A[ i ].s, A[ i ].f );
        for ( int j = N - 1; j >= 0; --j ) {
            if ( cover( i, j ) ) {
                for ( int k = 0; k <= N; ++k ) {
                    A[ k ].covered = true;
                }
                break;
            }
        }
    }

    printf( "%i\n", cost );
    return 0;
}
