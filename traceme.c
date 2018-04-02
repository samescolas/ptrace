#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int function( char * a )
{

    char buffer[1024];
    int ic;
	int i;
    int m;

    printf("Entered %s\n", __FUNCTION__ );

    m = open( a, O_RDONLY );

	i = 0;

    while( read( m, buffer, sizeof(buffer) ) > 0 ) 
    {
          printf("%s", buffer );
    }


    printf("LEAVING %s\n", __FUNCTION__ );
    return 0; 

}


int main ( int argc, char ** argv ) 
{

    printf("My pid..%d\n", getpid() );


    printf("Press any key to continue...\n");
    getchar();

    function( argv[1] );


    return 0;

}      
