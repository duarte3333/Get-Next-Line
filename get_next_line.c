/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:01:12 by dsa-mora          #+#    #+#             */
/*   Updated: 2022/10/27 01:46:06 by dsa-mora         ###   ########.fr       */
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
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}


char	*ft_strdup_until_nl(const char *src)
{
	int		size;
	char	*dest;
	int		i;

	size = ft_strlen(src);
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] != '\n' && src[i] != '\0'  )
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

//Retorna a palavra a partir do primeiro elemento c que encontrar
char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}


//Esta funcao recebe duas strings e faz a concatenação de ambas
//ou seja, junta-as
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size_concat;
	char	*concat;
	char	*temp;

	size_concat = ft_strlen(s1) + ft_strlen(s2);
	if (size_concat == 0)
		return ((char *)malloc(0 * sizeof(char)));
	concat = (char *)malloc((size_concat + 1) * sizeof(char));
	concat[size_concat] = 0;
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
	printf("SSS: \n %s\n", (char *)s);
	printf("LEN \n %li\n", len);
	substr = (char *)malloc((len + 1) * sizeof(char));
	temp = substr;
	if (!substr)
		return (NULL);
	while (len && s[start] != 0 && start <= ft_strlen(s))
	{
		*substr = s[start];
		printf("SUBBBB: \n %c\n", *substr);
		substr++;
		start++;
		len--;
	}
	*substr = 0;
	substr = temp;
	return (substr);
}

char	*forward_line(char *line)
{
	if (*line == '\0' || *line == '\n')
		return (0);
	while (*line != '\0' && *line != '\n')
		line++;
	line++;
	return (line);
}

// A cada iteracao o read() retorna o numero de bytes que ja leu
// ou seja, incrementa 1 o valor que retorna e passa a apontar
// para o proximo elemento do buffer
// Se acabar o ficheiro sai do loop, pois nb_line = 0
// Se chegar a uma newline sai do loop, pois acabou a linha
char	*ft_read_line(char *line, int fd, char	*buffer)
{
	int		nb_line;
	char	*line_temp;

	while (nb_line > 0)
	{
		line_temp = line;
		line = ft_strjoin(line_temp, buffer);
		free(line_temp);
		line_temp = NULL;
		if (ft_strchr(line, '\n'))
			break ;
		nb_line = read(fd, buffer, BUFFER_SIZE);
		if (!nb_line)
			return (NULL);
	}
	return (line);
}

char *ft_extract_line(char *line)
{
	int size;
	int i;
	int j;
	int *lets
	
	i = 0;
	j = 0;
	size = ft_strlen_nl(line);
	lets = (char *)malloc((size + 1) * sizeof(char));
	lets[size] = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		lets[j] = line[i];
		j++;
		i++;
	}
	while(i < 1)
	{
		i--;
		ready_line--;
		line--;
	}
	return (ready_line);
	printf("OI: \n %s\n", ready_line);
	printf("OLA: \n %s\n", line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*line;
	static char	*ready_line;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	buffer[BUFFER_SIZE] = 0;
	if (!buffer || (read(fd, 0, 0) < 0) || fd < 0 || fd > 1023)
		return (NULL);
	if (!line)
	{
		line = malloc(1);
		line[0] = 0;
	}
	if ((!ft_strchr(line, '\n')))
		line = ft_read_line(line, fd, buffer);
	free(buffer);
	buffer = NULL;
	//printf("MY STRING \n%s\n", line);
	
	ready_line = ft_substr(line, 0, ft_strlen_nl(line));
	//printf("READY: \n %s\n", ready_line);
	
	line = forward_line(line);
	//printf("HOW I AM NEXT\n %s\n", line);
	return (ready_line);
}

//printf("MY STRING \n%s\n", line);
//printf("READY: \n %s\n", ready_line);
//printf("HOW I AM NEXT\n %s\n", line);
int	main(void)
{
	int fd;
	fd = open("oi.txt", O_RDONLY);
	printf("fd %i\n", fd);
	printf("li isto: %s\n", get_next_line(fd));
	printf("li isto2: %s\n", get_next_line(fd));
	printf("li isto3: %s\n", get_next_line(fd));
}
