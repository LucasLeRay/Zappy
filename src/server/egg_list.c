/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** egg_list by Lucas Le Ray
*/

#include "server.h"

egg_list_t *egg_list_new(egg_t *data)
{
	egg_list_t	*egg_list = malloc(sizeof(egg_list_t));

	egg_list->data = data;
	egg_list->next = NULL;
	return (egg_list);
}

void egg_list_push(egg_list_t *egg_list, egg_t *data)
{
	egg_list_t	*new = egg_list_new(data);
	egg_list_t	*tmp = egg_list;

	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	egg_list_clear(egg_list_t *egg_list, bool free_p)
{
	egg_list_t	*tmp = egg_list->next;
	egg_list_t	*tmp_free;

	while (tmp) {
		tmp_free = tmp;
		tmp = tmp->next;
		if (tmp_free) {
			free_p ? free(tmp_free->data) : 0;
			free(tmp_free);
		}
	}
	egg_list->next = NULL;
}

void egg_list_del_data(egg_list_t **egg_list, egg_t *data,
			bool free_p)
{
	egg_list_t	*tmp = (*egg_list)->next;
	egg_list_t	*free_tmp;

	if (tmp->data == data)
		(*egg_list)->next = tmp->next;
	while (tmp) {
		if (tmp->next && tmp->next->data == data) {
			free_tmp = tmp->next;
			tmp->next = tmp->next->next;
			free_p ? free(free_tmp->data) : 0;
			free(free_tmp);
			return;
		}
		tmp = tmp->next;
	}
}

int egg_list_size_all(egg_list_t *egg_list)
{
	egg_list_t	*tmp = egg_list->next;
	int		size = 0;

	while (tmp) {
		size++;
		tmp = tmp->next;
	}
	return (size);
}