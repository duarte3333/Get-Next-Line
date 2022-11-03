/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:01:12 by dsa-mora          #+#    #+#             */
/*   Updated: 2022/11/03 11:19:02 by dsa-mora         ###   ########.fr       */
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
	if (!line || line[i] == '\0' || line[i] == '\n')
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	j = ++i;
	while (line[i] != '\0')
		i++;
	size_tmp = i - j + 1;
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
	char	*line_temp;

	nb_line = 1;
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

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*line;
	char		*ready_line;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	buffer[BUFFER_SIZE] = 0;
	if (!buffer || (read(fd, 0, 0) < 0) || fd < 0 || fd > 1023)
		return (NULL);
	if (!line)
	{
		line = malloc(1);
		line[0] = 0;
	}
	if (!(ft_strchr(line, '\n')))
		line = ft_read_line(line, fd, buffer);
	free(buffer);
	ready_line = ft_substr(line, 0, ft_strlen_nl(line));
	line = forward_line(line);
	return (ready_line);
}

// printf("MY STRING \n%s\n", line);
// printf("READY: \n %s\n", ready_line);
// printf("HOW I AM NEXT\n %s\n", line);
int	main(void)
{
	int	fd;

	fd = open("oi.txt", O_RDONLY);
	printf("VALOR FD: %i\n", fd);
	printf("-----------------------------------------------\n");
	printf("\033[0;32m");
	printf("ITERATION 1  \n");
	printf("\033[0m");
	printf("\nOUTPUT 1 Iteration: %s\n", get_next_line(fd));
	printf("-----------------------------------------------\n");
	printf("\033[0;32m");
	printf("ITERATION 2  \n");
	printf("\033[0m");
	printf("\nOUTPUT 2 Iteration: %s\n", get_next_line(fd));
	printf("-----------------------------------------------\n");
	printf("\033[0;32m");
	printf("ITERATION 3  \n");
	printf("\033[0m");
	printf("\nOUTPUT 3 Iteration: %s\n", get_next_line(fd));
	printf("-----------------------------------------------\n");
}
