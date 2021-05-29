#include "pipex.h"

char	*get_path(char **envp)
{
	int	i;
	int	j;
	char	find[5];

	i = 0;
	strcpy(find, "PATH");
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			++j;
		if (strncmp(find, envp[i], j) == 0)
			return (envp[i] + j + 1);
		++i;
	}
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	char	**paths;

	i = 0;
	paths = ft_split(get_path(envp), ':');
	printf("paths :\n");
	while (paths[i])
		printf("%s\n", paths[i++]);
	return (0);
	i = 1;
	while (i < ac - 1)
	{
		int pd[2];
		pipe(pd);

		if (!fork()) {
			dup2(pd[1], 1); // remap output back to parent
			execlp(av[i], av[i], NULL);
			perror("exec");
			abort();
		}

		// remap output from previous child to input
		dup2(pd[0], 0);
		close(pd[1]);
		i++;
	}
	execlp(av[i], av[i], NULL);
	perror("exec");
	abort();
	return (0);
}
