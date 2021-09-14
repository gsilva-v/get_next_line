/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:03:50 by gabriel           #+#    #+#             */
/*   Updated: 2021/09/14 14:25:49 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*left_str[OPEN_MAX];//a unica diferença entre o bonus e a original, é que ao inves de criarmos um unico array, será criado uma matriz
//o valor definido por openmax, sera a quantidade de arquivos que podem ser abertos ao mesmo tempo
	line = NULL;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	left_str[fd] = ft_readleftstr(fd, left_str[fd]);
	if (!left_str[fd])
		return (NULL);
	line = ft_line(left_str[fd]);
	left_str[fd] = ft_newleft(left_str[fd]);
	if (line[0] == '\0')
	{//nesse caso, caso algo de errado, nao podemos liberar a memoria toda da matriz, entao podemos liberar so a linha atual
		free(line);
		return (NULL);
	}
	return (line);
}
