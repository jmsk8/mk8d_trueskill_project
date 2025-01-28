#include "../includes/libft.h"

char *ft_strndup(const char *s, size_t n)
{
	char *dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	strncpy(dup, s, n);
	dup[n] = '\0';
	return (dup);
}
