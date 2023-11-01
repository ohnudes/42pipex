#include "test.h"

static char	*get_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4) && *env)
		env++;
	return (*env + 5);
}

static char	**fill_paths(char *raw, char **vector, size_t *path_len)
{
	char	*swp;
	size_t	i;
	size_t	j;
	
	i = 0;
	j = 0;
	vector = ft_split(raw, ':');
	if (!vector)
		return (NULL);
	while (vector[i])
	{
		swp = vector[i];
		j = ft_strlen(swp);
		if (swp[j - 1] != '/')
		{
			vector[i] = ft_strjoin(vector[i], "/");
			free(swp);
		}
		i++;
	}
	*path_len = i;
	return (vector);
}

void	init_path(data_t *pdata, char **av, char **env)
{
	char	*tmp;
	tmp = get_path(env);
	if (tmp)
	{
		pdata->paths = fill_paths(tmp, pdata->paths, &pdata->path_len);
		if (pdata->paths)
		{
			//print_vec(pdata->paths, "init_paths/paths");
			pdata->rawcmd[0] = ft_split(av[2], ' ');
			//print_vec(pdata->rawcmd[0], "init_paths/rawcmd[0]");
			if (pdata->rawcmd[0])
			{
				pdata->rawcmd[1] = ft_split(av[3], ' ');
				//print_vec(pdata->rawcmd[1], "init_paths/rawcmd[1]");
				return ;
			}
		}
	}
	exit_mem(pdata);
}
