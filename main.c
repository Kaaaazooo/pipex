/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 14:26:42 by sabrugie          #+#    #+#             */
/*   Updated: 2021/05/29 15:09:39 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_strtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i++] = NULL;
	}
	free(tab);
	tab = NULL;
}

char	*get_path(char **envp)
{
	int		i;
	int		j;
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

void	getcmd(char *args, char **env)
{
	char		*tmp;
	char		**paths;
	char		**strs;
	int			i;

	paths = ft_split(get_path(env), ':');
	strs = ft_split(args, ' ');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = tmp;
		tmp = ft_strjoin(paths[i], *strs);
		execve(tmp, strs, env);
		if (errno != ENOENT)
			perror("pipex:");
		free(tmp);
		++i;
	}
	write(STDERR_FILENO, "pipex: command not found : ",
		ft_strlen("pipex: command not found : "));
	dprintf(STDERR_FILENO, "%s\n", *strs);
	free_strtab(paths);
	free_strtab(strs);
}

int	pipe_loop(int pd[2], int ac, char **av, char **envp)
{
	int	i;
	int	pid;
	int	fd;

	i = 3;
	while (i < ac - 2)
	{
		pipe(pd);
		pid = fork();
		if (!pid)
		{
			dup2(pd[1], 1);
			getcmd(av[i], envp);
		}
		dup2(pd[0], 0);
		close(pd[1]);
		i++;
	}
	fd = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		perror("pipex");
	return (fd);
}

int	main(int ac, char **av, char **envp)
{
	int		fd;
	int		pd[2];

	if (ac < 5)
		return (-1);
	fd = open(av[1], O_RDONLY);
	pipe(pd);
	if (!fork())
	{
		dup2(pd[1], 1);
		dup2(fd, 0);
		getcmd(av[2], envp);
	}
	dup2(pd[0], 0);
	close(pd[1]);
	close(fd);
	pipe_loop(pd, ac, av, envp);
	if (!fork())
	{
		dup2(fd, 1);
		getcmd(av[ac - 2], envp);
	}
	close(fd);
	return (0);
}
