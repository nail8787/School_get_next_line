#include "get_next_line.h"

static char		*ft_strchr(char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			*s = '\0';
			return ((char*)s);
		}
		else
			s++;
	}
	if (*s == c)
	{
		*s = '\0';
		return ((char *)s);
	}
	else
		return (NULL);
}

static int		clean(char **leftover)
{
	if (*leftover)
	{
		free(*leftover);
		*leftover = NULL;
	}
	return (1);
}

static int		check_leftover(char **leftover, char **line)
{
	char		*check;
	char		*antileak;

	if (*leftover)
	{
		check = ft_strchr(*leftover, '\n');
		if (check)
		{
			antileak = *leftover;
			*line = ft_strdup(*leftover);
			*leftover = ft_strdup(check + 1);
			if (!*line || !*leftover)
				return (-1 * clean(&antileak));
			return (clean(&antileak));
		}
		return (0);
	}
	else
		return (-2);
}

static int		read_from_fd(int fd, char **line, char **leftover, char *buf)
{
	int			bytes_read;
	char		*antileak;

	while ((bytes_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes_read] = '\0';
		antileak = *leftover;
		if (ft_strchr(buf, '\n') != NULL)
		{
			*line = ft_strjoin(*leftover, buf);
			*leftover = ft_strdup(ft_strchr(buf, '\0') + 1);
			if (!*line || !*leftover)
				return (-1 * clean(&antileak));
			return (clean(&antileak));
		}
		else
		{
			if (!(*leftover = ft_strjoin(*leftover, buf)))
				return (-1 * clean(&antileak));
			clean(&antileak);
		}
	}
	if (bytes_read < BUFFER_SIZE && ((ft_strchr(*leftover, '\n')) == NULL))
		return (0);
	return (-1);
}

int				get_next_line(int fd, char **line)
{
	static char	*leftover;
	char		buf[BUFFER_SIZE + 1];
	int			res;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line || (read(fd, buf, 0) < 0))
		return (-1);
	*line = NULL;
	res = check_leftover(&leftover, line);
	if (res == 1)
		return (res);
	if (res == -1)
		return (-1 * clean(&leftover));
	if (res == -2)
	{
		leftover = ft_strdup("");
		if (!leftover)
			return (-1);
	}
	if ((res = read_from_fd(fd, line, &leftover, buf)) <= 0)
	{
		if (!(*line = ft_strdup(leftover)))
			return (-1 * clean(&leftover));
		clean(&leftover);
	}
	return (res);
}
