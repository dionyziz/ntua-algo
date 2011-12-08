#include <cstdio>
#include <set>
#include <cmath>

using namespace std;

int ask( int i, int j ) {
    int bitmask = pow( 2, j - 1 );
    return ( i & bitmask ) > 0;
}

void printCandidates( set< int > c ) {
    for ( set< int >::iterator i = c.begin(); i != c.end(); ++i ) {
        for ( int j = 4; j >= 1; --j ) {
            printf( "%i", ask( *i, j ) );
        }
        printf( "\n" );
    }
}

int main() {
    set< int > c;
    set< int > c0;
    set< int > c1;
    int result = 0;
    int x;
    int n = 16;

    for ( int i = 0; i < n; ++i ) {
        if ( i != 6 ) {
            c.insert( i );
        }
    }
    printCandidates( c );

    for ( int j = 4; j >= 2; --j ) {
        x = 0;
        c0.clear();
        c1.clear();
        for ( set< int >::iterator i = c.begin(); i != c.end(); ++i ) {
            if ( ask( *i, j ) == 1 ) {
                c1.insert( *i );
                x = !x;
            }
            else {
                c0.insert( *i );
            }
        }
        if ( x == 1 ) {
            c = c1;
            result += pow( 2, j - 1 );
        }
        else {
            c = c0; 
        }
        printf( "\nCandidates:\n" );
        printCandidates( c );
    }
    result += 1 - ask( *( c.begin() ), 1 );
    printf( "%i\n", result );
    return 0;
}
