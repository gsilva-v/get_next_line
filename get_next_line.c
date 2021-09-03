#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
//bibliotecas para usar as funções do main
char	*ft_readleftstr(int fd, char *left_str)
{
	char *buffer;
	int read_byte;
		
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));//alocamos memoria ao buffer a depender do tamanho do buffer e colocamos + 1 para garantir o espaço do byte nulo
	if (!buffer)
	{
		free (buffer);	
		return (NULL);
	}
	read_byte = 1;
	while (!ft_strchr(left_str, '\n') && read_byte != 0)//se o read_byte resultar 0, é por que nao foi lido nada. se o read_byte resultar -1, significa que algo deu errado
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1 )
		{
			free(buffer);//caso de um erro, nos liberaremos a memoria alocada e retonaremos nulo
			return (NULL);
		}
		buffer[read_byte] = '\0';// colocamos o byte nulo ao final do buffer
		left_str = ft_strjoin(left_str, buffer);//criaremos uma nova string com a junção da nossa antiga string com oq foi lido pelo buffer
	}	
	free(buffer);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char	*line;
	static char	*left_str;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)//caso o tipo de arquivo ou tamanho do buffer nao seja passado retornaremos um erro
		return (NULL);
	left_str = ft_readleftstr(fd, left_str);//usaremos a função para atribuir a linha a variavel
	if (!left_str)
		return (NULL);
	line = ft_line(left_str);//usaremos a função para criar a linha que deverermos retornar
	if (line[0] == '\0')
	{
		free(line); //caso nao tenha sido lido nada, liberaremos a memoria alocada e retornaremos um nulo
		return (NULL);
	}
	left_str = ft_newleft(left_str);//armazenaremos a posição que paramos caso aja mais linhas para ler
	return (line);// retornamos a linha atual
}


/*
int	main(void)
{
	char	*line;
	int		i;
//	int		fd1;
//	int		fd2;
	int		fd3;
//	fd1 = open("test.txt", O_RDONLY);
//	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
//		line = get_next_line(fd1);
//		printf("line [%02d]: %s", i, line);
//		free(line);
//		line = get_next_line(fd2);
//		printf("line [%02d]: %s", i, line);
//		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
//	close(fd1);
//	close(fd2);
	close(fd3);
	return (0);
}*/
