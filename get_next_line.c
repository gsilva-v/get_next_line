/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:04:06 by gabriel           #+#    #+#             */
/*   Updated: 2021/09/14 11:58:43 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_readleftstr(int fd, char *left_str)
{
	char	*buffer;
	int		read_byte;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	read_byte = 1;
	while (!ft_strchr(left_str, '\n') && read_byte != 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1 )
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_byte] = '\0';
		left_str = ft_strjoin(left_str, buffer);
	}	
	free(buffer);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left_str = ft_readleftstr(fd, left_str);
	if (!left_str)
		return (NULL);
	line = ft_line(left_str);
	left_str = ft_newleft(left_str);
	if (line[0] == '\0')
	{
		free(left_str);
		free(line);
		return (NULL);
	}
	return (line);
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*line;
	int		i;
//	int		fd1;
	int		fd2;
//	int		fd3;
//	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
//	fd3 = open("test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
//		line = get_next_line(fd1);
//		printf("line [%02d] test1: %s", i, line);
//		free(line);
		line = get_next_line(fd2);
		printf("line [%02d] test2: %s", i, line);
//		free(line);
//		line = get_next_line(fd3);
//		printf("line [%02d] test2: %s", i, line);
		free(line);
		i++;
	}
//	close(fd1);
	close(fd2);
//	close(fd3);
	return (0);
}