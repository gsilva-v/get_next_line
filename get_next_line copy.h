#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>//malloc e free
# include <unistd.h>//write
# include <stddef.h>//size_t

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
size_t	ft_strlen(char *str);
char	*ft_line(char *left_str);
char	*ft_newleft(char *left_str);
char	*get_next_line(int fd);
char	*ft_readleftstr(int fd, char *left_str);
#endif
