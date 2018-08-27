/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** write_egg by Lucas Le Ray
*/

#include "server.h"

void print_egg(egg_list_t *eggs, case_t *c, char **tmp)
{
	if (eggs->data->c == c) {
		*tmp += sprintf(*tmp, "7");
		if (eggs->next || player_list_size_all(c->players)
			|| item_list_size_all(c->items))
			*tmp += sprintf(*tmp, " ");
	}
}