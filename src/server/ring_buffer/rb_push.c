/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** rb_push.c
*/

#include "server.h"

static rn_t	*rb_get_unused_rn(rb_t *ring)
{
	rn_t	*node;

	for (size_t i = 0; i < ring->max_buffers; ++i)
		if (ring->buffers[i].type == UNUSED) {
			node = ring->buffers + i;
			node->type = USED;
			return (node);
		}
	node = malloc(sizeof(rn_t));
	if (!node)
		return (NULL);
	rn_init(node);
	node->type = EXTRA;
	return (node);
}

int	rb_push(rb_t *ring, void *data)
{
	rn_t	*node = rb_get_unused_rn(ring);

	if (!node)
		return (-1);
	else if (!ring->tail || !ring->head) {
		ring->tail = node;
		ring->head = node;
	} else {
		node->prev = ring->head;
		ring->head->next = node;
		ring->head = node;
	}
	node->data = data;
	++ring->nb_nodes;
	return (0);
}

int	rb_push_front(rb_t *ring, void *data)
{
	rn_t	*node = rb_get_unused_rn(ring);

	if (!node)
		return (-1);
	else if (!ring->tail || !ring->head) {
		ring->tail = node;
		ring->head = node;
	} else {
		node->next = ring->tail;
		ring->tail->prev = node;
		ring->tail = node;
	}
	node->data = data;
	++ring->nb_nodes;
	return (0);
}
