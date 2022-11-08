/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:01:12 by dsa-mora          #+#    #+#             */
/*   Updated: 2022/11/08 15:34:54 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	return (substr);
}
//Se a line nao existir retorna NULL
//Se a line for '\0', damos free line e retorna-se NULL
//Se a line for '\n', o temp aloca 1 byte para o NULL   
//Na maioria dos casos, esta funcao vai andar a line para a frente 
//ate ao ultimo elemento que leu, gerando uma variavel temporaria 
//que ira conter desde o primeiro elemento da proxima linha 
//ate ao final do ficheiro

char	*ft_forward_line(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
			i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	j = ++i;
	while (line[i] != '\0')
		i++;
	tmp = (char *)malloc((i - j + 1) * sizeof(char));
	tmp[i - j] = 0;
	i = -1;
	j--;
	while (line[++j] != '\0')
		tmp[++i] = line[j];
	free(line);
	return (tmp);
}

//Esta funcao comeca por ler um buffer com o read() 
//Caso, a line seja vazia o read() retorna 0 
//Caso, a line nao exista, o read() retorna -1
//Caso um buffer nao chegue para ler a linha toda, 
//rescreve-se nele e vai se guardando tudo na line com o ft_strjoin()
char	*ft_read_line(char *line, int fd, char	*buffer)
{
	int		nb_line;

	nb_line = read(fd, buffer, BUFFER_SIZE);
	if (nb_line <= 0)
	{
		if (!line[0])
		{
			free(line);
			line = NULL;
		}
		return (line);
	}
	while (nb_line > 0)
	{
		line = ft_strjoin(line, buffer);
		if (ft_strchr(line, '\n'))
			break ;
		nb_line = read(fd, buffer, BUFFER_SIZE);
		buffer[nb_line] = 0;
	}
	return (line);
}

//Caso o buffer seja menor que 0 ou o fd nao seja valido retorna-se NULL
//Esta funcao ira ler a primeira linha de um ficheiro caso seja chamada, 
//e caso seja chamada de novo ira ler a linha a seguir do ficheiro, etc...
//Caso ja nao haja mais linhas no ficheiro para ler e se 
//continue a chamar a funcao ela ira retorna NULL 
char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*line;
	char		*ready_line;

	buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		free(buffer);
		return (NULL);
	}
	if (!line)
		line = (char *)ft_calloc(1, 1);
	if (!(ft_strchr(line, '\n')))
		line = ft_read_line(line, fd, buffer);
	ready_line = ft_substr(line, 0, ft_strlen_nl(line));
	line = ft_forward_line(line);
	if (!ready_line)
		free(line);
	free(buffer);
	return (ready_line);
}

// printf("MY STRING \n%s\n", line);
// printf("READY: \n %s\n", ready_line);
// printf("HOW I AM NEXT\n %s\n", line);

// int	main(void)
// {
// 	int	fd;
// 	char *s;

// 	fd = open("oi.txt", O_RDONLY);
// 	s = get_next_line(fd);
// 	printf("VALOR FD: %i\n", fd);
// /* 	printf("\033[0;32m");
// 	printf("ITERATION 1  \n");
// 	printf("\033[0m"); */
// 	printf("\nOUTPUT 1 Iteration: %s\n", s); free(s);
// 	printf("-----------------------------------------------\n");
// /* 	printf("\033[0;32m");
// 	printf("ITERATION 2  \n");
// 	printf("\033[0m"); */
// 	s = get_next_line(fd); printf("\nOUTPUT 2 Iteration: %s\n", s); free(s);
// 	printf("-----------------------------------------------\n");
// /* 	printf("\033[0;32m");
// 	printf("ITERATION 3  \n");
// 	printf("\033[0m"); */
// 	s = get_next_line(fd); printf("\nOUTPUT 3 Iteration: %s\n", s); free(s);
// 	printf("-----------------------------------------------\n");
// 	s = get_next_line(fd); printf("\nOUTPUT 3 Iteration: %s\n", s); free(s);
// 	printf("-----------------------------------------------\n");
// 	s = get_next_line(fd); printf("\nOUTPUT 3 Iteration: %s\n", s); free(s);
// 	printf("-----------------------------------------------\n");
// }

