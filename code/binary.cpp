#include <cstdio>
#define INFINITY 100000
#define N 11

using namespace std;

int data[ N ] = { -1, 2, 3, 5, 100, 291, 391, 1024, 2048, 9001, 10100 };

int get( int i ) {
    if ( i > N ) {
        return INFINITY;
    }
    return data[ i ];
}

int sizeUpperBound() {
    int high = 1;

    while ( get( high ) != INFINITY ) {
        high *= 2;
    }
    return high;
}

int binarySearch( int key, int low, int high ) {
    if ( low >= high ) {
        return -1;
    }
    int mid = ( low + high ) / 2;
    if ( key == get( mid ) ) {
        return mid;
    }
    if ( key < get( mid ) ) {
        return binarySearch( key, low, mid );
    }
    if ( key > get( mid ) ) {
        return binarySearch( key, mid + 1, high );
    }
}

int find( int k ) {
    return binarySearch( k, 1, sizeUpperBound() );
}

int main() {
    int k = 291;

    printf( "Found key at position: %i\n", find( k ) ) ;
    return 0;
}
