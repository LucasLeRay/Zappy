/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** item_list2 by Lucas Le Ray
*/

#include "server.h"

int item_list_size(item_list_t *item_list, item_e data)
{
	item_list_t	*tmp = item_list->next;
	int		size = 0;

	while (tmp) {
		if (tmp->data == data)
			size++;
		tmp = tmp->next;
	}
	return (size);
}

int item_list_size_all(item_list_t *item_list)
{
	item_list_t	*tmp = item_list->next;
	int		size = 0;

	while (tmp) {
		size++;
		tmp = tmp->next;
	}
	return (size);
}