#include "header.h"

int main(int argc, char *argv[]) {
	int link[2], fd[2];
	pid_t pid;
	char str[4096] = "";	
	char buf[] = "Parent rockled\n";
	FILE *fp;
	if(pipe(fd)){
		perror("pipe");
		return -1;
	}

	pipe(link);

	//remap_pipe_stdin_stdout(fd[0], fd[1]);
	//remap_pipe_stdin_stdout(link[0], link[1]);
	switch(fork()){
		case -1:
			perror("fork");
			return -1;
		case 0:
			// child
			dup2(link[1], STDOUT_FILENO);
			close(link[1]);
			close(link[0]);

			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);

			execl("./child", "./child", (char *)0);
		default:
			fp = fopen("parent.txt", "w");

			write(fd[1], buf, sizeof(buf));

			read(link[0], str, sizeof(str));
			fprintf(fp, "Pipe contents: %s\n", str);
			wait(NULL);
	}
	printf("END~\n");
	return 0;
} 
