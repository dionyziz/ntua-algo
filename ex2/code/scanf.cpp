#include <cstdio>
#include <cstring>

using namespace std;

int main() {
    char W[ 100 ];

    while ( scanf( "%s", &W ) != EOF ) {
        printf( "Read word %i characters wide.\n", strlen( W ) );
    }
    return 0;
}
