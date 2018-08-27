/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** init.c
*/

#include "server.h"

int	rb_init(rb_t *ring, size_t max_buffers)
{
	rn_t	*buffers;

	buffers = malloc(sizeof(rn_t) * max_buffers);
	if (!buffers)
		return (-1);
	for (size_t i = 0; i < max_buffers; ++i)
		rn_init(buffers + i);
	ring->tail = NULL;
	ring->head = NULL;
	ring->buffers = buffers;
	ring->max_buffers = max_buffers;
	ring->nb_nodes = 0;
	return (0);
}

void	rn_init(rn_t *node)
{
	node->type = UNUSED;
	node->next = NULL;
	node->prev = NULL;
	node->data = NULL;
}

void	rb_it_init(rb_it_t *it, rb_t *rb)
{
	it->buff = rb;
	it->tmp = rb->tail;
}
