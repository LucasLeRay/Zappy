/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** rb_extract.c
*/

#include "server.h"

static bool	has_cmd_in_buff(
			rb_t *buff, const char *delims,
			size_t *iteration, size_t *cmd_size)
{
	rb_it_t		it;
	char		*data;
	size_t		dpos = 0;

	rb_it_init(&it, buff);
	(*iteration) = 0;
	(*cmd_size) = 0;
	do {
		data = rb_it_get(&it);
		for (size_t i = 0; data && data[i]; ++i) {
			++(*cmd_size);
			dpos += (data[i] == delims[dpos] ? 1 : -dpos);
			if (delims[dpos] == '\0')
				return (true);
		}
		rb_it_iterate(&it);
	} while (data && ++(*iteration));
	rb_it_deinit(&it);
	return (false);
}

static void	add_rest_cmd_to_buff(rb_t *buff, char *rest)
{
	if (!rest || !(*rest))
		return;
	rest = strdup(rest);
	if (!rest) {
		error_msg(strerror(errno));
		rb_clear(buff, true);
	} else {
		rb_push_front(buff, rest);
	}
}

char	*extract_cmd_from_buff(rb_t *buff, const char *delims)
{
	rb_it_t		it;
	char		*data;
	char		*cmd = NULL;
	size_t		cmd_size = 0;
	size_t		iteration = 0;

	if (!has_cmd_in_buff(buff, delims, &iteration, &cmd_size))
		return (NULL);
	rb_it_init(&it, buff);
	for (size_t i = 0; i <= iteration; ++i) {
		data = rb_it_get(&it);
		rb_it_erase(&it, false);
		cmd = str_concat_free(cmd, data);
	}
	if (!cmd)
		return ((void *)(error_msg(strerror(errno))));
	cmd[cmd_size - strlen(delims)] = 0;
	add_rest_cmd_to_buff(buff, cmd + cmd_size);
	rb_it_deinit(&it);
	return (cmd);
}

char	*rb_pop_head_no_delete(rb_t *ring)
{
	rn_t	*node = ring->head;
	void	*data;

	if (!node)
		return (NULL);
	data = node->data;
	return (data);
}

void	*rb_pop_head(rb_t *ring)
{
	rn_t	*node = ring->head;
	void	*data;

	if (!node)
		return (NULL);
	if (node->prev) {
		ring->head = node->prev;
		node->prev->next = NULL;
	} else {
		ring->tail = NULL;
		ring->head = NULL;
	}
	data = node->data;
	rn_deinit(node, node->type == EXTRA, false);
	--ring->nb_nodes;
	return (data);
}
