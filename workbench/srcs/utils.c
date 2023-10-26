
#include "../include/pipex.h"
#include <stdlib.h>

int	err_msg(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

char	**free_dchar(char **ptr)
{
	char	**ref;
	char	**head;

	ref = NULL;
	head = ptr;
	ptr++;
	while (*ptr)
	{
		if (ptr + 1 != NULL)
			ref = ptr + 1;
		free(*ptr);
		ptr = ref;
	}
	free (ptr);
	return (NULL);
}
