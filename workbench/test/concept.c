#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

int	main(int argc, char **argv)
{
	int	fd1[2];
	int	fd2[2];
	int	status;
	int	pid;

	pipe(fd1);
	pid = fork();
	if (pid == 0) // hijo 1
	{
		close(fd1[READ_END]);
		dup2(fd1[WRITE_END], STDOUT_FILENO);
		close(fd1[WRITE_END]);
		execlp("/bin/ls/", "ls", "-l", NULL);
	}
	else // padre
	{
		close(fd1[WRITE_END]);
		pipe(fd2);
		pid = fork();
		if (pid == 0) // hijo 2
		{
			close(fd2[READ_END]);

			dup2(fd1[READ_END], STDIN_FILENO);
			close(fd1[READ_END]);

			dup2(fd2[WRITE_END], STDOUT_FILENO);
			close(fd2[WRITE_END]);
			execlp("/bin/grep/", "grep", "u", NULL);
		}
		else
		{
			close(fd1[READ_END]);
			close(fd2[WRITE_END]);

			pid = fork();
			
			if (pid == 0) //hijo 3
			{
				dup2(fd2[READ_END], STDIN_FILENO);
				close(fd2[READ_END]);

				execl("/usr/bin/wc", "wc", "-l", NULL);
			}
		}
	}
	close(fd2[READ_END]); //cerrar extremo 

	wait(&status);
	wait(&status);
	wait(&status);

	return (0);
}
