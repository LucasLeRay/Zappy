/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** str_to_tab by Lucas Le Ray
*/

#include "server.h"

static int	jump_delims(char *str, char *delims, bool reverse)
{
	size_t	i = 0;
	bool	found;

	for (; str[i]; ++i) {
		found = false;
		for (size_t d = 0; delims[d]; ++d) {
			if (str[i] == delims[d]) {
				found = true;
				break;
			}
		}
		if ((!reverse && !found) || (reverse && found))
			return (i);
	}
	return (i);
}

static int	str_to_tab_size(char *str, char *delims)
{
	size_t	size = 0;
	size_t	jump;

	while (*str) {
		str += jump_delims(str, delims, false);
		jump = jump_delims(str, delims, true);
		str += jump;
		size += (jump > 0);
	}
	return (size);
}

void	free_tab(char **tab)
{
	int	i;

	for (i = 0; tab[i]; i++)
		free(tab[i]);
	free(tab);
}

char	**str_to_tab(char *str, char *delims)
{
	size_t	size = str_to_tab_size(str, delims);
	char	**tab = malloc(sizeof(char *) * (size + 1));
	size_t	jump;

	size = 0;
	while (tab && *str) {
		str += jump_delims(str, delims, false);
		jump = jump_delims(str, delims, true);
		if (jump > 0) {
			tab[size] = malloc(sizeof(char) * (jump + 1));
			if (!tab[size])
				return (NULL);
			strncpy(tab[size], str, jump);
			tab[size][jump] = 0;
			++size;
		}
		str += jump;
		tab[size] = NULL;
	}
	return (tab);
}
