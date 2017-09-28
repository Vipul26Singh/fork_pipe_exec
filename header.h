#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DUP2CLOSE(oldfd, newfd) (dup2(oldfd, newfd) == 0  &&  close(oldfd) == 0)

#ifndef TRUE
#  define TRUE 1
#endif

#ifndef FALSE
#  define FALSE 0
#endif

#define DUP2CLOSE(oldfd, newfd) (dup2(oldfd, newfd) == 0  &&  close(oldfd) == 0)


int **childReadParentWrite;
int **childWriteParentRead;

int remap_pipe_stdin_stdout(int rpipe, int wpipe)
{
        if ( rpipe == 0  &&  wpipe == 1 )
                return TRUE;

        if ( rpipe >= 1  &&  wpipe > 1 )
        {
                return DUP2CLOSE(rpipe, 0)
                    && DUP2CLOSE(wpipe, 1);
        }


        if ( rpipe == 0  &&  wpipe >= 1 )
                return DUP2CLOSE(wpipe, 1);

        if ( rpipe  >= 1  &&  wpipe == 1 )
                return DUP2CLOSE(rpipe, 0);


        if ( rpipe >= 1   &&  wpipe == 0 )
        {
                return DUP2CLOSE(wpipe, 1)
                    && DUP2CLOSE(rpipe, 0);
        }

        if ( rpipe == 1  &&  wpipe == 0 )
        {
        const int tmp = dup(wpipe);

                return  tmp > 1
                    &&  close(wpipe)   == 0
                    &&  DUP2CLOSE(rpipe, 0)
                    &&  DUP2CLOSE(tmp,   1);
        }

        return  FALSE;
}

