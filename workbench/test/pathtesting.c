
#include <stdio.h>
#include "../libft/includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && s1[i] == s2[i] && s2[i] != 0)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*get_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

int	main(int ac, char *av[], char *env[])
{
	char	*rawpath;
	char	**paths;

	rawpath = get_path(env);
	printf("get_path:\n%s\n", rawpath);
	paths = ft_split(rawpath, ':');

	return (0);
}
