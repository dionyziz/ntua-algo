#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

int checker[ 4 ];
int mus[] = { 0, 2, 4, 5, 9, 10 };
int musLen = sizeof( mus ) / sizeof( int );

inline int max( int a, int b ) {
    return a > b? a: b;
}

int cStar( int mui ) {
    int profit = 0;
    int mu = mus[ mui ];

    for ( int e = 0; e < 4; ++e ) {
        if ( ( 1 << e ) & mu ) {
            profit += checker[ e ];
        }
    }
    return profit;
}

int main() {
    int N, i, e, mui, mu2i, solution = 0;
    int J[ 5 ], JP[ 5 ];

    for ( mui = 0; mui < musLen; ++mui ) {
        JP[ mui ] = 0;
    }

    scanf( "%i", &N );
    for ( i = 0; i < N; ++i ) {
        for ( e = 0; e < 4; ++e ) {
            scanf( "%i", &checker[ e ] );
        }
        for ( mui = 0; mui < musLen; ++mui ) {
            J[ mui ] = 0;
            for ( mu2i = 0; mu2i < musLen; ++mu2i ) {
                if ( ( mus[ mui ] & mus[ mu2i ] ) == 0 ) {
                    J[ mui ] = max( J[ mui ], JP[ mu2i ] + cStar( mui ) );
                }
            }
        }
        for ( mui = 0; mui < musLen; ++mui ) {
            JP[ mui ] = J[ mui ];
        }
    }
    for ( mui = 0; mui < musLen; ++mui ) {
        solution = max( solution, J[ mui ] );
    }
    printf( "%i\n", solution );

    return 0;
}
