/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:01:12 by dsa-mora          #+#    #+#             */
/*   Updated: 2022/10/29 18:49:07 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*forward_line(char *line)
{
	char	*tmp;

	if (*line == '\0' || *line == '\n')
		return (0);
	while (*line != '\0' && *line != '\n')
	{
		line++;
	}
	while (*line != '\0')
	{
		*tmp = *line;
		line++;
		tmp++;
	}
	free(line);
	line = tmp;
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
	ready_line = ft_substr(line, 0, ft_strlen_nl(line));
	line = forward_line(line);
	return (ready_line);
}

//printf("MY STRING \n%s\n", line);
//printf("READY: \n %s\n", ready_line);
//printf("HOW I AM NEXT\n %s\n", line);
// int	main(void)
// {
// 	int fd;
// 	fd = open("oi.txt", O_RDONLY);
// 	printf("fd %i\n", fd);
// 	printf("li isto: %s\n", get_next_line(fd));
// 	printf("li isto2: %s\n", get_next_line(fd));
// 	printf("li isto3: %s\n", get_next_line(fd));
// }
