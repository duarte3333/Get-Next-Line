/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:01:12 by dsa-mora          #+#    #+#             */
/*   Updated: 2022/11/07 02:24:04 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*forward_line(char *line)
{
	char	*tmp;
	int		i;
	int		j;
	int		size_tmp;

	i = 0;
	//printf("enter forward line\n");
	if (!line)
		return (NULL);
	if (line[i] == '\0')
	{
		free(line);
		return (NULL);
	}
	while (line[i] != '\0' && line[i] != '\n')
			i++;
	if (line[i] != '\0')
	{
		j = ++i;	
	}
	else
		j = i;
	while (line[i] != '\0')
		i++;
	size_tmp = i - j + 1;
	//printf("size temp: %i\n",size_tmp);
	tmp = (char *)malloc((size_tmp) * sizeof(char));
	tmp[size_tmp - 1] = 0;
	i = 0;
	while (size_tmp - 1)
	{
		tmp[i] = line[j];
		i++;
		j++;
		size_tmp--;
	}
	free(line);
	//printf("temp: %s\n",tmp);
	return (tmp);
}

// A cada iteracao o read() retorna o numero de bytes que ja leu
// Se acabar o ficheiro sai do loop, pois nb_line = 0
// Se chegar a uma newline sai do loop, pois acabou a linha
char	*ft_read_line(char *line, int fd, char	*buffer)
{
	int		nb_line;

	nb_line = read(fd, buffer, BUFFER_SIZE);
	//printf("nb line: %i\n", nb_line);
	//printf("buffer: %s\n", buffer);
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
		//printf("nb line: %i\n", nb_line);
		//printf("buffer: %s\n", buffer);
		buffer[nb_line] = 0;
	}
	free(buffer);
	//printf("Line que foi lida: \n %s\n", line);
	return (line);
}

//linha 94, caso ft_read() retorne NULL
//tirar calloc
char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*line;
	char		*ready_line;

	buffer = (char *)calloc((BUFFER_SIZE + 1), sizeof(char));
	if (BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		return (NULL);
	}
	if (!line)
		line = calloc(1, 1);
	if (!(ft_strchr(line, '\n')))
		line = ft_read_line(line, fd, buffer);
	ready_line = ft_substr(line, 0, ft_strlen_nl(line));
	//printf("READY: %s|\n", ready_line);
	line = forward_line(line);
	//printf("HOW I AM NEXT %s\n", line);
	if (!ready_line)
		free(line);
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
// }
