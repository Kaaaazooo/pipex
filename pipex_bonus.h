#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "utils.h"

char	**ft_split(char const *s, char c);
int		try_open(char *filename, int oflag, mode_t mode);
void	free_strtab(char **tab);
int		try_exec(char *file, char **cmd, char **env);
int		cmd_not_found(char *str, char ***paths, char ***strs);

#endif
