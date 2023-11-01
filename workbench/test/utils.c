
#include "test.h"

int	exit_ctl(data_t *pathdata, pipecon_t *pipes, int code)
{
	t_exitcode	exit_type[end];
	int			exitvalue;

	exitvalue = 0;
	exit_mem(pathdata);
	exit_fd(pipes);
	exitvalue = exit_type[code];
	return (exitvalue);
}

void	exit_fd(pipecon_t *pipes)
{
	size_t	i;

	i = 0;
	while (i < 2)
	{
		close(pipes->ft[i]);
		i++;
	}
}

void	exit_mem(data_t *pdata)
{
	size_t	i;

	i = 0;
	if (pdata->paths)
	{
		free_vec(pdata->paths);
		pdata->paths = NULL;
	}
	while (i < 2)
	{
		if (pdata->rawcmd[i])
		{
			free_vec(pdata->rawcmd[i]);
			pdata->rawcmd[i] = NULL;
		}
		if (pdata->cmd_path[i])
		{
			free(pdata->cmd_path[i]);
			pdata->cmd_path[i] = NULL;
		}
		i++;
	}
}

void	free_vec(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	while (i)
	{
		i--;
		free(str[i]);
	}
	free(str);
}

void	print_vec(char	**str, char *msg)
{
	size_t	i;
	i = 0;
	while (str[i])
	{
		printf("%s	%p	%s\n\n", msg, str, str[i]);
		i++;
	}
}
