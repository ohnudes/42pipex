
#include <stdio.h>
#include "../libft/includes/libft.h"

char	*get_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

int	main(int ac, char **av, char *env[])
{
	char	*raw;
	char	**paths;
	char	**cmdarg;
	int		i;

	if (ac < 1 || ac > 5)
		return (1);
	raw = get_path(env);
	paths = ft_split(raw, ':');
	cmdarg = ft_split(av[2], ' ');
	i = 0;
	while (cmdarg[i])
	{
		printf("%p = %s\n", *(cmdarg + i), *(cmdarg + i));
		i++;
	}
	free(paths);
	free(cmdarg);
	return (0);
}
