/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 14:26:42 by sabrugie          #+#    #+#             */
/*   Updated: 2021/06/06 17:22:48 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env)
{
	int		i;
	char	find[6];

	i = 0;
	ft_strcpy(find, "PATH=");
	while (env[i])
	{
		if (ft_strncmp(find, env[i], 5) == 0)
			return (env[i] + 6);
		++i;
	}
	return (NULL);
}

char	*joinpath_to_file(char *path, char *filename)
{
	char	*file;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (tmp == NULL)
		return (NULL);
	file = ft_strjoin(tmp, filename);
	free(tmp);
	if (file == NULL)
		return (NULL);
	return (file);
}

int	getcmd(char *args, char **env)
{
	char	*tmp;
	char	**paths;
	char	**strs;
	int		i;

	paths = ft_split(get_path(env), ':');
	if (paths == NULL)
		exit(1);
	strs = ft_split(args, ' ');
	if (strs == NULL)
		exit(errno);
	i = 0;
	while (paths[i])
	{
		tmp = joinpath_to_file(paths[i], *strs);
		if (tmp == NULL || try_exec(tmp, strs, env))
			exit(errno);
		free(tmp);
		++i;
	}
	if (!paths[i])
		cmd_not_found(*strs, &paths, &strs);
	free_strtab(paths);
	free_strtab(strs);
	exit(errno);
}

int	pipe_loop(int pd[2], int ac, char **av, char **env)
{
	int	i;
	int	fd;

	i = 2;
	while (++i < ac - 2)
	{
		pipe(pd);
		if (!fork())
		{
			dup2(pd[1], 1);
			getcmd(av[i], env);
		}
		dup2(pd[0], 0);
		close(pd[1]);
	}
	fd = try_open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (-1);
	if (!fork())
	{
		dup2(fd, 1);
		getcmd(av[ac - 2], env);
	}
	return (fd);
}

int	main(int ac, char **av, char **env)
{
	int	fd;
	int	pd[2];

	if (ac < 5)
	{
		ft_putdstr(STDERR_FILENO,
			"usage : ./pipex [input] [cmd1] ... [cmdN] [output]", 1);
		return (-1);
	}
	fd = try_open(av[1], O_RDONLY, 0);
	pipe(pd);
	if (fd >= 0)
	{
		if (!fork())
		{
			dup2(pd[1], 1);
			dup2(fd, 0);
			getcmd(av[2], env);
		}
	}
	dup2(pd[0], 0);
	close(pd[1]);
	close(fd);
	fd = pipe_loop(pd, ac, av, env);
	return (0);
}
