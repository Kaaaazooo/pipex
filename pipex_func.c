/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:54:47 by sabrugie          #+#    #+#             */
/*   Updated: 2021/06/06 15:56:43 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_strtab(char **tab)
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

int	try_open(char *filename, int oflag, mode_t mode)
{
	int	fd;

	if (oflag & O_CREAT)
		fd = open(filename, oflag, mode);
	else
		fd = open(filename, oflag);
	if (fd < 0)
	{
		ft_putdstr(STDERR_FILENO, "pipex: ", 0);
		ft_putdstr(STDERR_FILENO, strerror(errno), 0);
		ft_putdstr(STDERR_FILENO, ": ", 0);
		ft_putdstr(STDERR_FILENO, filename, 1);
	}
	return (fd);
}

int	try_exec(char *file, char **cmd, char **env)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd >= 0 && !close(fd))
	{
		if (execve(file, cmd, env) < 0)
		{
			if (errno == ENOEXEC || errno == EACCES)
			{
				ft_putdstr(STDERR_FILENO, "pipex: ", 0);
				ft_putdstr(STDERR_FILENO, strerror(errno), 0);
				ft_putdstr(STDERR_FILENO, ": ", 0);
				ft_putdstr(STDERR_FILENO, *cmd, 0);
				write(2, "\n", 1);
			}
			else
				perror("pipex");
			exit(errno);
		}
	}
	return (0);
}

int	cmd_not_found(char *str, char ***paths, char ***strs)
{
	ft_putdstr(STDERR_FILENO, "pipex: command not found: ", 0);
	ft_putdstr(STDERR_FILENO, str, 1);
	free_strtab(*paths);
	free_strtab(*strs);
	exit(127);
}
