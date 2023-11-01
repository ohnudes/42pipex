
# include "test.h"

void	cmd_check(data_t *pathdata, char **rawcmd[2])
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < pathdata->path_len)
	{
		pathdata->cmd_path[j] = ft_strjoin(pathdata->paths[i], *rawcmd[j]);
		if (access(pathdata->cmd_path[j], 0) == 0)
		{
			printf("cmd_check/cmd_path: valid	%p	%s\n", pathdata->cmd_path[j], pathdata->cmd_path[j]);
			j++;
			if (j == 2)
				return ;
			i = 0;
		}
		else
		{
			i++;
			free(pathdata->cmd_path[j]);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	data_t	pathdata;
	
	pathdata = (data_t){};
	init_path(&pathdata, argv, envp);
	cmd_check(&pathdata, pathdata.rawcmd);
	exit_mem(&pathdata);
	return (0);
}
