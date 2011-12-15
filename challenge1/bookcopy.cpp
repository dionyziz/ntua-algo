#include <cstdio>

using namespace std;

int A[ 100000 ];

int main() {
    int N, K;
    int low, high, solution;
    int max = 0, sum = 0;
    bool invalid;

    scanf( "%i %i", &N, &K );

    for ( int i = 0; i < N; ++i ) {
        scanf( "%i", &A[ i ] );
        sum += A[ i ];
        if ( A[ i ] > max ) {
            max = A[ i ];
        }
    }
    low = max - 1;
    high = sum;

    bool valid;

    while ( high - low > 1 ) {
        solution = ( high + low ) / 2;
        valid = true;
        sum = 0;
        for ( int i = 0, j = 0; i < N; ++i ) {
            sum += A[ i ];
            if ( sum > solution ) {
                sum = A[ i ];
                ++j;
                if ( j >= K ) {
                    low = solution;
                    valid = false;
                    break;
                }
            }
        }
        if ( valid ) {
            high = solution;
        }
    }

    printf( "%i\n", high );

    return 0;
}
