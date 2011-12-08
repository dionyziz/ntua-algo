#include<cstdio>
#include<stack>

const int N = 8;
using namespace std;

int main() {
    int A[ N + 1 ] = { 10000, 8, 13, 10, 6, 3, 5, 8, 2 };
    int B[ N + 1 ];
    stack< int > bullets;
    int bullet;

    for ( int i = N; i >= 1; --i ) {
        B[ i ] = 0;
    }
    for ( int i = N; i >= 1; --i ) {
        while ( !bullets.empty() ) {
            bullet = bullets.top();
            if ( A[ bullet ] < A[ i ] ) {
                B[ bullet ] = i;
                bullets.pop();
            }
            else {
                break;
            }
        }
        bullets.push( i );
    }
    printf( "Array B: " );
    for ( int i = 1; i <= N; ++i ) {
        printf( "%i ", B[ i ] );
    }
    printf( "\n" );

    return 0;
}
