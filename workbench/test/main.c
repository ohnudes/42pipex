
# include "test.h"
#include <unistd.h>

static int	child_two(data_t *pdata, pipecon_t *pipes, char **envp)
{
	perror("childtwo checkpoint");
	dup2(pipes->fd[0], STDIN_FILENO);
	dup2(pipes->ft[1], STDOUT_FILENO);
	close(pipes->fd[1]);
	close(pipes->fd[0]);
	if (execve(pdata->cmd_path[1], pdata->rawcmd[1], envp) == -1)
		return (err_relay("child_one/execve == -1"));
	perror("child two success");
	exit(EXIT_SUCCESS);
}

static int	child_one(data_t *pdata, pipecon_t *pipes, char **envp)
{
	perror("childone checkpoint");
	dup2(pipes->ft[0], STDIN_FILENO);
	dup2(pipes->fd[1], STDOUT_FILENO);
	close(pipes->fd[0]);
	close(pipes->fd[1]);
	if (execve(pdata->cmd_path[0], pdata->rawcmd[0], envp) == -1)
		return (err_relay("child_one/execve == -1"));
	perror("child one success");
	exit(EXIT_SUCCESS);
}

int	body(data_t *pdata, pipecon_t *pipes, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipes->fd) == -1)
		return (err_relay("body/pipe(fd): pipe == -1"));
	pid1 = fork();
	if (pid1 == -1)
		return (err_relay("body/fork/pid1: pid1 == -1"));
	if (pid1 == 0)
		child_one(pdata, pipes, envp);
	pid2 = fork();
	if (pid2 == -1)
		return (err_relay("body/fork/pid2: pid2 == -1"));
	if (pid2 == 0)
		child_two(pdata, pipes, envp);
	close(pipes->fd[0]);
	close(pipes->fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	exit_ctl(pdata, pipes, EXIT_SUCCESS);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	data_t		pathdata;
	pipecon_t	pipes;

	if (argc != 5)
	{
		perror("argc count error");
		return (0);
	}
	pathdata = (data_t){};
	pipes = (pipecon_t){};
	if (init_path(&pathdata, argv, envp) == -1)
		return (exit_ctl(&pathdata, &pipes, "main/init_path/return value == -1"));
	if (cmd_check(&pathdata, pathdata.rawcmd) == -1)
		return (exit_ctl(&pathdata, &pipes, "main/cmd_check/return value == -1"));
	if (init_pipe_values(&pipes, argv) == -1)
		return (exit_ctl(&pathdata, &pipes, "main/init_pipe_values/return value == -1"));
	if (body(&pathdata, &pipes, envp) == -1)
		return (exit_ctl(&pathdata, &pipes, "main/body/return value == -1"));
	return (0);
}
