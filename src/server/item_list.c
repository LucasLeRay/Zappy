/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** item_list by Lucas Le Ray
*/

#include "server.h"

item_list_t *item_list_new(item_e data)
{
	item_list_t	*item_list = malloc(sizeof(item_list_t));

	item_list->data = data;
	item_list->next = NULL;
	return (item_list);
}

void item_list_push(item_list_t *item_list, item_e data)
{
	item_list_t	*new = item_list_new(data);
	item_list_t	*tmp = item_list;

	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	item_list_clear(item_list_t *item_list)
{
	item_list_t	*tmp = item_list->next;
	item_list_t	*tmp_free;

	while (tmp) {
		tmp_free = tmp;
		tmp = tmp->next;
		if (tmp_free)
			free(tmp_free);
	}
	item_list->next = NULL;
}

void item_list_del_data(item_list_t **item_list, item_e data)
{
	item_list_t	*tmp = (*item_list)->next;
	item_list_t	*free_tmp;

	if (tmp->data == data) {
		(*item_list)->next = tmp->next;
		return;
	}
	while (tmp) {
		if (tmp->next && tmp->next->data == data) {
			free_tmp = tmp->next;
			tmp->next = tmp->next->next;
			free(free_tmp);
			return;
		}
		tmp = tmp->next;
	}
}