/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:01:12 by dsa-mora          #+#    #+#             */
/*   Updated: 2022/11/05 18:08:18 by dsa-mora         ###   ########.fr       */
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
	printf("ando pa frente\n");
	if (!line)
		return (NULL);
	if (line[i] == '\0')
	{
		free(line);
		return (NULL);
	}
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	j = ++i;
	while (line[i] != '\0')
		i++;
	size_tmp = i - j + 1;
	printf("size temp %i\n",size_tmp);
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
	printf("temp %s\n",tmp);
	return (tmp);
}

// A cada iteracao o read() retorna o numero de bytes que ja leu
// ou seja, incrementa 1 o valor que retorna e passa a apontar
// para o proximo elemento do buffer
// Se acabar o ficheiro sai do loop, pois nb_line = 0
// Se chegar a uma newline sai do loop, pois acabou a linha
char	*ft_read_line(char *line, int fd, char	*buffer)
{
	int		nb_line;

	nb_line = read(fd, buffer, BUFFER_SIZE);
	if (nb_line <= 0)
	{
		free(buffer);
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
		if (!nb_line)
			return (NULL);
	}
	printf("diz me a line quando leio: \n %s\n", line);
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
		line = ft_calloc(1, 1);
	if (!(ft_strchr(line, '\n')))
		line = ft_read_line(line, fd, buffer);
	free(buffer);
	ready_line = ft_substr(line, 0, ft_strlen_nl(line));
	line = forward_line(line);
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
// 	printf("-----------------------------------------------\n");
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
