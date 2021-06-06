/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:54:47 by sabrugie          #+#    #+#             */
/*   Updated: 2021/06/06 17:40:30 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_error(char *error, char *arg)
{
	int		i;
	char	buf[8096];

	i = 0;
	while (i < 8096)
		buf[i++] = 0;
	ft_strcpy(buf + ft_strlen(buf), "pipex: ");
	ft_strcpy(buf + ft_strlen(buf), error);
	ft_strcpy(buf + ft_strlen(buf), ": ");
	ft_strcpy(buf + ft_strlen(buf), arg);
	ft_strcpy(buf + ft_strlen(buf), "\n");
	write(STDERR_FILENO, buf, ft_strlen(buf));
}

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
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd >= 0 && !close(fd))
	{
		if (execve(file, cmd, env) < 0)
		{
			if (errno == ENOEXEC || errno == EACCES)
				pipex_error(strerror(errno), *cmd);
			else
				perror("pipex");
			exit(errno);
		}
	}
	return (0);
}

int	cmd_not_found(char *str, char ***paths, char ***strs)
{
	pipex_error("command not found", str);
	free_strtab(*paths);
	free_strtab(*strs);
	exit(127);
}
