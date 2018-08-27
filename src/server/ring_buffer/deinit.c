/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** init.c
*/

#include "server.h"

void	rb_deinit(rb_t *ring, bool free_self, bool free_data)
{
	rb_clear(ring, free_data);
	if (ring->buffers)
		free(ring->buffers);
	ring->tail = NULL;
	ring->head = NULL;
	ring->buffers = NULL;
	ring->max_buffers = 0;
	ring->nb_nodes = 0;
	if (free_self)
		free(ring);
}

void	rn_deinit(rn_t *node, bool free_self, bool free_data)
{
	node->type = UNUSED;
	node->next = NULL;
	node->prev = NULL;
	if (node->data && free_data)
		free(node->data);
	node->data = NULL;
	if (free_self)
		free(node);
}

void	rb_it_deinit(rb_it_t *it)
{
	it->buff = NULL;
	it->tmp = NULL;
}
