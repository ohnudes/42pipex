
#include "test.h"

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
