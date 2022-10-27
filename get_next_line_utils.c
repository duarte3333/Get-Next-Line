// size_t	ft_strlen(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

// char	*ft_strdup(const char *src)
// {
// 	int		size;
// 	char	*dest;
// 	int		i;

// 	size = ft_strlen(src);
// 	dest = (char *)malloc((size + 1) * sizeof(char));
// 	if (!dest)
// 		return (NULL);
// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

//A cada iteracao o read() retorna o numero de bytes que ja leu
//ou seja, incrementa 1 o valor que retorna e passa a apontar
//para o proximo elemento do buffer
//Se acabar o ficheiro sai do loop, pois nb_line = 0
//Se chegar a uma newline sai do loop, pois acabou a linha
// char	*ft_read_line(int fd)
// {
// 	int		nb_line;
// 	char	line[10000];
// 	char	buffer;
// 	int		i;

// 	nb_line = 1;
// 	i = -1;
// 	buffer = 0;
// 	while (nb_line > 0)
// 	{
// 		if (buffer == '\n')
// 			break ;
// 		nb_line = read(fd, &buffer, 1);
// 		line[++i] = buffer;
// 	}
// 	line[i] = '\0';
// 	return (ft_strdup(line));
// }

// char	*get_next_line(int fd)
// {
// 	//char	*buffer;
// 	char	*ret;

// 	//buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	ret = (char *)malloc((10000 + 1) * sizeof(char));
// 	//!buffer
// 	if (read(fd, 0, 0) < 0)
// 		return (NULL);  //sera que é -1?
// 	ret = ft_read_line(fd);
// 	//free(buffer);
// 	if (!ret)
// 		return (NULL);
// 	return (ret);
// } 