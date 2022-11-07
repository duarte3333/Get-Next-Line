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

//Esta funcao conta o numero de elementos incluindo \0 ou \n
size_t	ft_strlen_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	i++;
	return (i);
}

//Esta funcao aloca memoria para n bytes com o malloc
//e depois coloca zeros em todos os bytes que alocou
void	*ft_calloc(size_t nelem, size_t elsize)
{
	char	*arr;
	size_t	i;

	i = -1;
	arr = malloc(elsize * nelem);
	if (!arr)
		return (NULL);
	if (nelem != 0)
	{
		while (++i < nelem)
			arr[i] = 0;
		return ((void *)arr);
	}
	return ((void *)arr);
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
	//printf("\nsize buffer qnd leio %i\n", size_concat + 1);
	concat = (char *)calloc((size_concat + 1), sizeof(char));
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
