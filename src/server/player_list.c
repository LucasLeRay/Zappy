/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** player_list by Lucas Le Ray
*/

#include "server.h"

player_list_t *player_list_new(player_t *data)
{
	player_list_t	*player_list = malloc(sizeof(player_list_t));

	player_list->data = data;
	player_list->next = NULL;
	return (player_list);
}

void player_list_push(player_list_t *player_list, player_t *data)
{
	player_list_t	*new = player_list_new(data);
	player_list_t	*tmp = player_list;

	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	player_list_clear(player_list_t *player_list, bool free_p)
{
	player_list_t	*tmp = player_list->next;
	player_list_t	*tmp_free;

	while (tmp) {
		tmp_free = tmp;
		tmp = tmp->next;
		if (tmp_free) {
			free_p ? free(tmp_free->data) : 0;
			free(tmp_free);
		}
	}
	player_list->next = NULL;
}

void player_list_del_data(player_list_t **player_list, player_t *data,
			bool free_p)
{
	player_list_t	*tmp = (*player_list)->next;
	player_list_t	*free_tmp;

	if (tmp->data == data) {
		(*player_list)->next = tmp->next;
		return;
	}
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

int player_list_size_all(player_list_t *player_list)
{
	player_list_t	*tmp = player_list->next;
	int		size = 0;

	while (tmp) {
		size++;
		tmp = tmp->next;
	}
	return (size);
}