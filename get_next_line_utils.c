/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:20:27 by dsa-mora          #+#    #+#             */
/*   Updated: 2022/10/29 18:20:27 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlen_nl(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

//Ocupa n bytes com NULL a partir do elemento para o qual s está a apontar
void	ft_bzero(void *s, size_t n)
{
	char	*str;
	int		i;

	i = -1;
	str = (char *)s;
	while (n > 0)
	{
		str[++i] = 0;
		n--;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	final_size;

	if (nmemb == 0 || size == 0)
	{
		nmemb++;
		size++;
	}
	final_size = nmemb * size;
	p = malloc(final_size);
	if (!p)
		return (NULL);
	ft_bzero(p, final_size);
	return (p);
}

//Retorna a palavra a partir do primeiro elemento c que encontrar
char	*ft_strchr(char *s, int c)
{
	if (s)
	{
		while (s && *s != '\0')
		{
			if (*s == (char)c)
				return ((char *)s);
			s++;
		}
		if (*s == (char)c)
			return ((char *)s);
	}
	return (0);
}

//Esta funcao recebe duas strings e faz a concatenação de ambas
//ou seja, junta-as
char	*ft_strjoin(char *s1, char const *s2)
{
	int		size_concat;
	char	*concat;
	char	*temp;

	size_concat = ft_strlen(s1) + ft_strlen(s2);
	printf("\nsize buffer qnd leio %i\n", size_concat + 1);
	concat = (char *)ft_calloc((size_concat + 1), sizeof(char));
	temp = concat;
	while (*s1)
	{
		*concat = *s1;
		concat++;
		s1++;
	}
	while (*s2)
	{
		*concat = *s2;
		concat++;
		s2++;
	}
	concat = temp;
	if (!s1)
		free(s1);
	return (concat);
}

//s - uma str normal
//start - indice do str onde comeca a substr
//len - tamanho da maximo da substr
//Esta funcao vai criar uma substr desde o start ao indice len do s
//sendo o len um indice posterior ao s
//Caso o indice len exceda o tamanho da str s ele acaba a substring
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*temp;

	if (!s)
		return (NULL);
	substr = (char *)malloc((len + 1) * sizeof(char));
	printf("len substr %li\n", len + 1);
	temp = substr;
	if (!substr)
		return (NULL);
	while (len && s[start] != 0 && start <= ft_strlen(s))
	{
		*substr = s[start];
		substr++;
		start++;
		len--;
	}
	*substr = 0;
	substr = temp;
	printf("qual a substr: %s\n", substr);
	return (substr);
}
