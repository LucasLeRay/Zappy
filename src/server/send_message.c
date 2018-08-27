/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** send_message by Lucas Le Ray
*/

#include "server.h"

void send_message(server_t *server, player_list_t **p)
{
	char	*msg;

	while ((msg = rb_pop(&((*p)->data->msg_send)))) {
		if (!(*p)->data->disconnected
			&& write((*p)->data->fd, msg, strlen(msg)) == -1)
			(*p)->data->disconnected = true;
		free(msg);
	}
	if ((*p)->data->dead) {
		(*p)->data->team->nb_players--;
		player_list_del_data(&(*p)->data->case_on->players,
				(*p)->data, false);
		player_list_del_data(&server->players, (*p)->data, true);
		*p = server->players;
	}
}