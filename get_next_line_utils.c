/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 15:04:02 by gabriel           #+#    #+#             */
/*   Updated: 2021/09/14 14:17:27 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_strjoin(char *left_str, char *buffer)//a mesma função feita na libft, porém com algumas modificações
{
	char			*new_str;
	size_t			s;
	size_t			n;
	int				lenstr;

	lenstr = ft_strlen(left_str);
	s = 0;
	n = 0;
	if (!left_str)//caso seja a primeira vez que esteja lendo a linha, ou a linha atual nao contenha nada escrito 
	{
		left_str = (char *)malloc(1 * sizeof(char));//vamos alocar memória somente para o byte nulo
		left_str[0] = '\0';
	}
	new_str = malloc (sizeof(char) * (lenstr + ft_strlen(buffer)) + 1);//alocamos memória suficiente para oq ja foi lido e o buffer junto, contando com o \0
	if (new_str == NULL)
		return (NULL);
	while (left_str[n] != '\0')
		new_str[n++] = left_str[s++];
	s = 0;
	while (buffer[s])
		new_str[n++] = buffer[s++];
	new_str[n] = '\0';//copiamos ambas string e colocamos o \0 ai final dela
	free(left_str);//aqui garantimos que seja liberada a memoria caso tenha sido alocada no meio dessa função
	return (new_str);
}

char	*ft_line(char *left_str)//função de impressão da linha que sera retornada 
{
	int			i;
	char		*str;

	i = 0;
	if (!left_str)
		return (NULL);
	while (left_str[i] && left_str[i] != '\n')//procuramos a primeira ocorrencia da quebra de linha ou o fim do texto, isso servirá para a alocação da string
		i++;
	str = (char *) malloc (sizeof(char) * (i + 2));//alocaremos memória com esse valor + 2, isso porque teremos que garantir espaço para os caracterer \0 e \n
	if (!str)
		return (NULL);
	i = 0;//zeramos o contador novamente, somente para não usar 2
	while (left_str[i] && left_str[i] != '\n')//agora copiaremos a linha ate que acabe o texto ou ache uma quebra de linha
	{
		str[i] = left_str[i];
		i++;
	}
	if (left_str[i] == '\n')//caso tenha saido do loop pela quebra de linha, temos que coloca-la na sting
	{
		str[i] = left_str[i];
		i++;
	}
	str[i] = '\0';//colocamos o byte nulo logo após a quebra de linha
	return (str);
}

char	*ft_newleft(char *left_str)//função para armazenar a posição inicial da proxima linha
{
	int			s;
	int			i;
	char		*str;

	i = 0;
	s = 0;
	while (left_str[i] && left_str[i] != '\n')//iremos ate a primeira quebra de linha, de la que iremos começar a cópia
		i++;
	if (left_str[i] == '\0')//caso nao tenha uma proxima linha, liberamos aquela memoria e retornamos nulo
	{
		free(left_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(left_str) - i + 1));//alocamos memória de tamanho que comece a contar depois da quebra de linha
	if (!str)
		return (NULL);
	i++;// passamos do byte de quebra de linha e copiaremos todo o restante
	while (left_str[i])
		str[s++] = left_str[i++];
	str[s] = '\0';
	free(left_str);//tendo esse texto salvo, podemos liberar a memória alocada anteriormente
	return (str);
}
