/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** init.c
*/

#include "server.h"

void	rb_it_iterate(rb_it_t *it)
{
	if (it->tmp)
		it->tmp = it->tmp->next;
}

void	rb_it_erase(rb_it_t *it, bool free_data)
{
	rn_t	*next;

	if (!it->tmp)
		return;
	next = it->tmp->next;
	if (it->tmp->prev)
		it->tmp->prev->next = it->tmp->next;
	else
		it->buff->tail = it->tmp->next;
	if (it->tmp->next)
		it->tmp->next->prev = it->tmp->prev;
	else
		it->buff->head = it->tmp->prev;
	rn_deinit(it->tmp, it->tmp->type == EXTRA, free_data);
	--it->buff->nb_nodes;
	it->tmp = next;
}

void	*rb_it_get(rb_it_t *it)
{
	return (it->tmp ? it->tmp->data : NULL);
}

void	rb_it_set(rb_it_t *it, void *data)
{
	if (!it->tmp)
		return;
	it->tmp->data = data;
}
