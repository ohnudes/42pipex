
# include "test.h"


static void	child_two(data_t *pdata, pipecon_t *pipes, char **envp)
{
	dup2(pipes->fd[1], WRITE_END);
	close
	execve(*pdata->rawcmd[0], pdata->cmd_path, envp);
}

static void	child_one(data_t *pdata, pipecon_t *pipes, char **envp)
{
	dup2(pipes->fd[0], READ_END);
	execve(*pdata->rawcmd[0], pdata->cmd_path, envp);
}

int	body(data_t *pdata, pipecon_t *pipes, char **envp)
{
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (pipe(pipes->fd) == -1)
		return (exit_ctl(pdata, pipes, 3));
	child1 = fork();
	if (child1 == -1)
		return (exit_ctl(pdata, pipes, 4));
	if (child1 == 0)
		child_one(pdata, pipes, envp);
	child2 = fork();
	if (child2 == -1)
		return (exit_ctl(pdata, pipes, 5));
	if (child2 == 0)
		child_two(pdata, pipes, envp);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	data_t		pathdata;
	pipecon_t	pipes;

	pathdata = (data_t){};
	pipes = (pipecon_t){};
	if (init_path(&pathdata, argv, envp) == -1)
		return (exit_ctl(&pathdata, &pipes, 1));
	if (cmd_check(&pathdata, pathdata.rawcmd) == -1)
		return (exit_ctl(&pathdata, &pipes, 1));
	if (init_pipe_values(&pipes, argc, argv) == -1)
		return (exit_ctl(&pathdata, &pipes, 2));
	if (body(&pathdata, &pipes, envp) == -1)
	{

	}
	exit_ctl(&pathdata, &pipes, 3);
	return (0);
}
