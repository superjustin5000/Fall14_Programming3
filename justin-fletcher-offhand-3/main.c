#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARGS 20
#define BUFSIZE 1024



//void usage(char* name) {
//	fprintf(stderr, "Usage: %s filename\n", name);
//}






int main(int argc, char* argv[]) {


	pid_t pid1, pid2;

	int fd, pp[2]; //// file descripter and pipe.

	char buf[BUFSIZE];
	
	//int n;

	//if (argc !=2) { 
		//usage(argv[0]);
		//exit(0);
	//}

	//fd = open(argv[1], O_RDONLY);

	//if (fd < 0) {
		//perror("open failed\n");
		//exit(-1);
	//}


	if (pipe(pp) < 0) {
		perror("pipe failed");
		exit(-1);
	}



	pid1 = fork();
	if (pid1 > 0) { //in parent... fork again to make another child.
		pid2 = fork();
	}

	if (pid1 < 0 || pid2 < 0) { ///error forking

		perror("fork failed\n");
		exit(-1);

	} 

	
	if (pid1 == 0) { //------------child process number 1
		

		printf("child process 1\n");
		//sleep(2);
		//printf("child done\n");
		
		


		dup2(pp[1], STDOUT_FILENO);


		close(pp[0]);
		/*
		// more prints to ensure that sorting is correct.
		printf("a\n");
		printf("z\n");
		printf("d\n");
		printf("b\n");
		*/
		execlp("/bin/ls", "ls", "-1", NULL);

		close(pp[1]);
		//return if exec fails.
		printf("exec of ls failed\n");
		exit(-1);
	} 


	if (pid2 == 0) { // ------------ child process number 2

		printf("child process 2\n");


		dup2(pp[0], STDIN_FILENO);
		//dup2(pp[1], c2c[1]); 
		close(pp[0]);
		close(pp[1]);



		execlp("sort", "sort", NULL);

		perror("exec failed\n");
		exit(-1);

	}


	if (pid1 != 0 && pid2 != 0) { // ------------------------parent process of both..


		//close(fd);

		wait(0);

		close(pp[0]);
		close(pp[1]);

		//while( ( n = read(pp[0], buf, BUFSIZE) ) > 0 ) {
		//	buf[n] = 0;
		//	printf("%s", buf);
		//}


		//close(pp[0]);

		//printf("parent\n");
		//sleep(5);
		printf("parent found that child is done\n");

		exit(0);

	}


	return 0;

}