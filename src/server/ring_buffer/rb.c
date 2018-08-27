/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** init.c
*/

#include "server.h"

void	*rb_pop(rb_t *ring)
{
	rn_t	*node = ring->tail;
	void	*data;

	if (!node)
		return (NULL);
	if (node->next) {
		ring->tail = node->next;
		node->next->prev = NULL;
	} else {
		ring->tail = NULL;
		ring->head = NULL;
	}
	data = node->data;
	rn_deinit(node, node->type == EXTRA, false);
	--ring->nb_nodes;
	return (data);
}

void	rb_clear(rb_t *ring, bool free_data)
{
	rn_t	*tmp = ring->tail;
	rn_t	*next;

	while (tmp) {
		next = tmp->next;
		rn_deinit(tmp, tmp->type == EXTRA, free_data);
		tmp = next;
	}
	ring->tail = NULL;
	ring->head = NULL;
	ring->nb_nodes = 0;
}

size_t	rb_size(rb_t *ring)
{
	return (ring->nb_nodes);
}
