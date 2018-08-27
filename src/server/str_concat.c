/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** str_concat by Lucas Le Ray
*/

#include "server.h"

char	*str_sconcat(const char *a, const char *b, size_t sa, size_t sb)
{
	char	*str;
	size_t	size;

	if (!a || !b)
		return (str_sconcat(!a ? "" : a, !b ? "" : b, sa, sb));
	size = sa + sb;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	strncpy(str, a, sa);
	strncpy(str + sa, b, sb);
	return (str);
}

char	*str_concat_free(char *a, char *b)
{
	int	sa = (!a ? 0 : strlen(a));
	int	sb = (!b ? 0 : strlen(b) + 1);
	char	*concat = str_sconcat(a, b, sa, sb);

	if (a)
		free(a);
	if (b)
		free(b);
	return (concat);
}