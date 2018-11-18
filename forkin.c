#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
	printf("Hello from the parent!\n");
	for (int i = 0; i < 2; i++) {
		printf("Starting %s process\n", (i == 0) ? "first": "second");
		int processID = fork();
		if (!processID) { 
			// runs if not parent
			int fd = open("/dev/random", O_RDONLY);
			int * randomSeconds = malloc(sizeof(int));
			read(fd, randomSeconds, sizeof(int));
			(*randomSeconds) = abs(((*randomSeconds)) % 16) + 5;
			printf("Child with id: %d is sleeping for %d seconds. Be quiet!\n", getpid(), *randomSeconds);
			sleep(*randomSeconds);
			printf("Child with id: %d has woken up!\n", getpid());
            // allow parent to get how long the child slept for
			exit(*randomSeconds);
		}
	}
	int status = -1;
	int processId = wait(&status);
	printf("My favorite child has the id of %d because he only slept for %d seconds\n", processId, WEXITSTATUS(status));
	printf("My other child will wake up soon but I (the parent) am done\n");
	return 0;
}