#include <cstdio>
#include <map>

using namespace std;

int main() {
    int N, C, a, len, maxlen = 0;
    int sigma = 0, maxsigma = 0;
    map< int, int > exclude;

    exclude[ 0 ] = 0;
    scanf( "%i %i", &N, &C );
    for ( int i = 1; i <= N; ++i ) {
        scanf( "%i", &a );
        sigma -= a - C;
        if ( sigma > maxsigma ) {
            maxsigma = sigma;
            exclude[ sigma ] = i;
        }
        else {
            len = i - ( *exclude.lower_bound( sigma ) ).second;
            if ( len > maxlen ) {
                maxlen = len;
            }
        }
    }
    printf( "%i\n", maxlen );

    return 0;
}
