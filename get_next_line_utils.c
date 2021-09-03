#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	s;

	s = 0;
	if (!str)
		return (0);
	while (str[s])
		s++;
	return (s);
}

char	*ft_strchr(char *s, int c)
{
	int	find;

	find = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[find])
	{
		if (s[find] == (char) c)
			return ((char *)&s[find]);
		find ++;
	}
	return (0);
}

char	*ft_strjoin(char *left_str, char *buffer)
{
	char			*new_str;
	size_t			s;
	size_t			n;

	s = 0;
	n = 0;
	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));//geramos uma alocação para o caso da nossa variavel estatica nao contenha nada
		left_str[0] = '\0';
	}
	new_str = malloc (sizeof(char) * (ft_strlen(left_str) + ft_strlen(buffer)) + 1);//alocamos um espaço na memória suficiente para nosso buffer e a left_str
	if (new_str == NULL)
		return (NULL);
	while (left_str[n] != '\0')
		new_str[n++] = left_str[s++];
	s = 0;
	while (buffer[s])
		new_str[n++] = buffer[s++];
	new_str[n] = '\0';
	free(left_str);
	return (new_str);
}

char	*ft_line(char *left_str)//função para criar nossa linha
{
	int			i;
	char		*str;

	i = 0;
	if (!left_str)
		return (NULL);
	while (left_str[i] && left_str[i] != '\n')
		i++;//vamos até a primeira ocorrencia da quebra de linha, para determinar o tamanho da linha
	str = (char *) malloc (sizeof(char) * (i + 2));// garantindo que tenha memória suficiente para nossos caracteres '\0' e '\n'
	if (!str)
		return (NULL);
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	if (left_str[i] == '\n')
	{
		str[i] = left_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_newleft(char *left_str)//função para salvar a localização no programa
{
	int			s;
	int			i;
	char		*str;

	i = 0;
	s = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;//vamos até a primeira a ocorencia da quebra de linha para começar da segunda linha
	if (left_str[i] == '\0')//caso a nossa str acabe após a quebra de linha, nos retornaremos nulo
	{
		free(left_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - i + 1));// para excluirmos a primeira linha que ja foi copiada na função anterior
	if (!str)
		return (NULL);
	i++;
	while (left_str[i])
		str[s++] = left_str[i++];
	str[s] = '\0';
	free(left_str);
	return (str);
}