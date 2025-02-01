#ifndef PIPEX_H
#define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>


char	**ft_split(char const *s, char c);
size_t  ft_strlen(const char *s);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
#endif