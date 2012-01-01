#include <cstdio>
#include <cstdlib>

const float EPSILON = 0.00001;

using namespace std;

struct span {
    int i;
    float u;
    float l;
};

int cmp( const void* a, const void* b ) {
    float d = ( ( const span* )a )->u - ( ( const span* )b )->u;

    if ( d > EPSILON ) {
        return 1;
    }
    if ( d < -EPSILON ) {
        return -1;
    }
    return 0;
}

int main() {
    int i, N;
    float v, u, T, t;
    span A[ 10000 ];

    scanf( "%i %f %f", &N, &v, &T );

    for ( i = 0; i < N; ++i ) {
        scanf( "%f %f", &A[ i ].l, &A[ i ].u );
        A[ i ].i = i;
    }
    qsort( A, N, sizeof( span ), cmp );
    for ( i = 0; i < N; ++i ) {
        u = v + A[ i ].u;
        t = A[ i ].l / u;
        if ( T > t ) {
            printf( "%i %2.2f\n", A[ i ].i, A[ i ].l );
            T -= t;
        }
        else {
            printf( "%i %2.2f\n", A[ i ].i, T * u );
            break;
        }
    }

    return 0;
}
