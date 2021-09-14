/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:04:06 by gabriel           #+#    #+#             */
/*   Updated: 2021/09/14 14:01:47 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_readleftstr(int fd, char *left_str)//função que irá a linha passada
{
	char	*buffer;
	int		read_byte;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));//alocamos memoria a depender do tamanho do buffer passado
	if (!buffer)
	{
		free(buffer);
		return (NULL);//caso alguma coisa de errado na alocação, retornar nulo
	}
	read_byte = 1;// a quantidade de bytes pode ser definida inicialmente como qualquer valor, ja que sera modificada a cada vez que o loop concluir um ciclo
	while (!ft_strchr(left_str, '\n') && read_byte != 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);// vamos verificar a primeita quantidade de bytes que foram lidos
		if (read_byte == -1 )//caso a função read de algum erro, por padrão seu retorno será -1, entao paramos nosso programa
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_byte] = '\0';// colocamos o byte nulo ao final do buffer para usarmos a função que ira concatenar as strings
		left_str = ft_strjoin(left_str, buffer);
	}//esse loop acontecera durante toda a primeira linha texto passado
	free(buffer);//liberamos o buffer para que nao ocorra nenhum vazamento de memória posteriormente
	return (left_str);// retornamos a linha que acabou de ser lida
}

char	*get_next_line(int fd)//aqui a função principal
{
	char		*line;
	static char	*left_str;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)//caso algum parametro seja invalido, nosso programa ira terminar 
		return (NULL);
	left_str = ft_readleftstr(fd, left_str);//verificamos se há alguma coisa para ser lida e se o file descriptor é valido
	if (!left_str)
		return (NULL);
	line = ft_line(left_str);//atribuimos a primeira linha que foi lida nessa variável, ela será nosso retorno
	left_str = ft_newleft(left_str);//aqui salvamos a posição que paramos de ler, para que no loop do main, continue o programa daqui
	if (line[0] == '\0')//garantimos que nao aja vazamento de memoria caso a linha atual não contenha nada escrito
	{
		free(left_str);//liberamos tudo oq foi alocado e podemos parar por aqui
		free(line);
		return (NULL);
	}
	return (line);//caso tudo tenha dado certo, a linha atual sera retornada
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