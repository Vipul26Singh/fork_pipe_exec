#include "header.h"

int create_child(int childIndex){

	pid_t pid;
	char processNo[5];
	int link[2], fd[2];

	if(pipe(fd)){
                perror("pipe");
                return -1;
        }

	childReadParentWrite[childIndex][0] = fd[0];
        childReadParentWrite[childIndex][1] = fd[1];

	if(pipe(link)){
                perror("pipe");
                return -1;
        }

	childWriteParentRead[childIndex][0] = link[0];
	childWriteParentRead[childIndex][1] = link[1];


	pid = fork();
	switch(pid){
                case -1:
                        perror("fork");
                        return -1;
                case 0:
			sprintf(processNo, "%d", childIndex);
                        // child
                        dup2(link[1], STDOUT_FILENO);
                        close(link[1]);
                        close(link[0]);

                        close(fd[1]);
                        dup2(fd[0], STDIN_FILENO);
                        close(fd[0]);

                        execl("./child", "./child", processNo, NULL);
                default:
			return pid;
        }

	return -1;


}


int main(int argc, char *argv[]) {

	if(argc<2){
		printf("Prive number of child\n");
		return -1;
	}

	int link[2], fd[2];
	int childCount = atoi(argv[1]);	
	int r=childCount, c=2;
	int *pipeDescriptor[2];
	int *cid = NULL;
	FILE *fp = NULL;
	char str[4096] = "";
        char buf[100];

	cid = (int *)malloc(sizeof(int)*childCount);


        signal(SIGPIPE, SIG_IGN);


        childReadParentWrite = (int **)malloc(r * sizeof(int *));
        childWriteParentRead = (int **)malloc(r * sizeof(int *));

        for (int i=0; i<r; i++){
                 childReadParentWrite[i] = (int *)malloc(c * sizeof(int));
                 childWriteParentRead[i] = (int *)malloc(c * sizeof(int));
        }



	for (int i=0; i<childCount; i++){
		cid[i] = create_child(i);		

		if(cid[i] == -1){
			perror("fork failed:");
		}
	}

	fp = fopen("parent.txt", "w");
	for (int i=0; i<childCount; i++){
		if(cid[i]!=-1){
			sprintf(buf, "You_are_child_number_%d\n", i);
			write(childReadParentWrite[i][1], buf, sizeof(buf));

			read(childWriteParentRead[i][0], str, sizeof(str));
			fprintf(fp, "Pipe contents: %s\n", str);
			fflush(fp);
		}
	}

	wait(NULL);	
} 
