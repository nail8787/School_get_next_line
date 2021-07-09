#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	res;
	int		i;

	i = 0;
	res = 0;
	while (s[i] != '\0')
	{
		res++;
		i++;
	}
	return (res);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	res;
	size_t	index;

	index = 0;
	res = ft_strlen(src);
	if (size > 0)
	{
		while (index < size - 1 && src[index] != '\0')
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (res);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	res;

	if (size < ft_strlen(dst) + 1)
		res = size + (size_t)ft_strlen(src);
	else
		res = (size_t)ft_strlen(dst) + (size_t)ft_strlen(src);
	index = (size_t)ft_strlen(dst);
	if (size > 0)
	{
		while ((index < size - 1) && *src != '\0')
		{
			dst[index] = *src;
			src++;
			index++;
		}
		dst[index] = '\0';
	}
	return (res);
}

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*str;

	size = ft_strlen(s1) + 1;
	str = (char *)malloc(size * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, size);
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = (char *)malloc(len * sizeof(char));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, ft_strlen(s1) + 1);
	ft_strlcat(newstr, s2, len);
	return (newstr);
}
