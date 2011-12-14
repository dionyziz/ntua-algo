#include <cstdio>

using namespace std;

int main() {
    int N, K;
    int A[ 10000 ];
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
    low = max;
    high = sum;

    bool valid;

    while ( low != high ) {
        solution = ( high + low ) / 2;
        valid = true;
        sum = 0;
        for ( int i = 0, j = 0; i < N; ++i ) {
            sum += A[ i ];
            if ( sum > solution ) {
                sum = A[ i ];
                ++j;
                if ( j > K ) {
                    low = solution + 1;
                    valid = false;
                    break;
                }
            }
        }
        if ( valid ) {
            high = solution;
        }
    }

    printf( "%i\n", low );

    return 0;
}
